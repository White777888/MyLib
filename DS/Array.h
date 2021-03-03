#pragma once
#include <iostream>
#include <ostream>
#include "Exception.h"

using namespace std;

namespace MyLib {
	//����� �������
	template<typename AType> class Array
	{
		AType *arr;
		long int length;

		//������� �������� �������
		void deleteArray() {
			if (length != 0) {
				delete[]arr;
			}
		}

	public:

		//������������
		Array();
		Array(long length);
		Array(const Array& a);

		//����������
		~Array();

		//������� ������� � �������
		long getLength() {
			return length;
		}

		//�������� ���������� �������
		AType& operator[](long i) {

			//� ������ ������ �� �������
			//����������� ����������
			if (i < 0 || i >= length) {
				throw Exception("Index was out of array's border");
			}

			return arr[i];
		}
		AType& operator[](long i)const {

			//� ������ ������ �� �������
			//����������� ����������
			if (i < 0 || i >= length) {
				throw Exception("Index was out of array's border");
			}

			return arr[i];
		}

		//������������� �������� ������������
		Array operator=(const Array &a);

		//������� ��������� �������
		void resize(long newsize);

		//�������� ������ ������� � ������ ������
		template<typename AType> friend ostream& operator<<(ostream &stream, const Array<AType> &A);

		//�������������� ��������� ��� ���������� ���������
		//+ ������
		template<typename VType> Array<AType> operator+(VType val);
		//+ Array
		Array operator+(const Array &A);
		//������ + Array 
		template<typename AType, typename VType> friend Array<VType> operator+(VType val, const Array<AType> &A);

		//+ ������
		template<typename VType> Array<AType> operator+=(VType val);
		//+ Array
		Array operator+=(const Array &A);
		
		//������� �����
		Array operator-();

		//��������� ���������
		bool operator==(const Array &A);
		bool operator!=(const Array &A);

		//�������� �������
		Array operator,(Array &A);

		//������� ����������

		
	};

	template<typename AType> Array<AType>::Array() {
		arr = NULL;
		length = 0;
	}

	template<typename AType> Array<AType>::Array(long length) {
		//��������� ������ ��� ������
		arr = new AType[length];
		this->length = length;
	}

	template<typename AType> Array<AType>::Array(const Array& a) {
		//������� ������� ������
		/*deleteArray();*/

		//����� �������� ������ ������ � ����� ��������
		arr = new AType[a.length];
		length = a.length;

		//����� �������� ������ ������
		for (long i = 0; i < a.length; i++) {
			arr[i] = a.arr[i];
		}
	}

	template<typename AType> Array<AType>::~Array() {
		deleteArray();
	}

	template<typename AType> Array<AType> Array<AType>::operator=(const Array &a) {
		//������� ������� ������
		deleteArray();

		//����� �������� ������ ������ � ����� ��������
		arr = new AType[a.length];
		length = a.length;

		//����� �������� ������ ������
		for (long i = 0; i < a.length; i++) {
			arr[i] = a.arr[i];
		}

		return *this;
	}

	template<typename AType> void Array<AType>::resize(long newsize) {
		
		//����� ������
		AType *narr = new AType[newsize];

		//����������� ������� �������
		for (int i = 0; i < newsize && i < length; i++) {
			narr[i] = arr[i];
		}

		//�������� ������� �������
		delete[]arr;

		//����������� ������ �������
		arr = narr;

		//���������� ����� ������
		length = newsize;

	}

	template<typename AType> ostream& operator<<(ostream &stream, const Array<AType> &A) {

		cout << '[';
		
		for (int i = 0; i < A.length; i++) {

			cout << A[i] 
				/*���� ��������� ��������� �������,
				�� ������ �� �������, � ���. ������
				������� ������� � ������*/
				<< ((i == A.length - 1)? "" : ", ");
		}

		cout << "]\n";

		return stream;

	}

	template<typename AType>
	template<typename VType>
	Array<AType> Array<AType>::operator+(VType val)
	{
		Array temp = *this;
		temp.resize(temp.length + 1);
		temp[temp.length - 1] = val;

		return temp;
	}

	template<typename AType>
	Array<AType> Array<AType>::operator+(const Array &A)
	{
		//����� ������
		Array temp(length + A.length);

		//����� ��������� �� ������� � �����
		AType *temparr = arr;
		long l = length;

		//��������� ������� � �����
		for (long i = 0, j = 0; i < temp.length; i++, j++) {
			
			/*����� �������� � ����� �������
			�������� � �������*/
			if (j == l) {
				j = 0;
				temparr = A.arr;
				l = A.length;
			}

			temp.arr[i] = temparr[j];
			
			
		}

		return temp;
	}

	//������� ��������� �������� � ������
	template<typename AType, typename VType>
	Array<VType> operator+(VType val, const Array<AType> &A) {

		Array<VType> temp(A.length + 1);
		temp[0] = val;

		//��������� � �������� A
		for (long i = 1; i < temp.length; i++) {
			temp.arr[i] = (VType)A.arr[i - 1];
		}

		return temp;
	}

	template<typename AType> template<typename VType> Array<AType> Array<AType>::operator+=(VType val) {

		//���������
		this->resize(length + 1);
		//����������� ���������� ��������
		this->arr[length - 1] = val;
		//����������
		return *this;
	}
	template<typename AType> Array<AType> Array<AType>::operator+=(const Array &A) {
		
		//������ �����
		long l = length;

		//��������� ������
		this->resize(length + A.length);

		//�������� ������ A � �����
		for (long i = l, j = 0; i < this->length; i++, j++) {

			this->arr[i] = A[j];
		}

		return *this;
	}

	//������� ������ ���� ������� �������� �������
	template<typename AType> Array<AType> Array<AType>::operator-() {
		for (int i = 0; i < length; i++) {
			arr[i] = -arr[i];
		}
		return *this;
	}

	//��������� ���������
	template<typename AType>
	inline bool Array<AType>::operator==(const Array & A)
	{
		//���� ����� �� �����, �� ������� �� �����
		if (length != A.length) {
			return false;
		}

		//���� ���� �������� ��������, �� ������� �� �����
		for (long i = 0; i < length; i++) {
			if (arr[i] != A[i]) {
				return false;
			}
		}

		//���� � ����� � �������� �����, �� ������� �����
		return true;
	}
	template<typename AType>
	inline bool Array<AType>::operator!=(const Array & A)
	{
		return !(*this == A);
	}

	template<typename AType>
	inline Array<AType> Array<AType>::operator,(Array &A)
	{
		Array temp = A;
		return temp;
	}
	

}