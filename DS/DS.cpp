#include "pch.h"
#include "Matrix.h"
#include "Array.h"

#include <iostream>

using namespace std;
using namespace MyLib;

bool f(int a, int b) {
	return a < b;
}

int main()
{
	
	Array<double> arr(5);

	cin >> arr;

	cout << arr.getLength() << arr << endl;

	Array<int> arr2 = arr;
	cout << arr2.getLength() << arr2;


	//for (int i = 0; i < arr.getLength(); i++) {
	//	cout << arr[i] << ' ';
	//}
	//cout << endl;

	////Конструктор копий
	//Array<int> arr2 = arr;
	//for (int i = 0; i < arr2.getLength(); i++) {
	//	cout << arr2[i] << ' ';
	//}
	//cout << endl;


	////Оператор =
	//arr2[3] = 101;
	//arr = arr2;
	//for (int i = 0; i < arr.getLength(); i++) {
	//	cout << arr[i] << ' ';
	//}
	//cout << endl;

	//cout << arr;
	///*arr.MergeSort();*/
	//cout << arr.SubArray(1, 3) << arr;
	


	/*Matrix<int> A(5, 5);

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

	
	C.print();*/

	return 0;
}
