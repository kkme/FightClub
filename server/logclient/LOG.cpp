#include <LOG.hpp>

namespace PWRD{

	namespace Log{

		/*=========================================================
		 * @private
		 =========================================================*/
		Client* LOG::client_ = NULL;

		LOG* LOG::instance_ = NULL;

		/*=========================================================
		 * @protected
		 =========================================================*/
		int LOG::init(){

			Conf* conf = Conf::GetInstance(file_.c_str());

			if(NULL == conf){

				Error("Conf GetInstance failed");

				return -1;

			}

			//TCP
			string tcphost = conf->find("LogClient", "address");

			if(!tcphost.compare("")){

				tcphost = "127.0.0.1";

			}

			string portstr = conf->find("LogClient", "port");

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

			Address tcpaddr.Set(tcphost, port);

			//timeout
			string timeout = DEFAULTTIMER;

			string time = conf->find("timeout", "interval");

			try{

				timeout = boost::lexical_cast<int>(time);

				Trace("TRACE Timeout: interval=%s", time.c_str());

			}
			catch(boost::bad_lexical_cast& e){

				Error("Bad Lexical cast: time=%s, exception=%s", time.c_str(), e.what());

				return 0;

			}

			Note("Timeout: %d", timeout);


			client_ = new Client(timeout, tcpaddr);

			assert(NULL != client_);

			client_->Open();

			return 1;


		} //init

		int LOG::fini(){

			delete client_;

			client_ = NULL;

			delete instance_;

			instance_ = NULL;

			return 1;

		} //fini

		/*=========================================================
		 * @public
		 =========================================================*/
		LOG* LOG::Instance(){
			
			if(NULL == instance_){

				instance_ = new LOG();

			}

			return instance_;

		} //Instance

		int LOG::Log(int _type, const string& _msg){
			
			Head head;

			head.type = LOG;

			head.version = 1;

			LogRecord record;

			record.set_message(_msg);

			head.length = record.ByteSize();

			char* buf = new char[head.length];

			*buf = 0;

			record.SerializeToArray(buf, head.length);

			if(ESTABLISHED == client_->Connected()){

				client_->Send(head, buf, head.length);
			
			}
			else{

				Error("Connection lost: roleid=%d", roleid);
			
			}

			delete buf;

			return head.length;

		} //Log
	} //Log

} //PWRD
