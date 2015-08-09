#include <"VersionService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int VersionService::init(){

			return 1;

		}

		int VersionService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		void VersionService::Process(RegistryItem* _item UNUSED){
			
			Conf* conf = Conf::GetInstance();

			string version = conf->find("Version", "version");

			if(!_item->version().compare(version)){

				//match
				File file;

				file.set_uid(_item->uid());

				file.set_match(true);


			}
			else{

				string path = conf->find("Version", "path");

				string name = conf->find("Version", "name");
				

			}

		}

		void VersionService::Run(){
			

		}

	}

}
