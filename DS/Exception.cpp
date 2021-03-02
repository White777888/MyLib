#include "pch.h"
#include "Exception.h"

using namespace MyLib;

Exception::Exception()
{
	error = "Unknown ex";
}

Exception::Exception(string err) {
	error = err;
}

Exception::~Exception()
{
}
