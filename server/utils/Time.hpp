#ifndef __TIME_HPP
#define __TIME_HPP

#include <Global.hpp>

#define DATETIME_SIZE 20

namespace PWRD{

	namespace Utils{

		class Time{

			public:

				static time_t GetNow(){

					struct timeval t;

					gettimeofday(&t, NULL);

					return t.tv_sec;
				}

				static string Now(){

					char timer[DATETIME_SIZE];

					time_t timep;

					struct tm times;

					bzero(timer, DATETIME_SIZE);

					timep = time(NULL);

					localtime_r(&timep, &times);

					sprintf(timer, "%d-%02d-%02d %02d:%02d:%02d", \

						(times.tm_year+1900), (times.tm_mon+1), times.tm_mday, \

						times.tm_hour, times.tm_min, times.tm_sec);

					return string(timer, DATETIME_SIZE);

				} //Now


		};  //Time

	}; //Utils

} //PWRD

#endif
