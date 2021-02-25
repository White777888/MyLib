#include "pch.h"
#include "Matrix.h"
#include <iostream>

using namespace std;
using namespace MyLib;


int main()
{
	Matrix<int> A(5, 5);

	try {
		A[0][0] = 1;
	}
	catch(...){
		cout << "Error!\n";
		exit(1);
	}

	A.fill();

	A.print();

	cout << endl;

	Matrix<int> B = Matrix<int>(5, 5);

	B.fill();

	B.print();

	cout << endl;

	Matrix<int> C = A + B;

	A = A.Reshape(1, 25);
	A.print();

	cout << endl;

	
	C.print();

	return 0;
}
