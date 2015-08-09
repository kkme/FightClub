#include <ClientImpl.hpp>

namespace PWRD{

	namespace Network{

		/*
		 *  @protected
		 */
		int ClientImpl::init(){

			Load();

			return 1;

		}

		int ClientImpl::fini(){

			return 1;

		}

		/*
		 *  @private
		 */
		int ClientImpl::Load(){

			Conf* conf = Conf::GetInstance(file_.c_str());

			if(NULL == conf){

				Error("Conf GetInstance failed");

				return -1;

			}

			//timeout

			timeout_ = DEFAULTTIMER;

			string time = conf->find("timeout", "interval");

			try{

				timeout_ = boost::lexical_cast<int>(time);

				Trace("TRACE Timeout: interval=%s", time.c_str());

			}
			catch(boost::bad_lexical_cast& e){

				Error("Bad Lexical cast: time=%s, exception=%s", time.c_str(), e.what());

				return 0;

			}

			Note("Timeout: %d", timeout_);


			return 0;

		}//Load

		/*
		   @public
		   */
		void ClientImpl::Open(){


		}

		void ClientImpl::Run(){

			while(true){

				Trace("TRACE ClientImpl::Run()");

				while(areq_->AsyncWait() < 0){

					Trace("TRACE ClientImpl::Run %s", strerror(errno));

					continue;

				}

				Request* request = areq_->Dequeue();

				assert(NULL != request);

				Process(request);

			}

			return;

		}

		int ClientImpl::Process(Request* _req){

			Note("TRACE ClientImpl::Process()");

			assert(NULL != _req);

			if(!_req->type().compare("iplist")){

				Trace("TRACE Request type=%s", _req->type().c_str());

				FileSink sink;

				sink.Sync(_req->type(), _req->path(), _req->content());

				XMLBuilder* builder = new IPListBuilder(_req->path());

				assert(NULL != builder);

				builder->set_file(_req->path());

				builder->Load();

				ItemMap pmap = builder->items();

				//Compare to map
				ItemMap::iterator piter = pmap.begin();

				for(; piter != pmap.end(); piter++){

					Trace("TRACE Request: addr=%s, port=%d", piter->first.c_str(), piter->second);

					//in iplist not in sessionmap
					if(ss_.find(piter->first) == ss_.end()){

						Address addr(piter->first, piter->second);

						SyncQueue<Request*>* syncq = new SyncQueue<Request*>();

						assert(NULL != syncq);

						Client* client = new Client(timeout_, addr, syncq, astrq_);	

						assert(NULL != client);

						client->Open(timeout_);

						Trace("TRACE New Client: client=%p, addr=%s, timeout=%d", client, addr.IP().c_str());

						ss_[piter->first] = client;

						cg_[client] = syncq;

						Trace("TRACE Session Group: addr=%s <-=-> client=%p", 
								piter->first.c_str(), client);

						Trace("TRACE Client Group: client=%p <-=-> syncq=%p",
								client, syncq);
					}

				}//for

				Sessions::iterator siter = ss_.begin();

				for(; siter != ss_.end();){

					//in sessionmap not in iplist
					if(pmap.find(siter->first) == pmap.end()){

						Client *client = siter->second;

						client->Close();

						ss_.erase(siter++);

						SyncQueue<Request*> *syncq = cg_[client];

						delete syncq;

						cg_.erase(client);

						Trace("TRACE Close client: client=%p, addr=%s", client, siter->first.c_str()); 
					}//if map
					else{
					
						siter++;

					}

				}//for


			}//iplist
			else if(!_req->type().compare("conf") || !_req->type().compare("script")){

				Trace("TRACE Request: type=%s, path=%s", _req->type().c_str(), _req->path().c_str());

				//Push the request to Syncq
				Client *client = ss_[_req->ip()];

				assert(NULL != client);

				SyncQueue<Request*>* syncq = cg_[client];

				assert(NULL != syncq);

				syncq->Enqueue(_req);

				Trace("TRACE Request: client=%p <-=-> syncq=%p", client, syncq);


			}//conf, script
			else{
				//Illegal request

				Response* result = new Response();

				assert(NULL != result);

				//Client accept task illegal
				result->set_errnum("301");

				result->set_type(1);

				result->set_taskid(_req->taskid());

				string* json = new string(result->serialize());

				assert(NULL != json);

				FeedBack* fb = new FeedBack(1, json);

				assert(NULL != fb);

				astrq_->Enqueue(fb);

				Trace("TRACE Request type not defined:  taskid=%s, errnum=301, type=1",
						_req->taskid().c_str());

				delete result;

				return -1;

			}

			//Send sucessful result back

			Response* result = new Response();

			assert(NULL != result);

			result->set_errnum("201");

			result->set_type(-1);

			result->set_taskid(_req->taskid());

			string* json = new string(result->serialize());

			assert(NULL != json);

			FeedBack* fb = new FeedBack(1, json);

			assert(NULL != fb);

			astrq_->Enqueue(fb);

			Note("Successful! taskid=%s, type=-1, num=201", _req->taskid().c_str());

			delete result;

			return 1;


		}

	}//Network


}//PWRD
