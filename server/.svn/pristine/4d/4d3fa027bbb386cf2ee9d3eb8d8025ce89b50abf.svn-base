#ifndef __CLIENT_H
#define __CLIENT_H

#include <Head.hpp>

#include <Mutex.hpp>

#include <Daemon.hpp>

#include <Global.hpp>

#include <Stream.hpp>

#include <Address.hpp>

#include <Exception.hpp>

#include <Connector.hpp>

#include <FightClub.pb.h>

#include <CircleBuf.hpp>

#include <TimerQueue.hpp>

#include <EventHandler.hpp>

#include <ReactorService.hpp>

#include <ActiveQueueSigalton.hpp>

using namespace PWRD;

using namespace PWRD::Event;

using namespace PWRD::Utils;

using namespace PWRD::Network;

using namespace PWRD::ActiveObject;

namespace PWRD{

	namespace Network{

		class Client: public EventHandler{

			public:

				Client(int _timeout, Address& _addr):timeout_(_timeout), connected_(false), flag_(false), recv_(true), addr_(_addr){ init(); };

				virtual ~Client( ){ fini(); };

				virtual Handle GetHandle() const{ return stream_.GetHandle(); };

				virtual void Open();

				virtual int Timeout(bool &);

				virtual int Close();

				virtual int Send(Head& _head, const char* _buf, int length);

				virtual int Receive();

				virtual bool Connected(){ return connected_; };

			protected:

				int init();

				int fini();

			private:
				
				//timeout
				int timeout_;

				bool connected_;

				bool flag_;

				bool recv_;

				Head ihead_;

				Head ohead_;

				Mutex mutex_;

  				char *istream_;

				char *ostream_;

				Address& addr_;

				Stream stream_;

				Connector* connector_;

				CircleBuffer* circle_;

		};

	}

}

#endif
