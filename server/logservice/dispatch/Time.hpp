#ifndef __TIMENOW_HPP
#define __TIMENOW_HPP

namespace PWRD{

	namespace Timekit{

		class Now{

			typedef enum{

				TIMELEN = 50

			}TIMELENGTH;

			public:
				void operator()(string& _now){

					char buffer[TIMELEN];

					struct tm now_tm;

					time_t now = time(NULL);

					size_t pos = strftime(buffer, sizeof(buffer)-1, "%Y-%m-%d %H:%M:%S ", localtime_r(&now, &now_tm));

					buffer[pos] = 0;

					_now.assign(buffer);

					Trace("TRACE Current time=%s", _now.c_str());

				}
		};

	}

}

#endif
