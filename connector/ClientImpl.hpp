#ifndef __CLIENTIMPL_HPP
#define __CLIENTIMPL_HPP

#include <Conf.hpp>

#include <Client.hpp>

#include <Address.hpp>

#include <FileSink.hpp>

#include <FeedBack.hpp>

#include <XMLBuilder.hpp>

#include <MonitorBlock.hpp>

#include <boost/lexical_cast.hpp>

#define TCP_SERVER_PORT 11101

#define UDP_SERVER_PORT 11100

using namespace PWRD;

using namespace PWRD::XML;

using namespace PWRD::JSON;

using namespace PWRD::Logic;

using namespace PWRD::Network;

namespace PWRD{

	namespace Network{

		typedef map<string, Client*> Sessions;

		typedef map<Client*, SyncQueue<Request*>* > ClientGroup;

		class ClientImpl{

			public:

				ClientImpl(string& _file, ActiveQueue<Request*>* _areq, ActiveQueue<FeedBack*>* _astrq):file_(_file), areq_(_areq), astrq_(_astrq){ init(); };


				virtual ~ClientImpl(){ fini(); };

				void Open();

				void Run();

			protected:

				int init();

				int fini();

			private:

				int Load();

				int Process(Request*);

				int timeout_;

				string file_;

				Sessions ss_;

				ClientGroup cg_;

				ActiveQueue<Request*>* areq_;

				ActiveQueue<FeedBack*>* astrq_;
		};

	}

}

#endif
