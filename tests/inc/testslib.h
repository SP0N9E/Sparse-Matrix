/**
 * This file is part of the SparseMatrix library
 *
 * @license  MIT
 * @author   Petr Kessler (https://kesspess.cz)
 * @link     https://github.com/uestla/Sparse-Matrix
 */

#ifndef __TESTSLIB_H__

	#define	__TESTSLIB_H__

	#include <string>
	#include <vector>
	#include <cstring>
	#include <sstream>
	#include <iostream>
	#include <typeinfo>
	#include <exception>

	using namespace std;


	class FailureException : public exception
	{

		public:

			FailureException(const string & message) : exception(), message(message)
			{}


			virtual ~FailureException(void) throw ()
			{}


			inline string getMessage(void) const
			{
				return this->message;
			}


		protected:

			string message;

	};


	void assertException(const char * exceptionClass, void (*callback)(void))
	{
		try {
			callback();

		} catch (const exception & e) {
			string actualClass(typeid(e).name());

			if (strstr(actualClass.c_str(), exceptionClass) == NULL) {
				ostringstream oss;
				oss << "Exception class '" << exceptionClass << "' expected, but '" << actualClass << "' thrown.";

				throw FailureException(oss.str());
			}

			return ;
		}

		throw FailureException("Exception expected but none thrown.");
	}


	template<typename T>
	void assertEquals(const T & a, const T & b, const char * message = NULL)
	{
		if (!(a == b)) {
			ostringstream oss;
			if (message == NULL) {
				oss << "Objects not equal when they should be." << endl;

			} else {
				oss << message << endl;
			}

			oss << a << endl << "expected, but" << endl << b << " given";
			throw FailureException(oss.str());
		}
	}


	template<typename X, typename Y>
	void assertEquals(const X & a, const Y & b, const char * message = NULL)
	{
		if (!(a == b)) {
			ostringstream oss;
			if (message == NULL) {
				oss << "Objects not equal when they should be." << endl;

			} else {
				oss << message << endl;
			}

			oss << a << endl << "expected, but" << endl << b << " given";
			throw FailureException(oss.str());
		}
	}

#endif
