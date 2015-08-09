#ifndef __LOGSERVICE_HEAD_HPP
#define __LOGSERVICE_HEAD_HPP

#include <Daemon.hpp>

#include <Global.hpp>

#include <Monitor.pb.h>

using namespace PWRD;

namespace PWRD{
	
		typedef struct{

			TYPE type;

			long length;

			float version;

		}Head;
		
#define HEADLEN sizeof(Head)

		class HeadImpl{

			public:

				static int CheckProtocol(Head&);
		};

}

#endif
