#include <ClientImpl.hpp>

namespace PWRD{

	namespace Network{

		/*
		   @protected
		   */
		int ClientImpl::init(){

			server_ = NULL;

			switch(Load()){

				case -1:

					Error("ClientImpl init failed");

					return -1;

				case 0:


					server_ = new Client(timeout_, tcpaddr_);

					Note("New Client: addr=%p", server_);

					if(NULL == server_){

						Error("New Client failed");

						return -1;

					}

					break;

			}

			return 1;

		}

		int ClientImpl::fini(){

			if(server_ != NULL)

				delete server_;

			return 1;

		}

		/*
		   @public
		   */
		void ClientImpl::Open(){

			if(NULL != server_){

				Trace("TRACE Open TCP Client");

				server_->Open();

			}

		}

		/*
		   @private
		   */
		int ClientImpl::Load(){

			Conf* conf = Conf::GetInstance(file_.c_str());

			if(NULL == conf){

				Error("Conf GetInstance failed");

				return -1;

			}

			//TCP
			tcphost_ = conf->find("LogserviceTCPClient", "address");

			if(!tcphost_.compare("")){

				tcphost_ = "0.0.0.0";

			}

			string portstr = conf->find("LogserviceTCPClient", "port");

			int port = TCP_SERVER_PORT;

			if(portstr.compare("")){

				try{

					port = boost::lexical_cast<int>(portstr);

				}
				catch(boost::bad_lexical_cast& e){

					Error("Bad Lexical cast: port=%s, exception=%s", (portstr).c_str(), e.what());

					return 1;

				}

			}

			Trace("TRACE TCP Bind host: tcphost=%s, port=%d", tcphost_.c_str(), port);

			tcpaddr_.Set(tcphost_, port);

			portstr = conf->find("LogserviceClient", "port");

			if(!portstr.compare("")){

				port = UDP_SERVER_PORT;

			}
			else{

				try{

					port = boost::lexical_cast<int>(portstr);

				}
				catch(boost::bad_lexical_cast& e){

					Error("Bad Lexical cast: port=%s, exception=%s", (portstr).c_str(), e.what());

					return 0;

				}

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

		}


	}


}
