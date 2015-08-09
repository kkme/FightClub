#ifndef __SESSION_HPP
#define __SESSION_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Stream.hpp>

#include <Socket.hpp>

#include <Datagram.hpp>

#include <Acceptor.hpp>

#include <Exception.hpp>

#include <ReactorService.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <TimerQueue.hpp>

#include <CircleBuf.hpp>

#include <SyncQueue.hpp>

#include <ActiveQueue.hpp>

#include <Mutex.hpp>

using namespace PWRD;

using namespace PWRD::Utils;

using namespace PWRD::Event;

using namespace PWRD::Network;

using namespace PWRD::ActiveObject;


namespace PWRD{

	namespace Network{

		class Session : public EventHandler{  

			public:

				Session():flag_(false), recv_(true){ init(); };

				virtual ~Session(){ fini(); };

				Stream& GetStream() const;

				virtual Handle GetHandle() const;

				virtual void Open(int _intra = DEFAULTTIMER);

				virtual int Send();

				virtual int SendLost();

				virtual int SendHeartbeat();

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

				char *buf_; //buffer for receive

				Head ohead_; //output packet

				Head* head_; //heart

				Mutex lock_;

				char* ostream_;

				Stream* stream_;

				CircleBuffer* circle_;

		};

	}//Network

}//PWRD

#endif
