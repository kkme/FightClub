#ifndef __CLIENT_H
#define __CLIENT_H

#include <Head.hpp>

#include <Daemon.hpp>

#include <Global.hpp>

#include <Stream.hpp>

#include <Address.hpp>

#include <Connector.hpp>

#include <EventHandler.hpp>

#include <MonitorBlock.hpp>

#include <Monitor.pb.h>

#include <CircleBuf.hpp>

#include <SyncQueue.hpp>

#include <Transform.hpp>

#include <TimerQueue.hpp>

#include <ActiveQueue.hpp>

#include <ReactorService.hpp>

#include <FeedBack.hpp>

using namespace PWRD;

using namespace PWRD::JSON;

using namespace PWRD::Utils;

using namespace PWRD::Event;

using namespace PWRD::Network;

using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace Network{

		class Client: public EventHandler{

			public:

				Client(int _timeout, Address& _addr, SyncQueue<Request*>* _syncq, ActiveQueue<FeedBack*> *_activeq):flag_(false), recv_(true), connected_(false), timeout_(_timeout), addr_(_addr), syncq_(_syncq), activeq_(_activeq){ init(); };

				virtual ~Client( ){ fini(); };

				virtual Handle GetHandle() const{ return stream_.GetHandle(); };

				virtual void Open(int _timeout = DEFAULTTIMER);

				virtual int Timeout(bool &);

				virtual int Close();

				virtual int Send();

				virtual int Receive();

				virtual int SendHeartbeat();

				virtual bool Connected(){ return connected_; };

			protected:

				int init();

				int fini();

			private:
				bool flag_;

				bool recv_; 

				bool connected_;

				//timeout
				int timeout_;

				Head ihead_;

				Head ohead_;

  				char *istream_;

				char *ostream_;

				Address& addr_;

				Stream stream_;

				Connector* connector_;

				CircleBuffer* circle_;

				SyncQueue<Request*>* syncq_;

				ActiveQueue<FeedBack*>* activeq_;

		};

	}

}

#endif
