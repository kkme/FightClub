#ifndef __SERVER_HPP
#define __SERVER_HPP

#include <Session.hpp>

namespace PWRD{

	namespace Network{

		class Server: public EventHandler{

			public:

				Server(int _timeout, Address& _addr) { init(); }

				virtual ~Server(){ fini(); }

				virtual void Open();

				virtual int Receive();

				virtual Handle GetHandle() const;

			protected:

				int init();

				int fini();

			private:

				int timeout_;

				Address& addr_;

				Acceptor* acceptor_;

		};//Server

	}//Network


}//PWRD

#endif
