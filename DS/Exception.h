#pragma once
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

		//��������� ������
		string getError() {
			return error;
		}
	};
}
