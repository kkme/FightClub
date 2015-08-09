#include <ServerImpl.hpp>

namespace PWRD{

	namespace Network{

		/*
		   @protected
		   */
		int ServerImpl::init(){

			server_ = NULL;

			udpsvc_ = NULL;

			switch(Load()){

				case -1:

					Error("ServerImpl init failed");

					return -1;

				case 0:

					udpsvc_ = new DatagramService(udpaddr_, activeq_);

					Trace("TRACE New UPD Server: addr=%p", udpsvc_);

					if(NULL == udpsvc_){

						Error("New UDP Server failed");
						return -1;

					}

				case 1:


					server_ = new Server(timeout_, tcpaddr_, activeq_);

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

			if(udpsvc_ != NULL)

				delete udpsvc_;

			return 1;

		}

		/*
		   @public
		   */
		void ServerImpl::Open(){

			if(NULL != server_){

				Trace("TRACE Open TCP Server");

				server_->Open();

			}

			if(NULL != udpsvc_){

				Trace("TRACE Open UDP Server");

				udpsvc_->Open();

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

					port = boost::lexical_cast<int>(portstr);

				}
				catch(boost::bad_lexical_cast& e){

					Error("Bad Lexical cast: port=%s, exception=%s", (portstr).c_str(), e.what());

					return 1;

				}

			}

			Trace("TRACE TCP Bind host: tcphost=%s, port=%d", tcphost_.c_str(), port);

			tcpaddr_.Set(tcphost_, port);


			//UDP
			udphost_ = conf->find("LogserviceServer", "address");

			if(!udphost_.compare("")){

				udphost_ = "0.0.0.0";

			}

			portstr = conf->find("LogserviceServer", "port");

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

			Trace("TRACE UDP Bind host: tcphost=%s, port=%d", udphost_.c_str(), port);

			udpaddr_.Set(udphost_, port);

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

			return 0;

		}


	}


}
