#include <ServerImpl.hpp>

namespace PWRD{

	namespace Network{

		//=============================================================
		//protected
		//=============================================================
		int ServerImpl::init(){

			server_ = NULL;

			switch(Load()){

				case -1:

					Error("ServerImpl init failed");

					return -1;

				case 0:


					server_ = new Server(timeout_, tcpaddr_, syncq_, activeq_);

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
			
			int value = 0;

			stringstream ss;

			ss << str;

			ss >> value;

			return value;

		}

		//=============================================================
		//public
		//=============================================================
		void ServerImpl::Open(){

			if(NULL != server_){

				Trace("TRACE Open TCP Server");

				server_->Open();

			}

		}
		/*
		   @private
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

				try{

					port = Str2Int(portstr);

				}
				catch(std::exception& e){

					Error("Bad Lexical cast: port=%s, exception=%s", (portstr).c_str(), e.what());

					return 1;

				}

			}

			Trace("TRACE TCP Bind host: tcphost=%s, port=%d", tcphost_.c_str(), port);

			tcpaddr_.Set(tcphost_, port);

			//timeout

			timeout_ = DEFAULTTIMER;

			string time = conf->find("timeout", "interval");

			try{

				timeout_ = Str2Int(time);

				Trace("TRACE Timeout: interval=%s", time.c_str());

			}
			catch(std::exception& e){

				Error("Bad Lexical cast: time=%s, exception=%s", time.c_str(), e.what());

				return 0;

			}

			Note("Timeout: %d", timeout_);


			return 0;

		}


	}


}
