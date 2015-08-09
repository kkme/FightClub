#ifndef __SERVER_HPP
#define __SERVER_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Mutex.hpp>

#include <FCDef.hpp>

#include <Stream.hpp>

#include <Global.hpp>

#include <Socket.hpp>

#include <Datagram.hpp>

#include <Acceptor.hpp>

#include <Exception.hpp>

#include <FightClub.pb.h>

#include <TimerQueue.hpp>

#include <Registry.hpp>

#include <CircleBuf.hpp>

#include <DispatchCenter.hpp>

#include <ReactorService.hpp>

using namespace PWRD;

using namespace PWRD::IPC;

using namespace PWRD::Utils;

using namespace PWRD::Event;

using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		//TCP
		class Session : public EventHandler{  

			public:

				Session():flag_(false), recv_(true){ init(); };

				virtual ~Session(){ fini(); };

				Stream& GetStream() const;

				virtual Handle GetHandle() const;

				virtual void Open(int _intra = DEFAULTTIMER);

				virtual int Send(Head& _head, const char* _buf, int length);

				virtual int Receive();

				virtual int Timeout(bool &);

				virtual int Close();

				virtual CONNSTAT Connected(){ return connected_; };

				virtual bool Flag(){return flag_;};

			protected:

				int init();

				int fini();

			private:

				bool flag_;

				bool recv_; //HA, HEAD, BODY

				char *buf_;

				Head* head_;

				Mutex mutex_;

				Stream* stream_;

				CONNSTAT connected_;

				CircleBuffer* circle_;

		};

		class Server: public EventHandler{

			public:

				Server(int _timeout, Address& _addr) : 
					timeout_(_timeout), addr_(_addr){ init(); }

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

		};

	}


}

#endif
