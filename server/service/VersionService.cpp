#include <VersionService.hpp>

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
		int VersionService::Process(boost::shared_ptr<C2S_Version> _item UNUSED, EventHandler* _handler){

			boost::shared_ptr<S2C_Version> response(new S2C_Version());

			Conf* conf = Conf::GetInstance();

			string version = conf->find("Version", "version");

			//Check Version
			if(!_item->version().compare(version)){

				//Note("Version is up to date: uuid=%s", _item->uuid().c_str());

				Note("Version is up to date: server=%s, remote=%s", version.c_str(),  _item->version().c_str());

				response->set_match(true);


			}
			else{

				Note("Version Out Of Time!");

				response->set_match(false);

				boost::shared_ptr<Vector> dirs(new Vector());

				LookDir(dirs);

				Vector* vector = dirs.get();

				Vector::iterator it = vector->begin();

				for(; it != vector->end(); it++){
				
					File* file = response->add_flist();

					ReadFile((*it).get(), file);

					Note("=====================READFILE===================");
					

				}//for

			}

			//Send
			Head head;

			head.type = VERSION;

			head.version = 1;

			head.length = response->ByteSize();

			char* buf = new char[head.length];

			*buf = 0;

			response->SerializeToArray(buf, head.length);

			if(ESTABLISHED == _handler->Connected()){

				_handler->Send(head, buf, head.length);
			
			}
			else{

				Error("Connection lost, Packet can't be sent");
			
			}

			delete buf;

			return 1;


		}

		void VersionService::LookDir(boost::shared_ptr<Vector> _list){
		
			Conf* conf = Conf::GetInstance();

			string path = conf->find("Version", "path");

			Note("Version Service: path=%s", path.c_str());

			DIR *d;

			struct dirent *dir;

			if(NULL == (d = opendir(path.c_str()))){
			
				Note("Not a Directory: path=%s", path.c_str());

				return;

			}

			while(NULL != (dir = readdir(d))){

				if(strncmp(dir->d_name, ".", 1) == 0){
				
					continue;

				}

				string str;

				str.assign(dir->d_name);

				str = path + "/" + str;

				boost::shared_ptr<string> dirstr(new string(str));

				Note("File List: file=%s", str.c_str());

				_list->push_back(dirstr);
			

			}

			return;


		}

		void VersionService::ReadFile(const string* _name, File* _file){

			Trace("TRACE Read File: file=%s", _name->c_str());

			//Load file
			int fd = open(_name->c_str(), FLAGS, MODE );

			if(fd < 0){

				Error("Can't open this file: errno=%d, errmsg=%s", errno, strerror(errno));

				return ;

			}

			char buf[BUFSIZ];

			int len = read(fd, buf, BUFSIZ);

			if(len < 0){

				Error("Read file failed: errno=%d, errmsg=%s", errno, strerror(errno));

				return ;

			}

			buf[len] = 0;

			Note("Read File: file=%s, len=%d", _name->c_str(), len);

			close(fd);

			string content(buf, len);

			_file->set_match(false);

			_file->set_path(*_name);

			_file->set_content(content);

			_file->set_md5sum("=================");

		}//ReadFile

	}//FC

}//PWRD
