#ifndef __VERSIONSERVICE_HPP
#define __VERSIONSERVICE_HPP

#include <Conf.hpp>

#include <Head.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Server.hpp>

#include <FightClub.pb.h>

#include <StringTool.hpp>

#include <boost/shared_ptr.hpp>


using namespace PWRD;

using namespace PWRD::Event;

namespace PWRD{

	namespace FC{

		typedef enum {

			FLAGS = O_RDONLY|O_CREAT,

			MODE  = S_IRUSR

		}OPTION;

		class VersionService{

			public:

				typedef vector<boost::shared_ptr<string> > Vector;

				VersionService(){ init(); }

				virtual ~VersionService(){ fini(); }

				static int Process(boost::shared_ptr<C2S_Version> _packet UNUSED, EventHandler* _handler UNUSED);

			protected:

				int init();

				int fini();

			private:

				static void LookDir(boost::shared_ptr<Vector>);

				static void ReadFile(const string* _file, File*);


		};//VersionService

	}//FC

}//PWRD

#endif
