#pragma once
#include <string>

using namespace std;

namespace MyLib {
	class XExecption
	{
		string error;

	public:
		XExecption();
		XExecption(string err);
		~XExecption();
	};
}
