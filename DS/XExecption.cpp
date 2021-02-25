#include "pch.h"
#include "XExecption.h"

using namespace MyLib;

XExecption::XExecption()
{
	error = "Unknown ex";
}

XExecption::XExecption(string err) {
	error = err;
}

XExecption::~XExecption()
{
}
