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
		Matrix MultMatrixRecurse(const Matrix &A, const Matrix &B);

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
		Matrix operator=(const Matrix &m);
		/*Matrix operator=(const Matrix &m)const;*/

		Matrix operator+(Matrix B);
		Matrix operator-(Matrix B);

		Matrix operator*(const Matrix &B);
		bool operator==(const Matrix &B);

		void print();
		void print()const;
		void fill(int limit = 10, int offset = 0);

		const Matrix Cut(int x1, int y1, int x2, int y2) const;
		Matrix<MType> Cut(Point left_up, Point right_down);

		Matrix Insert(const Matrix &Inp, int x1, int y1, int x2, int y2);

		Matrix ExpandTo(int rows, int cols);
		Matrix ExpandTo(int rows, int cols) const;

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

		string ToString();
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


	template<class MType> Matrix<MType> Matrix<MType>::operator=(const Matrix &m) {
		deleteMatrix();

		size1 = m.size1;
		size2 = m.size2;

		arr = new int*[size1];

		for (int i = 0; i < size1; i++) {
			arr[i] = new int[size2];

			for (int j = 0; j < size2; j++) {
				arr[i][j] = m[i][j];
			}
		}

		return *this;
	}


	template<class MType>Matrix<MType> Matrix<MType>::operator+(Matrix B) {
		if (B.IsEmpty()) {
			return *this;
		}
		if (size1 != B.size1 || size2 != B.size2) {
			Matrix C(1, 1);
			C[0][0] = 0;
			return C;
		}

		Matrix C(size1, size2);

		for (int x = 0; x < size1; x++) {
			for (int y = 0; y < size2; y++) {
				C[x][y] = arr[x][y] + B[x][y];
			}
		}

		return C;
	}

	template<class MType>Matrix<MType> Matrix<MType>::operator-(Matrix B) {
		if (B.IsEmpty()) {
			return *this;
		}
		if (size1 != B.size1 || size2 != B.size2) {
			Matrix C(1, 1);
			C[0][0] = 0;
			return C;
		}

		Matrix C(size1, size2);

		for (int x = 0; x < size1; x++) {
			for (int y = 0; y < size2; y++) {
				C[x][y] = arr[x][y] - B[x][y];
			}
		}

		return C;
	}


	template<class MType> Matrix<MType> Matrix<MType>::operator*(const Matrix &B) {
		if (this->size1 != B.size2 || this->size2 != B.size1) {
			cout << "Incorrect sizes\n";
			return Matrix(0, 0);
		}

		int power = (double)log2(size1) != (int)log2(size1) ? ceil((double)log2(size1)) :
			(double)log2(size2) != (int)log2(size2) ? ceil((double)log2(size2)) :
			(double)log2(B.size1) != (int)log2(B.size1) ? ceil((double)log2(B.size1)) :
			(double)log2(B.size2) != (int)log2(B.size2) ? ceil((double)log2(B.size2)) : 0;


		if (power != 0) {

			Matrix a = *this;
			Matrix b = B;

			a = a.ExpandTo(pow(2, power), pow(2, power));
			b = b.ExpandTo(pow(2, power), pow(2, power));

			Matrix c = MultMatrixRecurse(a, b);
			c = c.Cut(0, 0, this->size1 - 1, B.size2 - 1);
			return c;
		}
	}

	template<class MType> bool Matrix<MType>::operator==(const Matrix &B) {
		if (size1 != B.size1 || size2 != B.size2) {
			return false;
		}

		for (int i = 0; i < size1; i++) {
			for (int j = 0; j < size2; j++) {
				if (arr[i][j] != B[i][j]) {
					return false;
				}
			}
		}

		return true;
	}

	template<class MType> Matrix<MType> Matrix<MType>::Insert(const Matrix &source, int x1, int y1, int x2, int y2) {
		if (x1 < 0 || x1 >= size2) {
			/*cout << "Wrong point 1 (x)\n\n";*/
			return *this;
		}
		else if (x2 < 0 || x2 >= size2) {
			/*cout << "Wrong point 2 (x)\n\n";*/
			return *this;
		}
		else if (y1 < 0 || y1 >= size1) {
			/*cout << "Wrong point 1 (y)\n\n";*/
			return *this;
		}
		else if (y2 < 0 || y2 >= size1) {
			/*cout << "Wrong point 2 (y)\n\n";*/
			return *this;
		}

		if (source.IsEmpty()) {
			return *this;
		}
		if (source.size1 == 0 || source.size2 == 0) {
			return  *this;
		}

		Matrix inputed = *this;
		for (int y = y1, i = 0; y <= y2; y++, i++) {
			for (int x = x1, j = 0; x <= x2; x++, j++) {
				inputed[y][x] = source[i][j];
			}
		}

		return inputed;
	}

	template<class MType> Matrix<MType> Matrix<MType>::ExpandTo(int rows, int cols) {
		if (rows > size1 && cols > size2) {

			Matrix C(rows, cols);

			C.fill(1, 0);

			C = C.Insert(*this, 0, 0, size2 - 1, size1 - 1);

			return C;
		}

		return *this;
	}
	template<class MType> Matrix<MType> Matrix<MType>::ExpandTo(int rows, int cols) const {
		if (rows > size1 && cols > size2) {

			Matrix C(rows, cols);

			C.fill(1, 0);

			C = C.Insert(*this, 0, 0, size2 - 1, size1 - 1);

			return C;
		}

		return *this;
	}

	template<class MType>string Matrix<MType>::ToString() {
		string str = "";

		for (int i = 0; i < size1; i++) {
			for (int j = 0; j < size2; j++) {
				str.append(to_string(arr[i][j]));
				str += " ";
			}

			if (i != size1 - 1)
				str += "\n";
		}

		return str;
	}

	template<class MType> Matrix<MType> Matrix<MType>::MultMatrixRecurse(const Matrix &A, const Matrix &B) {
		//Если передана матрицы 1x1, то возвращаем обычное произведение
		if (A.size1 == 1 && A.size2 == 1 && B.size1 == 1 && B.size2 == 1) {
			Matrix C(1, 1);
			C[0][0] = A[0][0] * B[0][0];
			return C;
		}
		else {

			//Создаем матрицы для хранения подрезультатов
			/*Matrix C11 = C.Cut(0, 0, floor((double)(C.size2 - 1) / 2), floor((double)(C.size1 - 1) / 2));
			Matrix C12 = C.Cut(ceil((double)(C.size2) / 2), 0, C.size2 - 1, floor((double)(C.size1 - 1) / 2));
			Matrix C21 = C.Cut(0, ceil((double)C.size1 / 2), floor((double)(C.size2 - 1) / 2), C.size1 - 1);
			Matrix C22 = C.Cut(ceil((double)C.size2 / 2), ceil((double)C.size1 / 2), C.size2 - 1, C.size1 - 1);*/

			//Делим матрицу A
			Matrix A11 = A.Cut(0, 0, floor((double)(A.size2 - 1) / 2), floor((double)(A.size1 - 1) / 2));
			/*cout << "A11:\n";  A11.print(); cout << "\n";*/

			Matrix A12 = A.Cut(ceil((double)(A.size2) / 2), 0, A.size2 - 1, floor((double)(A.size1 - 1) / 2));
			/*cout << "A12:\n";  A12.print(); cout << "\n";*/

			Matrix A21 = A.Cut(0, ceil((double)A.size1 / 2), floor((double)(A.size2 - 1) / 2), A.size1 - 1);
			/*cout << "A21:\n";  A21.print(); cout << "\n";*/

			Matrix A22 = A.Cut(ceil((double)A.size2 / 2), ceil((double)A.size1 / 2), A.size2 - 1, A.size1 - 1);
			/*cout << "A22:\n";  A22.print(); cout << "\n";*/


			//Делим матрицу B
			Matrix B11 = B.Cut(0, 0, floor((double)(B.size2 - 1) / 2), floor((double)(B.size1 - 1) / 2));
			/*cout << "B11:\n";  B11.print(); cout << "\n";*/

			Matrix B12 = B.Cut(ceil((double)B.size2 / 2), 0, B.size2 - 1, floor((double)(B.size1 - 1) / 2));
			/*cout << "B12:\n";  B12.print(); cout << "\n";*/

			Matrix B21 = B.Cut(0, ceil((double)B.size1 / 2), floor((double)(B.size2 - 1) / 2), B.size1 - 1);
			/*cout << "B21:\n";  B21.print(); cout << "\n";*/

			Matrix B22 = B.Cut(ceil((double)B.size2 / 2), ceil((double)B.size1 / 2), B.size2 - 1, B.size1 - 1);
			/*cout << "B22:\n";  B22.print(); cout << "\n";*/


			//Вычисляем S-матрицы
			/*Matrix S1 = B12 - B22;
			Matrix S2 = A11 + A12;
			Matrix S3 = A21 + A22;
			Matrix S4 = B21 - B11;
			Matrix S5 = A11 + A22;
			Matrix S6 = B11 + B22;
			Matrix S7 = A12 - A22;
			Matrix S8 = B21 + B22;
			Matrix S9 = A11 - A21;
			Matrix S10 = B11 + B12;*/

			//Вычисляем P-матрицы
			Matrix P1 = MultMatrixRecurse(A11, B12 - B22);
			Matrix P2 = MultMatrixRecurse(A11 + A12, B22);
			Matrix P3 = MultMatrixRecurse(A21 + A22, B11);
			Matrix P4 = MultMatrixRecurse(A22, B21 - B11);
			Matrix P5 = MultMatrixRecurse(A11 + A22, B11 + B22);
			Matrix P6 = MultMatrixRecurse(A12 - A22, B21 + B22);
			Matrix P7 = MultMatrixRecurse(A11 - A21, B11 + B12);

			/*Matrix P1 = MultMatrixRecurse(A11, S1);
			Matrix P2 = MultMatrixRecurse(S2, B22);
			Matrix P3 = MultMatrixRecurse(S3, B11);
			Matrix P4 = MultMatrixRecurse(A22, S4);
			Matrix P5 = MultMatrixRecurse(S5, S6);
			Matrix P6 = MultMatrixRecurse(S7, S8);
			Matrix P7 = MultMatrixRecurse(S9, S10);*/

			//Считаем результат
			/*C11 = P5 + P4 - P2 + P6;
			C12 = P1 + P2;
			C21 = P3 + P4;
			C22 = P5 + P1 - P3 - P7;*/


			//Собираем конечный результат
			Matrix C(A.size1, B.size2);
			C = C.Insert(P5 + P4 - P2 + P6, 0, 0, floor((double)(C.size2 - 1) / 2), floor((double)(C.size1 - 1) / 2));
			C = C.Insert(P1 + P2, ceil((double)(C.size2) / 2), 0, C.size2 - 1, floor((double)(C.size1 - 1) / 2));
			C = C.Insert(P3 + P4, 0, ceil((double)C.size1 / 2), floor((double)(C.size2 - 1) / 2), C.size1 - 1);
			C = C.Insert(P5 + P1 - P3 - P7, ceil((double)C.size2 / 2), ceil((double)C.size1 / 2), C.size2 - 1, C.size1 - 1);

			/*C = C.Input(C11, 0, 0, floor((double)(C.size2 - 1) / 2), floor((double)(C.size1 - 1) / 2));
			C = C.Input(C12, ceil((double)(C.size2) / 2), 0, C.size2 - 1, floor((double)(C.size1 - 1) / 2));
			C = C.Input(C21, 0, ceil((double)C.size1 / 2), floor((double)(C.size2 - 1) / 2), C.size1 - 1);
			C = C.Input(C22, ceil((double)C.size2 / 2), ceil((double)C.size1 / 2), C.size2 - 1, C.size1 - 1);*/

			/*cout << "C:\n"; C.print(); cout << "\n";*/

			return C;
		}
	}


	template<class MType> std::once_flag Matrix<MType>::initRand;
}