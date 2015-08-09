#include <Session.hpp>

using namespace PWRD{

	using namespace Network{

		//===================================================================
		//Session 
		//===================================================================
		/*
		   @protected
		   */
		int Session::init(){

			stream_ = new Stream;

			buf_ = new char[BUFSIZE];

			circle_ = new CircleBuffer();

			ostream_ = new char[BUFSIZE];

			assert(NULL != ostream_);

			head_ = new Head();

			assert(NULL != stream_);

			assert(NULL != buf_);

			assert(NULL != circle_);

			assert(NULL != head_);

			return 1;

		}

		int Session::fini(){

			delete stream_;

			stream_ = NULL;

			delete buf_;

			buf_ = NULL;

			delete ostream_;

			ostream_ = NULL;

			delete circle_;

			circle_ = NULL;

			delete head_;

			head_ = NULL;

			return 1;

		}

		/*
		   @public
		   */
		Stream& Session::GetStream() const{

			return *stream_;
		}

		void Session::Open(int _intra){

			Trace("TRACE Open & Register Handler: handler=%p, intra=%d", this, _intra);

			stream_->Nonblock(); 

			ReactorService::Instance()->Register(this, EventHandler::READ_MASK);

			TimerQueue::Register(this, _intra);
		}

		Handle Session::GetHandle() const{

			return stream_->GetHandle();

		}

		int Session::Receive(){


			try{
				//Use nonblocking IO receive data, throw Exception when occur error
				int bytes =  0;

				while((bytes = stream_->Receive(buf_, BUFSIZE)) <= 0) {


					if(bytes < 0 && (EINTR == errno || EAGAIN == errno)){

						continue;

					}

					Error("Stream Closed by peer: buf=%p, len=%d, errnum=%d, errmsg=%s",
							buf_, bytes, errno, strerror(errno));

					stream_->Close();

					Close();

					return 0;


				}


				//clear the flag
				flag_ = true;

				int n = circle_->add(buf_, bytes);

				//Note("Receive data: buf=%p, bytes=%d, add_buffer=%d", buf_, bytes, n); 

				for (;;){

					if (recv_ && circle_->used() >= HEADLEN) {

						bytes = circle_->get((char*)head_, HEADLEN);

						Trace("TRACE Receive Head: total=%d, get=%d, version=%f, type=%d, length=%lu", 
								circle_->used(), bytes, head_->version, head_->type, head_->length);

						int rev = 0;

						if((rev = HeadImpl::CheckProtocol(*head_)) < 0){

							Error("Protocol Broken");

							stream_->Close();

							return -1;

						}
						else if(HA == rev){

							Trace("TRACE Receive a Heartbeat");

							recv_ = true;

							continue;
						}

						recv_ = false;

					} 

					if (!recv_ && circle_->used() >= (unsigned)head_->length) {

						char *buf = new char[head_->length];

						bzero(buf, head_->length);

						ssize_t len = circle_->get(buf, head_->length);

						Trace("TRACE Receive body: total=%d, get=%d, type=%d, bodylen=%d", 
								circle_->used(), len, head_->type, head_->length);


						recv_ = true;

						FileBlock *res = new FileBlock();
						//Memorypool::Instance()->construct(buf, head_->length);

						assert(NULL != res);

						res->ParseFromArray(buf, head_->length);
							
						Trace("TRACE New FileBlock: buf=%p, len=%d", buf, head_->length);

						if(NULL == res){

							Error("New FileBlock failed: buf_=%p, len=%d", buf_, head_->length);

							return -1;

						}

						//Note("ADD Addr=%p", res);
						activeq_->Enqueue(res);

						delete buf;

					}

					if ((recv_ && circle_->used() < HEADLEN) || 

							(!recv_ && circle_->used() < (unsigned)head_->length)) {

						break;

					}

				}

			} catch (const Exception& e){ 

				Error("Exception occur: errmsg=%s", e.what());

				return -1;
			}

			return 0;
		}


		int Session::SendHeartbeat(){

			Trace("TRACE Send: addr=%p", this);

			Head head;

			memset(&head, 0, HEADLEN);

			head.version = 0.0f;

			head.type = HA;

			head.length = 0;

			try{

				int bytes = stream_->Send((char*)&head, HEADLEN);

				Trace("TRACE Send Heartbeat: stream=%p, bytes=%d", stream_, bytes);

			}
			catch (const Exception& e){

				Error("Exception occur: errmsg=%s", e.what());

				return -1;
			}

			return 0;

		}

		int Session::Send(){

			try{

				ohead_.version = 1.0f;

				ohead_.type = _mess->type();

				ohead_.length = size;

				int bytes = stream_->Send((char *)&ohead_, HEADLEN);

				Trace("TRACE Send Head: stream=%p, bytes=%d", stream_, bytes);

				bytes = stream_->Send((char *)ostream_, size);

				Trace("TRACE Send Body: stream=%p, bytes=%d", stream_, bytes);

				return bytes;


			}
			catch(const Exception& e){

				Error("Exception occur: errmsg=%s", e.what());

				return -1;

			}

			return 1;

		}

		int Session::SendLost(){
			

			return 1;

		}

		int Session::Timeout(bool& _flag){

			Trace("TRACE TCP Timeout: addr=%p", this);

			if(flag_){

				Trace("TRACE Timeout and receive data normal");

				flag_ = false;

			}
			else{

				Error("There are no data arrived, Close the Session");

				flag_ = true;

				Close();


			}

			_flag = flag_;

			return 0;

		}//Timeout

		int Session::Close(){

			try{

				TimerQueue::Remove(this);

				Error("Connect lost!: addr=%p", this);

				delete this;

			}
			catch (const Exception& e){

				Trace("TRACE Exception occur: errmsg=%s", e.what());

				return -1;
			}

			return 1;

		}//Close


	}//Network

}//PWRD
