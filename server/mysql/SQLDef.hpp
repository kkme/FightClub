#ifndef __SQLDEF_HPP
#define __SQLDEF_HPP

#include <Global.hpp>

#include <Daemon.hpp>

using namespace PWRD;

namespace PWRD{

		namespace DB{

				typedef enum{

					INIT_MAX = 0,
					INIT_USER,
					INIT_ITEM,
					INIT_EQUIP,
					INIT_BUFF,
					INIT_FRIEND,
					INIT_PK,
					INIT_RANK,
					SELECT_USER,
					UPDATE_PKEXP,
					UPDATE_PKLEVEL,
					UPDATE_RANKEXP,
					UPDATE_RANKLEVEL,
					UPDATE_MONEY,
					UPDATE_GOLD,
					UPDATE_CASHSTAT,
					UPDATE_LASTLOGOUT,
					UPDATE_ITEM,
					UPDATE_EQUIP,
					UPDATE_BUFF,
					UPDATE_FRIEND,
					UPDATE_PKWIN,
					UPDATE_PKLOST,
					UPDATE_RANKWIN,
					UPDATE_RANKLOST,
					INSERT_BILL

				
				}GAMERSQL;

				typedef vector<string> SQLVector;

				typedef map<GAMERSQL, string> SQLMap;

				class SQLDef{

						public:

								static SQLDef* Instance(); 

								~SQLDef(){ fini(); };

								static SQLVector Get();

								static string Get(GAMERSQL);

						protected:

								SQLDef(){ init(); };

								static int init();

								static int fini();


						private:

								static SQLMap map_;

								static SQLDef* instance_;

				
				}; //SQLDef


		} //DB

} //PWRD

#endif
