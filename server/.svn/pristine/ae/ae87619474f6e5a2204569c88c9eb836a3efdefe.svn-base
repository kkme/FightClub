#include <FileService.hpp>

namespace PWRD{

	namespace Persist{

		/*
		   @static members
		   */
		FileMap FileService::fmap_;

		FileMap FileService::dmap_;

		NameMap FileService::nmap_;

		bool FileService::debug_ = true;

		string  FileService::file_ = "";

		string  FileService::root_ = "";

		string  FileService::day_ = "";

		int FileService::debugfd_ = 0;

		FileService* FileService::instance_ = NULL;

		/*
		   @public
		   */

		FileService* FileService::Instance(string& _file){

			file_ = _file;

			Trace("TRACE FileService Instance: conf=%s", _file.c_str());

			if(NULL == instance_){

				instance_ = new FileService();;


			}

			return instance_;

		}


		int FileService::Load(){

			Trace("TRACE FileService Load: file=%s", file_.c_str());


			if(Cont() < 0){

				Error("Load conf failed!");

				return -1;

			}

			return 1;

		}

		int FileService::Find(int _type){

			if(fmap_.find(_type) == fmap_.end()){

				//Error("ERROR Can't find file: type=%d, write to debug", _type);
				//define debug
				if(debug_) return debugfd_;

				return 0;
			}

			Trace("TRACE LogRecord: type=%d  <===> fd=%d", _type, dmap_[fmap_[_type]]);

			return dmap_[fmap_[_type]];

		}

		int FileService::Makedir(string& _day){

			Trace("TRACE today=%s, tomorror=%s", day_.c_str(), _day.c_str());

			if(!day_.compare(_day)){

				Trace("TRACE the same day");

				return 0;

			}

			//Close prefile
			FileMap::const_iterator diter;

			if(dmap_.size() > 0){

				for(diter = dmap_.begin(); diter != dmap_.end(); diter++){

					if(diter->second > 0){

						close(diter->second);

						Trace("TRACE Close file: name=%s, fd=%d", 
								nmap_[diter->first].c_str(), diter->second );

					}

				}

			}

			//debug
			if(debugfd_ > 0){

				close(debugfd_);

			}

			day_ = _day;

			string path = root_ + "/" + day_ + "/";

			Trace("TRACE New directory: dir=%s", path.c_str());

			if(access(path.c_str(), F_OK) != 0){

				if(mkdir(path.c_str(), 0755) < 0){

					Error("Can't mkdir: dir=%s, errno=%d, errmsg=%s",
							path.c_str(), errno, strerror(errno));

					return -1;
				}
			}

			NameMap::const_iterator iter;

			for(iter = nmap_.begin(); iter != nmap_.end(); iter++){

				int key = iter->first;

				string file = path + iter->second;

				Trace("TRACE Open file: file=%s", file.c_str());

				int fd = open(file.c_str(), FLAGS, MODE );

				if(fd < 0){

					Error("Can't open file: file=%s, errno=%d, errmsg=%s",
							file.c_str(), errno, strerror(errno));

					return -1;
				}

				dmap_[key] = fd;

				Trace("TRACE Make pair: key=%d <===> fd=%d", key, fd);

			}

			//debug
			if(debug_){

				string debugfile = path + "debug";

				debugfd_ = open(debugfile.c_str(), FLAGS, MODE);

				if(debugfd_ < 0){

					Error("Can't open debug file: file=%s", debugfile.c_str());

					return -1;
				}
			}

			return 1;
		}

		int FileService::Write(int _fd, const char* _buf, int len){

			if(_fd < 0){
				
				Error("Bad file descriptor: fd=%d", _fd);

				return -1;
				
			}

			if(NULL == _buf || len < 0){
				
				Error("Bad log buffer");

				return -1;

			}

			Trace("TRACE Write file: fd=%d, buf=%p, len=%d", _fd, _buf, len);

			return write(_fd, _buf, len);
		}

		/*
		   @protected
		   */

		int FileService::init(){

			fmap_.clear();

			nmap_.clear();

			dmap_.clear();

			debug_ = true;

			Trace("TRACE FileService init");

			return 1;

		}

		int FileService::fini(){

			if(NULL != instance_){

				delete instance_;

				instance_ = NULL;
			}

			Trace("TRACE FileService fini");

			return 1;

		}

		/*
		   @private
		   */
		int FileService::Cont(){

			Conf* conf = Conf::GetInstance(file_.c_str());

			if(NULL == conf){

				Error("Conf GetInstance failed");

				return -1;

			}

			root_ = conf->find("logserver", "root");

			if(!root_.compare("")){

				root_ = "/export/logs";

			}

			Trace("TRACE Root dir: root=%s", root_.c_str());

			string debug = conf->find("logserver", "debug");

			if(!debug.compare("0")){

				debug_ = false;

			}

			Trace("TRACE Debug mode: debug=%d", debug_);

			//tkeys: transport  num ==> type
			//fkeys: logservice num ==> file

			Vector fkeys,  tkeys;

			conf->getkeys("logservice", fkeys);

			Trace("TRACE Logservice Keys: size=%d", fkeys.size());

			conf->getkeys("transport", tkeys);

			Trace("TRACE Transport Keys: size=%d", tkeys.size());


			//load to map

			Vector::const_iterator iter;

			for(iter = fkeys.begin(); iter != fkeys.end(); iter++){

				string value = conf->find("logservice", *iter);

				int key = 0;

				try{
					key = boost::lexical_cast<int>(*iter);
				}
				catch(boost::bad_lexical_cast& e){

					Error("Bad Lexical cast: key=%s, exception=%s", (*iter).c_str(), e.what());

					return -1;
				}

				nmap_[key] = value;

				Trace("TRACE Name Map: key=%d, file=%s", key, value.c_str());
			}

			for(iter = tkeys.begin(); iter != tkeys.end(); iter++){

				string value = conf->find("transport", *iter);

				typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

				boost::char_separator<char> sep(" ,;.|]-[");

				tokenizer tokens(value, sep);

				for(tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); tok_iter++){

					Trace("TRACE value=%s, key=%s", (*iter).c_str(), (*tok_iter).c_str());

					int key = 0;

					int num = 0;

					try{
						key = boost::lexical_cast<int>(*tok_iter);

						num = boost::lexical_cast<int>(*iter);

					}
					catch(boost::bad_lexical_cast& e){

						Error("Bad Lexical cast: key=%s, num=%s, exception=%s", (*tok_iter).c_str(), (*iter).c_str(), e.what());

						return -1;

					}

					fmap_[key] = num;

					Trace("TRACE File Map: key=%d, file=%s", key, value.c_str());

				}

			}

			return 1;


		}

	}

}
