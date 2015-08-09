/****************************************************************************
 * Speed socket's reactor library
 * Copyright (c) 2008 by Huang RuiGuang(jiangrg1981@gmail.com)
 *
 * Permission to use, copy, modify, distribute and sell this software.
 *****************************************************************************/

#ifndef __EXCEPTION_H
#define __EXCEPTION_H

#include <exception>
#include <string>

namespace PWRD{

	namespace Event{

		class Exception : public std::exception {

			public:

				Exception(const std::string& msg);

				virtual ~Exception() throw();

				virtual const char* what() const throw();

			private:

				std::string msg_;

		};  
	}
}

#endif

