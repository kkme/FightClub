#ifndef __LOGSERVICE_HEAD_HPP
#define __LOGSERVICE_HEAD_HPP

#include <FightClub.pb.h>

#include <Daemon.hpp>

#include <Global.hpp>

using namespace PWRD;

namespace PWRD{

	typedef struct{

		TYPE type;

		int length;

		int version;

	}Head;

#define HEADLEN sizeof(Head)

	class HeadImpl{

		public:

			static int CheckProtocol(Head&);
	};

}

#endif
