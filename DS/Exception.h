#pragma once

#ifndef EXCEPTION_H
#define EXCEPTION_H
#include <string>

using namespace std;

namespace MyLib {
	class Exception
	{
		string error;

	public:
		Exception();
		Exception(string err);
		~Exception();

		//Получение ошибки
		string getError() {
			return error;
		}
	};
}
#endif
