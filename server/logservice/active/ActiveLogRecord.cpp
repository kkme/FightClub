#include <ActiveLogRecord.hpp>

namespace PWRD{

	namespace ActiveObject{


		int ActiveLogRecord::Log(int _type, string _server, string _process, string _message){

			Trace("TRACE ActiveLogRecord Persistance");



			//write to file
			//get timestamp
			string t;

			Now now; now(t);


			string day = t.substr(0, 10);

			FileService::Makedir(day);


			//find the file
			int fd = FileService::Find(_type);

			if(fd < 0){
				
				Error("Can't find the type of log, and debug doesn't open: type=%d", _type);

				return -1;
			}


			//concate the string
			//eg.: timestamp server process log
			t  = t + " " + _server + " " + _process + " " + _message;

			//write
			//return FileService::Write(fd, _message.c_str(), _message.size());
			return FileService::Write(fd, t.c_str(), t.size());

		}

	}

}
