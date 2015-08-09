#ifndef __SERVER_HPP
#define __SERVER_HPP

#include <Conf.hpp>
#include <Head.hpp>
#include <Stream.hpp>
#include <Exception.hpp>
#include <Socket.hpp>
#include <Datagram.hpp>
#include <Acceptor.hpp>
#include <ReactorService.hpp>

#include <Global.hpp>
#include <Request.hpp>
#include <Scheduler.hpp>
#include <Memorypool.hpp>
#include <ActiveQueue.hpp>
#include <ActiveLogRecord.hpp>

#include <TimerQueue.hpp>

#include <CircleBuf.hpp>

using namespace PWRD;

using namespace PWRD::Utils;
using namespace PWRD::Event;
using namespace PWRD::Network;
using namespace PWRD::Persist;
using namespace PWRD::ActiveObject;


namespace PWRD{

	namespace Network{

		class HeadImpl{

			public:

				static int CheckProtocol(Head&);
		};

		//UDP
		class DatagramService :public EventHandler{

			public:

				DatagramService(Address& _addr, ActiveQueue<Request*> *_activeq):
					flag_(false), addr_(_addr), activeq_(_activeq){ init(); }

				virtual ~DatagramService(){ fini(); }

				virtual void Open(int _intra = DEFAULTTIMER);

				virtual int Send();

				virtual int Receive();

				virtual int Timeout(bool &);

				virtual int Close();

				virtual Handle GetHandle() const;

				virtual bool Flag(){return flag_;};

			protected:

				int init();

				int fini();

			private:

				bool flag_;

				Datagram *dg_;

				Address& addr_;

				char *buf_;

				ActiveQueue<Request*> *activeq_;
		};

		//TCP
		class StreamHandler : public EventHandler{  

			public:

				StreamHandler(ActiveQueue<Request*> *_activeq):flag_(false), recv_(true), activeq_(_activeq){ init(); };

				virtual ~StreamHandler(){ fini(); };

				Stream& GetStream() const;

				virtual Handle GetHandle() const;

				virtual void Open(int _intra = DEFAULTTIMER);

				virtual int Send();

				virtual int Receive();

				virtual int Timeout(bool &);

				virtual int Close();

				virtual bool Flag(){return flag_;};

			protected:

				int init();

				int fini();

			private:

				bool flag_;

				bool recv_; //HA, HEAD, BODY

				Head* head_;

				Stream* stream_;

				char *buf_;

				CircleBuffer* circle_;

				ActiveQueue<Request*> *activeq_;

		};

		class Server: public EventHandler{

			public:

				Server(int _timeout, Address& _addr, ActiveQueue<Request*> *_activeq) : 
					timeout_(_timeout), addr_(_addr), activeq_(_activeq){ init(); }

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

				ActiveQueue<Request*> *activeq_;

		};

	}


}

#endif
