#include <Server.hpp>

namespace PWRD{

	namespace Network{


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

			head_ = new Head();

			if(NULL == stream_){

				Error("New Acceptor Error");

				return -1;

			}

			if(NULL == buf_){

				Error("New Buffer Error");

				return -1;

			}

			if(NULL == circle_){

				Error("New Circle Error");

				return -1;

			}

			if(NULL == head_){

				Error("New Head Error");

				return -1;

			}

			return 1;

		}

		int Session::fini(){

			delete stream_;

			stream_ = NULL;

			delete buf_;

			buf_ = NULL;

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

			connected_ = ESTABLISHED;

			stream_->Nonblock(); 

			ReactorService::Instance()->Register(this, EventHandler::READ_MASK);

			//TimerQueue::Register(this, _intra);
		}

		Handle Session::GetHandle() const{

			return stream_->GetHandle();

		}

		int Session::Receive(){


			try{
				//Use nonblocking IO receive data, throw Exception when occur error
				//Receive Head

				int bytes =  0;

				while((bytes = stream_->Receive(buf_, BUFSIZE)) <= 0) {


					if(bytes < 0 && (EINTR == errno || EAGAIN == errno)){

						continue;

					}

					Error("Stream Closed by peer: buf=%p, len=%d, errno=%d, errmsg=%s",
							buf_, bytes, errno, strerror(errno));

					return -1;


				}


				//clear the flag
				flag_ = true;

				int n = circle_->add(buf_, bytes);

				Trace("Receive data: buf=%p, bytes=%d, add_buffer=%d", buf_, bytes, n); 

				//recive 

				for (;;){

					if (recv_ && circle_->used() >= HEADLEN) {

						bytes = circle_->get((char*)head_, HEADLEN);

						Trace("TRACE Receive Head: total=%d, get=%d, version=%d, type=%d, length=%d", 
								circle_->used(), bytes, head_->version, head_->type, head_->length);


						/*
						int rev = 0;

						if((rev = HeadImpl::CheckProtocol(*head_)) < 0){

							Error("Protocol Broken");

							stream_->Close();

							return -1;

						}
						else*/
						if(HA == head_->type){

							Trace("TRACE Receive a Heartbeat~~~~~~~~~~~~~~~~~~~~");

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

						Note("Create a new Packet: type=%d, len=%d", head_->type, head_->length);

						Packet* packet = new Packet(head_->length, head_->type, buf, this);

						ActiveQueueSigalton<Packet*>::Queue()->Enqueue(packet);

						delete buf;

					}

					if ((recv_ && circle_->used() < HEADLEN) || 
							(!recv_ && circle_->used() < (unsigned)head_->length) ) 
						break;
				}

			} catch (const Exception& e){ 

				Error("Exception occur: errmsg=%s", e.what());

				return -1;
			}//try

			return 0;

		}//Receive


		int Session::Send(Head& _head, const char* _buf, int length){

			try{
				
				ScopedLock lock(mutex_);

				int bytes = stream_->Send((char *)&_head, HEADLEN);

				Note("Send Head: stream=%p, bytes=%d", stream_, bytes);

				bytes = stream_->Send((char *)_buf, length);

				Note("Send Body: stream=%p, bytes=%d", stream_, bytes);

				return bytes;

			}
			catch(const Exception& e){

				Error("Exception occur: errmsg=%s", e.what());

				return -1;

			}//try

		}//Send


		int Session::Timeout(bool& _flag){

			Trace("TRACE TCP Timeout: addr=%p", this);

			if(flag_){

				Trace("TRACE Timeout and receive data normal");

				flag_ = false;

			}
			else{

				Error("There are no data arrived, Close the Session");

				flag_ = true;

			}

			_flag = flag_;

			return 0;

		}

		int Session::Close(){

			try{

				//TimerQueue::Remove(this);

				stream_->Close();

				connected_ = CLOSED;

				Registry::Remove(this);

				Error("Connect lost!: addr=%p", this);


			}
			catch (const Exception& e){

				//Trace("TRACE Exception occur: errmsg=%s", e.what());

				return -1;
			}

			return 1;

		}

		//===================================================================
		// Server
		//===================================================================
		/*
		   @protected
		 */
		int Server::init(){

			acceptor_ = new Acceptor(addr_);

			if(NULL == acceptor_){

				Error("New Acceptor Error");

				return -1;

			}

			return 1;

		}

		int Server::fini(){

			delete acceptor_;

			acceptor_ = NULL;

			return 1;

		}


		/*
		   @public
		 */
		void Server::Open(){

			Trace("TRACE Open Acceptor Handler");

			ReactorService::Instance()->Register(this, EventHandler::READ_MASK);
		}

		Handle Server::GetHandle() const{

			return acceptor_->GetHandle();

		}

		int Server::Receive(){

			Session *sh_ = new Session();

			Trace("TRACE New Session: addr=%p", sh_);

			if(NULL == sh_){

				Error("New Session failed");
				return -1;

			}

			acceptor_->Accept(sh_->GetStream());

			sh_->Open(timeout_);

			Note("Accept a client: handle=%d", sh_->GetHandle());

			return 0;
		}
	};

}
