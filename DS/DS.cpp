#include "pch.h"
#include "Matrix.h"
#include "Array.h"

#include <iostream>

using namespace std;
using namespace MyLib;


int main()
{

	Array<int> arr(5);
	cout << arr.getLength() << endl;

	for (int i = 0; i < arr.getLength(); i++) {
		cin >> arr[i];
	}

	for (int i = 0; i < arr.getLength(); i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;

	//Конструктор копий
	Array<int> arr2 = arr;
	for (int i = 0; i < arr2.getLength(); i++) {
		cout << arr2[i] << ' ';
	}
	cout << endl;


	//Оператор =
	arr2[3] = 101;
	arr = arr2;
	for (int i = 0; i < arr.getLength(); i++) {
		cout << arr[i] << ' ';
	}
	cout << endl;

	//Оператор []
	/*try {
		arr[-1] = 99;
	}
	catch (Exception ex) {
		cout << ex.getError().c_str() << endl;
	}

	for (int i = 0; i < arr.getLength(); i++) {
		cout << arr[i] << ' ';
	}*/

	//Проверка изменения размера
	arr.resize(5);
	arr2.resize(5);
	cout << arr;

	cout << endl;

	cout << arr << arr2;
	
	Array<double> arr3 = 77.5 + arr;
	cout << arr3;

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
