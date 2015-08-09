#include <Server.hpp>
namespace PWRD{

	namespace Network{

		//===================================================================
		//HeadImpl
		//===================================================================
		int HeadImpl::CheckProtocol(Head &_head){

			if(LOG == _head.type){

				Trace("TRACE Receive a LOG pakage");

				if(_head.length < 0){

					Error("Invaild Head length: length=%d", _head.type);

				}

				if(BUFSIZE < _head.length){

					Error("Message's length beyond the BUFSIZE=%d: head.length=%d", BUFSIZE, _head.length);

					return 0;


				}


				return LOG;

			}
			else if(HA == _head.type){

				Trace("TRACE Receive a HA pakage");

				return HA;

			}

			Error("Invaild Head type: type=%d", _head.type);

			return -1;

		}

		//===================================================================
		//DatagramService
		//===================================================================
		/*
		   @protected
		   */
		int DatagramService::init(){

			dg_ = new Datagram(addr_);

			if(NULL == dg_){

				Error("New Buffer Error");

				return -1;
			}

			buf_ = new char[BUFSIZE];

			if(NULL == buf_){

				Error("New Buffer Error");

				return -1;
			}

			return 1;

		}

		int DatagramService::fini(){

			delete dg_;

			dg_ = NULL;

			delete buf_;

			buf_ = NULL;

			return 1;

		}

		/*
		   @public
		   */
		void DatagramService::Open(int _intra){

			Trace("TRACE Open: timer intra=%d", _intra);

			dg_->Nonblock();

			ReactorService::Instance()->Register(this, EventHandler::READ_MASK);

			//TimerQueue::Register(this, _intra);

		}

		int  DatagramService::Send(){

			Trace("TRACE Send: addr=%p", this);

			return 0;

		}

		int  DatagramService::Receive(){

			Trace("TRACE Receive");

			try{
				//datagram
				int bytes = 0;

				while((bytes = dg_->Receive(buf_, BUFSIZE)) <= 0){

					if (bytes == 0){

						Error("Datagram Closed by peer");

						dg_->Close();

						return 0;

					}

					if(EINTR == errno || EAGAIN == errno){

						continue;

					}


				}


				flag_ = true;

				buf_[bytes] = 0;

				Trace("TRACE Receive data: bytes=%d, buf=%p", bytes, buf_);


				/*
				 *	ActiveObject
				 */

				//Request *res = Memorypool::Instance().construct(buf_, bytes);
				//Request *res = new Request(buf_, bytes);

				Request *res = new Request(buf_, bytes);//Memorypool::Instance()->construct(buf_, bytes);

				if(NULL == res){

					Error("TRACE New Request: buf_=%p, len=%d", buf_, bytes);

					return -1;

				}

				activeq_->Enqueue(res);

			}
			catch (const PWRD::Event::Exception& e){

				Trace("Exception occur: errmsg=%s", e.what());

				return -1;
			}


			return 0;

		}

		int  DatagramService::Timeout(bool& _flag){

			Trace("TRACE UDP Timeout: addr=%p", this);

			if(flag_){

				Trace("TRACE Timeout and receive data normal");

				flag_ = false;

			}
			else{

				//Error("There are no data arrived, Close the Session");

				flag_ = true;

				//TimerQueue::Remove(this);

				Close();

			}

			_flag = flag_;

			return 0;

		}

		Handle DatagramService::GetHandle() const{

			return dg_->GetHandle();

		}

		int  DatagramService::Close(){

			Trace("TRACE UDP Timeout!");

			return -1;


		}

		//===================================================================
		//StreamHandler 
		//===================================================================
		/*
		   @protected
		   */
		int StreamHandler::init(){

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

		int StreamHandler::fini(){

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
		Stream& StreamHandler::GetStream() const{

			return *stream_;
		}

		void StreamHandler::Open(int _intra){

			Trace("TRACE Open & Register Handler: handler=%p, intra=%d", this, _intra);

			stream_->Nonblock(); 

			ReactorService::Instance()->Register(this, EventHandler::READ_MASK);

			TimerQueue::Register(this, _intra);
		}

		Handle StreamHandler::GetHandle() const{

			return stream_->GetHandle();

		}

		int StreamHandler::Receive(){


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

					stream_->Close();

					//Close();

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

						Request *res = new Request(buf, head_->length);//Memorypool::Instance()->construct(buf, head_->length);

						Trace("TRACE New Request: buf=%p, len=%d", buf, head_->length);

						if(NULL == res){

							Error("New Request failed: buf_=%p, len=%d", buf_, head_->length);

							return -1;

						}

						//Note("ADD Addr=%p", res);
						activeq_->Enqueue(res);

						delete buf;

					}

					if ((recv_ && circle_->used() < HEADLEN) || 
							(!recv_ && circle_->used() < (unsigned)head_->length) ) 
						break;
				}

			} catch (const Exception& e){ 

				Error("Exception occur: errmsg=%s", e.what());

				return -1;
			}

			return 0;
		}


		int StreamHandler::Send(){

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

				Trace("Trace Exception occur: errmsg=%s", e.what());

				return -1;
			}

			return 0;

		}

		int StreamHandler::Timeout(bool& _flag){

			Trace("TRACE TCP Timeout: addr=%p", this);

			if(flag_){

				//Trace("TRACE Timeout and receive data normal");
				//Note("Timeout and receive data normal");

				flag_ = false;

			}
			else{

				Error("There are no data arrived, Close the Session");

				flag_ = true;

				//stream_->Close();

				Close();


			}

			_flag = flag_;

			return 0;

		}

		int StreamHandler::Close(){

			try{

				TimerQueue::Remove(this);

				Error("Connect lost!: addr=%p", this);

				delete this;

			}
			catch (const Exception& e){

				Trace("Trace Exception occur: errmsg=%s", e.what());

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

			StreamHandler *sh_ = new StreamHandler(activeq_);

			Trace("TRACE New StreamHandler: addr=%p", sh_);

			if(NULL == sh_){

				Error("New StreamHandler failed");
				return -1;

			}

			acceptor_->Accept(sh_->GetStream());

			Note("Accept a client: handle=%d", sh_->GetHandle());

			sh_->Open(timeout_);

			return 0;
		}
	};

}
