#include "pch.h"
#include "Matrix.h"
#include <iostream>

using namespace std;
using namespace MyLib;

std::once_flag Matrix<int>::initRand;

int main()
{
	Matrix<int> A(5, 5);

	A[0][0] = 1;
	A.fill();

	A.print();

	cout << endl;

	Matrix<int> B = Matrix<int>(5, 5);

	B.fill();

	B.print();

	return 0;
}
