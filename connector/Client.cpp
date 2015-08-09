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

			}

			return -1;

		}

		/*
		 * @public
		 */
		void Client::Open(int _timeout){

			timeout_ = _timeout;

			TimerQueue::Register(this, _timeout);

			try{

				Trace("TRACE Open & Register Handler: addr=%s, timeout=%d", addr_.IP().c_str(), _timeout);

				connector_->Connect(addr_, stream_);

				ReactorService::Instance()->Register(this, EventHandler::READ_MASK);

				connected_ = true;

				Send();



			}
			catch(const Exception& e){

				Error("Exception occur: addr=%s, errmsg=%s", addr_.IP().c_str(), e.what());

				return;
			}



		}


		int Client::Timeout(bool& _flag UNUSED){

			if(!connected_){

				Open(timeout_);

				return 1;

			}
			else{
				
				//Trace("Trace ============Timeout=========");

				Send();

			}

			//_flag = flag_;

			return 0;

		}

		int Client::Close(){

			try{

				connected_ = false;

				Trace("TRACE Connection was closed by peer!: addr=%s", addr_.IP().c_str());

				//TimerQueue::Remove(this);

				return 1;

			}
			catch(const Exception& e){

				Error("Exception occur: addr=%s, errmsg=%s", addr_.IP().c_str(), e.what());

				return -1;

			}

		}

		int Client::SendHeartbeat(){

			//Trace("TRACE Send Heartbeat: addr=%p", this);

			if(connected_){

				Head head;

				memset(&head, 0, HEADLEN);

				head.version = 0.0f;

				head.type = HA;

				head.length = 0;

				try{

					int bytes = stream_.Send((char*)&head, HEADLEN);

					//Trace("TRACE Send Heartbeat: stream=%p, bytes=%d", &stream_, bytes);

				}
				catch (const Exception& e){

					Error("Exception occur: addr=%s, port=%d, errmsg=%s", addr_.IP().c_str(), addr_.Port(), e.what());

					connected_ = false;

					return -1;
				}
			}


			return 0;


		}	


		int Client::Send(){

			try{

				//Send request to servers
				if(connected_){
					
					//Trace("TRACE"); 
					Trace("TRACE Send: connected_=%d, syncq=%p, size=%d", (int)connected_, syncq_, syncq_->Size());

					if(syncq_->Size() > 0){
					
						Request* res  = syncq_->Dequeue();

						if(NULL == res){

							Error("Bad string: syncq_=%p, size=%d", syncq_, syncq_->Size());

							return -1;


						}

						//Create a Fileblock witch defined by protobuf, and send it to the server

						FileBlock* fb = new FileBlock();

						assert(NULL != fb);

						fb->set_taskid(res->taskid());

						fb->set_path(res->path());

						fb->set_content(res->content());

						fb->set_type(res->type());

						int size = fb->ByteSize();

						//Serialize to ostream
						fb->SerializeToArray(ostream_, size);

						//Delete the request
						delete res;

						//Send
						try{
							
							ohead_.version = 1.0f;

							ohead_.type = FB;

							ohead_.length = size;

							int bytes = stream_.Send((char *)&ohead_, HEADLEN);

							Trace("TRACE Send Head: addr=%s, bytes=%d", addr_.IP().c_str(), bytes);

							bytes = stream_.Send((char *)ostream_, size);

							Trace("TRACE Send Body: addr=%s, bytes=%d", addr_.IP().c_str(), bytes);

							return bytes;

						}
						catch(const Exception& e){


							Error("Exception occur: addr=%s, port=%d, errmsg=%s", addr_.IP().c_str(), addr_.Port(), e.what());

							return -1;

						}

					}

				}//if
				else{

					Trace("Connection Lost!!!!!!!!!! connected_=%d", (int)connected_);

				}

			}
			catch(const Exception& e){

				Error("Exception occur: addr=%s, port=%d, errmsg=%s", addr_.IP().c_str(), addr_.Port(), e.what());

				connected_ = false;

				return -1;

			}

			return 1;

		}

		int Client::Receive(){

			try{
				//Use nonblocking IO receive data, throw Exception when occur error

				int bytes =  0;

				while((bytes = stream_.Receive(istream_, BUFSIZE)) <= 0) {


					if(bytes < 0 && (EINTR == errno || EAGAIN == errno)){

						continue;

					}

					Error("Stream Closed by peer: addr=%s, len=%d, errno=%d, errmsg=%s",
							addr_.IP().c_str(), bytes, errno, strerror(errno));

					stream_.Close();

					return -1;


				}


				//clear the flag
				flag_ = true;

				int n = circle_->add(istream_, bytes);

				//Trace("Receive data: addr=%s, bytes=%d, add_buffer=%d", addr_.IP().c_str(), bytes, n); 

				//recive 

				for (;;){

					if (recv_ && circle_->used() >= HEADLEN) {

						bytes = circle_->get((char*)&ihead_, HEADLEN);

						//Trace("TRACE Receive Head: addr=%s, total=%d, get=%d, type=%d", addr_.IP().c_str(), circle_->used(), bytes, ihead_.type);

						int rev = 0;

						if((rev = HeadImpl::CheckProtocol(ihead_)) < 0){

							Error("Protocol Broken: addr=%s", addr_.IP().c_str());

							stream_.Close();

							return -1;

						}
						else if(HA == rev){

							//Trace("TRACE Receive a Heartbeat");

							recv_ = true;

							continue;
						}

						recv_ = false;

					} 

					if (!recv_ && circle_->used() >= (unsigned)ihead_.length) {

						char *buf = new char[ihead_.length];

						bzero(buf, ihead_.length);

						ssize_t len = circle_->get(buf, ihead_.length);
						

						/*
						Trace("TRACE Receive body: addr=%s, total=%d, get=%d, type=%d, bodylen=%d", 
								addr_.IP().c_str(), circle_->used(), len, ihead_.type, ihead_.length);

						*/

						recv_ = true;

						Result *result = new Result();

						assert(result != NULL);

						result->ParseFromArray(buf, ihead_.length);

						Response* response = Transform::Process(result);

						Trace("TRACE New Result: buf=%p, len=%d", buf, ihead_.length);

						//Note("ADD Addr=%p", res);

						string* json = new string(response->serialize());

						assert(json);

						FeedBack* feed = new FeedBack(result->type(), json);

						activeq_->Enqueue(feed);

						delete buf;

						delete result;

						delete response;

					}

					if ((recv_ && circle_->used() < HEADLEN) || 
							(!recv_ && circle_->used() < (unsigned)ihead_.length) ) {
						
						break;

					}
				}

			} 
			catch (const Exception& e){ 

				Error("Exception occur: addr=%s, errmsg=%s", addr_.IP().c_str(), e.what());

				return -1;
			}

			return 0;

		}

	}//Network

}//PWRD
