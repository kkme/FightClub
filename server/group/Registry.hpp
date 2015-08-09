#ifndef __REGISTRY_HPP
#define __REGISTRY_HPP

#include <Time.hpp>

#include <Global.hpp>

#include <Daemon.hpp>

#include <Mutex.hpp>

#include <EventHandler.hpp>

#include <FightClub.pb.h>

using namespace PWRD;

using namespace PWRD::IPC;

using namespace PWRD::Utils;

using namespace PWRD::Event;

#include <boost/multi_index/member.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/ordered_index.hpp>
#include <boost/multi_index/hashed_index.hpp>

using boost::multi_index_container;
using namespace boost::multi_index;

#define CLEARTIME 300

namespace PWRD{

	namespace Mem{

		typedef EventHandler* HANDLER;

		struct Gamer_t{

			string roleid;

			HANDLER handler;

			int pklevel;

			int ranklevel;

			STAT stat;

			Gamer_t(HANDLER _handler):handler(_handler){}

			Gamer_t(const string& _roleid, HANDLER _handler, int _level, STAT _stat, bool _flag):roleid(_roleid), handler(_handler), stat(_stat){

				if(_flag){ ranklevel = _level; } else{ pklevel = _level; }

			}

			Gamer_t(const string& _roleid, HANDLER _handler, int _pklevel, int _ranklevel)
				:roleid(_roleid), handler(_handler), pklevel(_pklevel), ranklevel(_ranklevel), stat(IDLE){}

		}; //Gamer_t

		typedef struct {} ROLEIDTAG;

		typedef struct {} HANDLERTAG;

		typedef struct {} PKLEVELTAG;

		typedef struct {} RANKLEVELTAG;

		typedef struct {} STATTAG;

		typedef multi_index_container<

			Gamer_t,

			indexed_by<

				ordered_unique<

					tag<ROLEIDTAG>, BOOST_MULTI_INDEX_MEMBER(Gamer_t, string, roleid)>,

				ordered_unique<

					tag<HANDLERTAG>, BOOST_MULTI_INDEX_MEMBER(Gamer_t, HANDLER, handler)>,

				ordered_non_unique<

					tag<PKLEVELTAG>,  BOOST_MULTI_INDEX_MEMBER(Gamer_t, int, pklevel)>,

				ordered_non_unique<

					tag<RANKLEVELTAG>,  BOOST_MULTI_INDEX_MEMBER(Gamer_t, int, ranklevel)>,

				ordered_non_unique<

					tag<STATTAG>,  BOOST_MULTI_INDEX_MEMBER(Gamer_t, STAT, stat)> 
			>

		> GamerSet; //GamerSet

		typedef vector<boost::shared_ptr<Gamer_t> > GamerList;

		class Registry{

			public:

				static long Size();

				virtual ~Registry(){ fini(); }

				static Registry* Instance();

				static bool Check(const string& _roleid);

				static bool Check(HANDLER _handler);

				static void Registe(const Gamer_t& _gamer);

				static void Remove(HANDLER _handler);

				static boost::shared_ptr<Gamer_t> Get(const string& _roleid);

				static GamerList Get(int _level, int _num, bool _type); //false: pk; true: rank

				static string Get(HANDLER _handler);

				static bool UpdateStat(const string& _roleid, STAT _stat);

				static bool UpdateLevel(const string& _roleid, int _level, bool _type); //false: pk; true: rank

				static STAT QueryStat(const string& _roleid);

				static HANDLER QueryHandler(const string& _roleid);


			protected:

				Registry(){ init(); }

				static int init();

				static int fini();

			private:

				static Mutex mutex_;

				static GamerSet map_;

				static Registry* instance_;
			
		}; //Registry

	} //Mem

} //PWRD

#endif
