#include "FileSink.hpp"

namespace PWRD{

	namespace Logic{

		/*
		 * @protected
		 */

		int FileSink::init(){

			/*
			   filedef_.path = "";

			   filedef_.name = "";

			   filedef_.mode = 00755;

			   filedef_.offset = 0;

			   filedef_.md5sum = "";
			   */

			return 1;

		}

		int FileSink::fini(){

			return 1;

		}


		/*
		 * @ public
		 */

		bool FileSink::Sync(const string& _type, const string& _path, const string& _content){

			int fd = -1;


			if((fd = open(_path.c_str(), FLAGS, (!_type.compare("script") ? MODEX : MODE))) < 0){

				Error("Open file error: file=%s, errmsg=%s", _path.c_str(), strerror(errno));

				return false;

			}

			if( (write(fd, _content.c_str(), _content.size())) < 0 ){

				Error("Write File failed!: file=%s, errmsg=%s", _path.c_str(), strerror(errno));

				return false;

			}

			close(fd);

			return true;

		}

		bool FileSink::Process(FileBlock* _block){

			Result* result = NULL;

			//Sync to FileSystem
			if(!Sync(_block->type(), _block->path(), _block->content())){

				result = new Result();

				assert(NULL != result);

				result->set_type(-1);

				result->set_errnum(errno);

				result->set_errmsg(strerror(errno));

				result->set_taskid(_block->taskid());

				Registry::Instance()->syncq()->Enqueue(result);

				Error("Sync to filesystem error: file=%s", _block->path().c_str());

				return false;


			}

			Note("TRACE Sync to FileSystem: path=%s", _block->path().c_str());

			//Recv conf file, Singal Reactor to run
			if(!_block->type().compare("conf")){

				int len = _block->path().size();

				string buf = _block->path();

				//Write to Pipe
				if(write(outfd_, &len, sizeof(int)) < 0 ||

					write(outfd_, buf.c_str(), buf.size()) < 0){

					Note("Write to Pipe-=-=-=-=-=-: outfd=%d", outfd_);

					result = new Result();

					assert(NULL != result);

					result->set_type(-1);

					result->set_errnum(errno);

					result->set_errmsg(strerror(errno));

					result->set_taskid(_block->taskid());

					Registry::Instance()->syncq()->Enqueue(result);

					Error("Write to Pipe failed: pipefd=%d, errmsg=%s", outfd_, strerror(errno));

					return false;

				}

			}

			result = new Result();

			assert(NULL != result);

			result->set_type(-1);

			result->set_errnum(204);

			result->set_errmsg("File Transfer sucessfully!");

			result->set_taskid(_block->taskid());

			Registry::Instance()->syncq()->Enqueue(result);

			Trace("TRACE Write to Pipe: pipefd=%d, path=%s", outfd_, _block->path().c_str());

			return true;



		}//Process

	}//Logic

}//PWRD

/*
 *  @protected	
 */

/*
   bool FileSink::Prepare(const string& _path){

   if(!_path.compare("")){ 

   return false;

   }

   if('/' == _path[_path.size()-1]){


   filedef_.path = _path;

   filedef_.path[_path.size() - 1] = 0;

   }

   return true;

   }

   bool FileSink::Create(const string& _path, const string& _name){

   if(!_path.compare("") || !_name.compare("")){

   return false;

   }

   string file = _path + "/" + _name;


   int fd = -1;

   if((fd = open(file.c_str(), O_CREAT | O_TRUNC, filedef_.mode) ) < 0){

   Error("Open file error: errmsg=%s", strerror(errnum));

   return false;

   }

   close(fd);

   return true;

   }

   bool FileSink::Append(const string& _content){

   int fd = -1;

   string file = filedef_.path + "/" + filedef_.name;


   if( (fd = open(file.c_str(), O_CREAT | O_APPEND | O_WRONLY, filedef_.mode) ) < 0){

   Error("Open file error: errmsg=%s", strerror(errnum));

   return false;

   }


   if( (write(fd, _content.c_str(), _content.size())) < 0 ){

   Error("Write File failed!:");

   return false;

}

close(fd);

return true;


}

bool FileSink::Checksum(const string& _path){

	char sum[32];
	*sum = 0;

	md5sum(_path.c_str(), sum, 1);

	if(!filedef_.md5sum.compare(sum)){

		logs.write_log(DEBUG, "");

		return true;
	}

	//error_.set_errnum(EMD5SUM);

	logs.write_log(NORMAL, "md5sum error!");

	return false;


}


bool FileSink::Checkoff(const string& _path){

	struct stat sb;

	if(-1 == stat(_path.c_str(), &sb)){


		//error_.set_errnum(errnum);

		logs.write_log(NORMAL, "stat error!");

		return false;

	}

	if(filedef_.offset != sb.st_size){

		logs.write_log(NORMAL, "offset doesn't match");

		//error_.set_errnum(EOFFSET);

		return false;


	}

	return true;

}
*/
