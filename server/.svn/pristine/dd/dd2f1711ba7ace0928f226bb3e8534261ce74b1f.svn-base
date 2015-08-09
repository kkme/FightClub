#include <Client.hpp>

namespace PWRD{

	namespace Network{

		/*
		 * @protected
		 */
		int Client::init(){

			istream_ = new char[BUFSIZ];

			assert(istream_ != NULL);

			*istream_ = 0;

			ostream_ = new char[BUFSIZ];

			assert(ostream_ != NULL);

			*ostream_ = 0;

			connector_ = new Connector();

			assert(connector_ != NULL);

			circle_ = new CircleBuffer();

			assert(circle_ != NULL);

			return 1;
		}

		int Client::fini(){

			if(connector_ != NULL){

				delete connector_;

			}

			if(NULL != istream_){

				delete istream_;

			}

			if(NULL != ostream_){

				delete ostream_;

			}

			if(NULL != circle_){

				delete circle_;

				circle_ = NULL;
				
			}


			return -1;

		}

		/*
		 * @public
		 */
		void Client::Open(){

			//TimerQueue::Register(this, timeout_);

			try{

				Trace("TRACE Open & Register Handler: handler=%p, intra=%d", this, timeout_);

				connector_->Connect(addr_, stream_);

				ReactorService::Instance()->Register(this, EventHandler::READ_MASK);

				connected_ = true;


			}
			catch(const Exception& e){

				//Error("Exception occur: errmsg=%s", e.what());

				return;
			}



		}


		int Client::Timeout(bool& _flag UNUSED){

			if(!connected_){

				Open();

				return 1;

			}

			//_flag = flag_;

			return 0;

		}

		int Client::Close(){

			try{

				connected_ = false;

				Trace("TRACE Connection was closed by peer!");

				//TimerQueue::Remove(this);

				return 1;

			}
			catch(const Exception& e){

				//Error("Exception occur: errmsg=%s", e.what());

				return -1;

			}

		}

		int Client::Send(Head& _head, const char* _buf, int length){

			try{
				
				ScopedLock lock(mutex_);

				int bytes = stream_.Send((char *)&_head, HEADLEN);

				Note("Send Head: stream=%p, bytes=%d", &stream_, bytes);

				bytes = stream_.Send((char *)_buf, length);

				Note("Send Body: stream=%p, bytes=%d", &stream_, bytes);

			}
			catch(const Exception& e){

				//Error("Exception occur: errmsg=%s", e.what());

				return -1;

			}


		}//Send()

		int Client::Receive(){

			try{
				//Use nonblocking IO receive data, throw Exception when occur error

				int bytes =  0;

				while((bytes = stream_.Receive(istream_, BUFSIZE)) <= 0) {


					if(bytes < 0 && (EINTR == errno || EAGAIN == errno)){

						continue;

					}

					Error("Stream Closed by peer: buf=%p, len=%d, errno=%d, errmsg=%s",
							istream_, bytes, errno, strerror(errno));

					stream_.Close();

					return -1;


				}


				//clear the flag
				flag_ = true;

				int n = circle_->add(istream_, bytes);

				Trace("Receive data: buf=%p, bytes=%d, add_buffer=%d", istream_, bytes, n); 

				//recive 

				for (;;){

					if (recv_ && circle_->used() >= HEADLEN) {

						bytes = circle_->get((char*)&ihead_, HEADLEN);

						Trace("TRACE Receive Head: total=%d, get=%d, type=%d, length=%lu", 
								circle_->used(), bytes, ihead_.type, ihead_.length);

						int rev = 0;

						/*
						if((rev = HeadImpl::CheckProtocol(ihead_)) < 0){

							Error("Protocol Broken");

							stream_.Close();

							return -1;

						}
						else
						*/
						if(HA == rev){

							Trace("TRACE Receive a Heartbeat");

							recv_ = true;

							continue;
						}

						recv_ = false;

					} 

					if (!recv_ && circle_->used() >= (unsigned)ihead_.length) {

						char *buf = new char[ihead_.length];

						bzero(buf, ihead_.length);

						ssize_t len = circle_->get(buf, ihead_.length);

						Note("Receive body: total=%d, get=%d, type=%d, bodylen=%d", 
								circle_->used(), len, ihead_.type, ihead_.length);


						recv_ = true;

						Note("Create a new Packet: type=%d, len=%d", ihead_.type, ihead_.length);

						Packet* packet = new Packet(ihead_.length, ihead_.type, buf, this);

						ActiveQueueSigalton::Queue()->Enqueue(packet);

						delete buf;

					}

					if ((recv_ && circle_->used() < HEADLEN) || 
							(!recv_ && circle_->used() < (unsigned)ihead_.length) ) 
						break;
				}

			} 
			catch (const Exception& e){ 

				//Error("Exception occur: errmsg=%s", e.what());

				return -1;
			}

			return 0;

		}

	}//Network

}//PWRD
