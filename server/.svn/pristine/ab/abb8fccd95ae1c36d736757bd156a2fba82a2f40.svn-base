#include <Service.hpp>

namespace PWRD{

	namespace FC{

		int Service::size_ = THREADPOOLSIZE;

		pool Service::pool_;

		Service* Service::instance_ = NULL;

		/*=========================================================
		 * @protected
		 =========================================================*/
		int Service::init(){

			Conf* conf = Conf::GetInstance();

			string str = conf->find("ThreadPool", "size");

			size_ = StringTool::Str2Int(str);

			pool_.size_controller().resize(size_);

			return 1;

		}

		int Service::fini(){

			return 1;

		}

		/*=========================================================
		 * @public
		 =========================================================*/
		 Service* Service::Instance(){
		 
			if(NULL == instance_){
			
				instance_ = new Service();

			}

			return instance_;
			
		 }

		 pool& Service::ThreadPool(){
		 
		 	return pool_;

		 }//ThreadPool

	}//FC

}//PWRD
