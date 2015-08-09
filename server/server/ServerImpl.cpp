#include <ServerImpl.hpp>

namespace PWRD{

	namespace Network{

		/*
		   @protected
		   */
		int ServerImpl::init(){

			server_ = NULL;

			switch(Load()){

				case -1:

					Error("ServerImpl init failed");

					return -1;


				case 0:


					server_ = new Server(timeout_, tcpaddr_);

					Trace("TRACE New Server: addr=%p", server_);

					if(NULL == server_){

						Error("New Server failed");

						return -1;

					}

					break;


			}

			return 1;

		}

		int ServerImpl::fini(){

			if(server_ != NULL)

				delete server_;

			return 1;

		}

		int ServerImpl::Str2Int(string str){
			
			int result = 0;	

			stringstream ss;

			ss << str;

			ss >> result;

			return result;


		}
		
		/*
		 *  @public
		 */
		void ServerImpl::Open(){

			if(NULL != server_){

				Trace("TRACE Open TCP Server");

				server_->Open();

			}

		}

		/*
		 *  @private
		 */
		int ServerImpl::Load(){

			Conf* conf = Conf::GetInstance(file_.c_str());

			if(NULL == conf){

				Error("Conf GetInstance failed");

				return -1;

			}

			//TCP
			tcphost_ = conf->find("LogserviceTCPServer", "address");

			if(!tcphost_.compare("")){

				tcphost_ = "0.0.0.0";

			}

			string portstr = conf->find("LogserviceTCPServer", "port");

			int port = TCP_SERVER_PORT;

			if(portstr.compare("")){

				port = Str2Int(portstr);

			}

			Trace("TRACE TCP Bind host: tcphost=%s, port=%d", tcphost_.c_str(), port);

			tcpaddr_.Set(tcphost_, port);


			//timeout
			timeout_ = DEFAULTTIMER;

			string time = conf->find("timeout", "interval");

			timeout_ = Str2Int(time);

			Trace("TRACE Timeout: interval=%s", time.c_str());


			return 0;

		}


	}


}
