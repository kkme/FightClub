#include <"RegistryService.hpp>

namespace PWRD{

	namespace FC{

		/*=========================================================
		 * @protected
		 =========================================================*/
		int RegistryService::init(){

			return 1;

		}

		int RegistryService::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		void RegistryService::Process(RegistryItem* _registry, HANDLER _handler){
			
			assert(NULL != _registry);

			assert(NULL != _handler);

			Registry::RegisteHandler(_registry->id(), _handler);

			Registry::Initialize(_handler, _registry->id());

			return ;

		}

		void RegistryService::Run(){
			
			return;

		}

	}

}
