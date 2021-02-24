#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>
#include <mutex>

using namespace std;

namespace MyLib {
	struct Point {
		int x, y;
	};

	template<class MType> class Matrix {

		//Указатель на массив и его размеры
		MType **arr;
		int size1;
		int size2;

		//Функция для очищения памяти
		void deleteMatrix() {
			for (int i = 0; i < size1; i++) {
				delete[]arr[i];
			}
			delete[]arr;
		}

		////Функция умножения матриц методом Штрассена
		//Matrix MultMatrixRecurse(const Matrix &A, const Matrix &B);

		//Флаг для однократной инициализации генератора случ. чисел
		static std::once_flag initRand;

	public:

		//Конструкторы
		Matrix();
		Matrix(int s1, int s2);
		Matrix(const Matrix &m);

		~Matrix();

		

		MType* operator[](const int i) {
			return arr[i];
		}
		const MType* operator[](const int i) const {
			return arr[i];
		}
		//Matrix operator=(const Matrix &m);
		///*Matrix operator=(const Matrix &m)const;*/

		//Matrix operator+(Matrix B);
		//Matrix operator-(Matrix B);

		//Matrix operator*(const Matrix &B);
		//bool operator==(const Matrix &B);

		void print();
		void print()const;
		void fill(int limit = 10, int offset = 0);

		const Matrix Cut(int x1, int y1, int x2, int y2) const;
		Matrix<MType> Cut(Point left_up, Point right_down);

		/*Matrix Insert(const Matrix &Inp, int x1, int y1, int x2, int y2);*/

		/*Matrix ExpandTo(int rows, int cols);
		Matrix ExpandTo(int rows, int cols) const;*/

		bool IsEmpty() {
			return size1 == 0 || size2 == 0;
		}
		bool IsEmpty() const {
			return size1 == 0 || size2 == 0;
		}

		int getS1() {
			return size1;
		}
		int getS2() {
			return size2;
		}

		/*string ToString();*/
		Matrix Reshape(int s1, int s2);
		Matrix Reshape(int s1, int s2)const;

		static Matrix dot(const Matrix &A, const Matrix &B);
		
		
		Matrix dot(const Matrix<MType> &B);
	};



	template<class MType> Matrix<MType>::Matrix(int s1, int s2) {

		std::call_once(initRand, [this] {srand(time(NULL)); });

		size1 = s1;
		size2 = s2;
		arr = new MType*[s1];

		for (int i = 0; i < s1; i++) {
			arr[i] = new MType[s2];
		}
	}

	template<class MType> Matrix<MType>::Matrix() {
		std::call_once(initRand, [this] {srand(time(NULL)); });
		size1 = 0;
		size2 = 0;
		arr = NULL;
	}

	template<class MType> Matrix<MType>::Matrix(const Matrix &m) {

		std::call_once(initRand, [this] {srand(time(NULL)); });

		size1 = m.size1;
		size2 = m.size2;

		arr = new MType*[size1];

		for (int i = 0; i < size1; i++) {
			arr[i] = new MType[size2];

			for (int j = 0; j < size2; j++) {
				arr[i][j] = m[i][j];
			}
		}
	}


	template<class MType> Matrix<MType>::~Matrix() {
		deleteMatrix();
	}

	template<class MType> void Matrix<MType>::print() {
		for (int i = 0; i < size1; i++) {
			for (int j = 0; j < size2; j++)
				cout << arr[i][j] << ' ';
			cout << '\n';
		}
		cout << '\n';
	}

	template<class MType> void Matrix<MType>::print() const {
		for (int i = 0; i < size1; i++) {
			for (int j = 0; j < size2; j++)
				cout << arr[i][j] << ' ';
			cout << '\n';
		}
		cout << '\n';
	}

	template<class MType> void Matrix<MType>::fill(int limit, int offset) {

		for (int i = 0; i < size1; i++) {
			for (int j = 0; j < size2; j++) {
				arr[i][j] = rand() % limit + offset;
			}
		}
	}

	template<class MType> static Matrix<MType> Matrix<MType>::dot(const Matrix &A, const Matrix &B) {

		if (A.size1 != B.size2 || A.size2 != B.size1) {
			cout << "Wrong sizes\n\n";
			Matrix C(0, 0);
			return C;
		}
		Matrix C(A.size1, B.size2);


		for (int i = 0; i < A.size1; i++) {

			for (int j = 0; j < B.size2; j++) {

				C[i][j] = 0;

				for (int k = 0; k < A.size2; k++) {
					C[i][j] += A[i][k] * B[k][j];
				}
			}
		}
	}


	template<class MType> Matrix<MType> Matrix<MType>::dot(const Matrix<MType> &B) {
			if (size1 != B.size2 || size2 != B.size1) {
			cout << "Wrong sizes\n\n";
			Matrix C(0, 0);
			return C;
		}

		Matrix C(size1, B.size2);


		for (int i = 0; i < size1; i++) {

			for (int j = 0; j < B.size2; j++) {

				C[i][j] = 0;

				for (int k = 0; k < size2; k++) {
					C[i][j] += arr[i][k] * B[k][j];
				}
			}
		}

		return C;
	}


	template<class MType> const Matrix<MType> Matrix<MType>::Cut(int x1, int y1, int x2, int y2) const {
			if (x1 < 0 || x1 >= size2) {
			/*cout << "Wrong point 1 (x)\n\n";*/
			return Matrix(0, 0);
		}
		else if (x2 < 0 || x2 >= size2) {
			/*cout << "Wrong point 2 (x)\n\n";*/
			return Matrix(0, 0);
		}
		else if (y1 < 0 || y1 >= size1) {
			/*cout << "Wrong point 1 (y)\n\n";*/
			return Matrix(0, 0);
		}
		else if (y2 < 0 || y2 >= size1) {
			/*cout << "Wrong point 2 (y)\n\n";*/
			return Matrix(0, 0);

		}

		Matrix cuted(y2 - y1 + 1, x2 - x1 + 1);

		for (int y = y1, i = 0; y <= y2; y++, i++) {
			for (int x = x1, j = 0; x <= x2; x++, j++) {
				cuted[i][j] = this->arr[y][x];
			}
		}

		return cuted;
	}

	template<class MType> Matrix<MType> Matrix<MType>::Cut(Point left_up, Point right_down) {
			if (left_up.x < 0 || left_up.x >= size2) {
			cout << "Wrong point 1 (x)\n\n";
			Matrix<MType> C(1, 1);
			C[0][0] = 0;
			
			return C;
		}
		else if (right_down.x < 0 || right_down.x >= size2) {
			cout << "Wrong point 2 (x)\n\n";
			Matrix C(1, 1);
			C[0][0] = 0;
			return C;
		}
		else if (left_up.y < 0 || left_up.y >= size1) {
			cout << "Wrong point 1 (y)\n\n";
			Matrix C(1, 1);
			C[0][0] = 0;
			return C;
		}
		else if (right_down.y < 0 || right_down.y >= size1) {
			cout << "Wrong point 2 (y)\n\n";
			Matrix C(1, 1);
			C[0][0] = 0;
			return C;
		}
	
		Matrix cuted(right_down.y - left_up.y + 1, right_down.x - left_up.x + 1);
	
		for (int y = left_up.y, i = 0; y <= right_down.y; y++, i++) {
			for (int x = left_up.x, j = 0; x <= right_down.x; x++, j++) {
				cuted[i][j] = this->arr[y][x];
			}
		}
	
		return cuted;
	}


	template<class MType> Matrix<MType> Matrix<MType>::Reshape(int s1, int s2) {
		Matrix C(s1, s2);
	
		int *a = new int[size1 * size2];
	
		for (int i = 0; i < size1; i++) {
			for (int j = 0; j < size2; j++) {
				a[i * size2 + j] = arr[i][j];
			}
		}
	
		for (int i = 0; i < s1; i++) {
			for (int j = 0; j < s2; j++) {
				C[i][j] = a[i * s2 + j];
			}
		}
	
		delete[]a;
	
		return C;
	}

	template<class MType> Matrix<MType> Matrix<MType>::Reshape(int s1, int s2)const {
		Matrix C(s1, s2);
	
		int *a = new int[size1 * size2];
	
		for (int i = 0; i < size1; i++) {
			for (int j = 0; j < size2; j++) {
				a[i * size2 + j] = arr[i][j];
			}
		}
	
		for (int i = 0; i < s1; i++) {
			for (int j = 0; j < s2; j++) {
				C[i][j] = a[i * s2 + j];
			}
		}
	
		delete[]a;
	
		return C;
	}

	/*std::once_flag Matrix<class MType>::initRand;*/
}