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

		//������� ��� ���������� ���������
		void insertion_sort(AType *arr, long left, long right, bool(*CompareFunc)(AType a, AType b) = AscOrd);

		//������� ��� ���������� ��������
		void merge_sort(AType *arr, long left, long right, bool(*CompareFunc)(AType a, AType b) = AscOrd);
		//�������, ������� ����� ��������������� ������� ��� �������
		void merge(AType *arr, long left, long middle, long right, bool(*CompareFunc)(AType a, AType b) = AscOrd);

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
		//������� ������������ true, ���� a > b
		static bool AscOrd(AType a, AType b) {
			return a > b;
		}
		static bool DescOrd(AType a, AType b) {
			return a < b;
		}
		/*�������� ������ ����� ��������� �������
		���������� ��������, �� �� ��������� �������� �������
		����� �������� ������� ���������� ���������*/
		
		//���������� ���������
		void InsertSort(bool(*CompareFunc)(AType a, AType b) = AscOrd);
		//���������� ��������
		void MergeSort(bool(*CompareFunc)(AType a, AType b) = AscOrd);
		
		//��������� ����������
		Array SubArray(long left, long right);
		
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
		return A;
	}

	//������� ���������� ��������
	template<typename AType>
	void Array<AType>::MergeSort(bool(*CompareFunc)(AType a, AType b))
	{
		merge_sort(arr, 0, length - 1, CompareFunc);
	}
	
	//������� ���������� ���������
	template<typename AType>
	Array<AType> Array<AType>::SubArray(long left, long right)
	{
		//�������� �� ������������ ������
		if (left < 0 || right >= length) {
			throw Exception("Incorrect borders");
		}
		if (left > right) {
			throw Exception("left > right!");
		}

		//������ ���������������� �������
		Array temp(right - left + 1);

		for (int i = 0; i < temp.length; i++) {
			temp[i] = this->arr[left + i];
		}

		return temp;
	}
	//������� ��������� ������� � ������������ �������
	template<typename AType>
	void Array<AType>::merge_sort(AType * arr, long left, long right, bool(*CompareFunc)(AType a, AType b))
	{
		if ((right - left + 1) <= 15) {
			insertion_sort(arr, left, right, CompareFunc);
		}
		else if (left < right) {

			//����� �������� �������
			long middle = (left + right) / 2;

			//����������� �����
			//1
			merge_sort(arr, left, middle, CompareFunc);
			//2
			merge_sort(arr, middle + 1, right, CompareFunc);

			//������� �����������
			merge(arr, left, middle, right, CompareFunc);
		}
	}
	//������� ������� ���� ��������
	template<typename AType>
	void Array<AType>::merge(
		AType * arr, long left, long middle, long right, bool(*CompareFunc)(AType a, AType b)){
		//������� �����������
		long s1 = middle - left + 1;
		long s2 = right - middle;

		//������������ �������
		AType *a1 = new AType[s1];
		AType *a2 = new AType[s2];

		//�������� ������ �� arr
		for (long i = 0; i < s1; i++) {
			a1[i] = arr[left + i];
		}
		for (long i = 0; i < s2; i++) {
			a2[i] = arr[(middle + 1) + i];
		}

		//��������� �� ��������� ����������� �������� ��������
		long na1 = 0, na2 = 0;

		for (long i = left; i <= right; i++) {

			//���� ������ ��������� ����������
			//����� �������� ���� ������ � ������
			if (na1 == s1) {
				for (; i <= right; i++) {
					arr[i] = a2[na2++];
				}
				break;
			}
			//���� ������ ��������� ����������
			//����� �������� ���� ������ � ������
			if (na2 == s2) {
				for (; i <= right; i++) {
					arr[i] = a1[na1++];
				}
				break;
			}

			//���������� � �������� ������������������
			//������� ��������
			if (CompareFunc(a2[na2], a1[na1])) {
				arr[i] = a1[na1++];
			}
			else {
				arr[i] = a2[na2++];
			}
		}

		//������� ������ ��� ��������
		delete[]a1;
		delete[]a2;

	}

	//������� ���������� ���������
	template<typename AType>
	void Array<AType>::InsertSort(bool(*CompareFunc)(AType a, AType b))
	{
		insertion_sort(arr, 0, length - 1, CompareFunc);
	}
	template<typename AType> void Array<AType>::insertion_sort(AType *arr, long left, long right, bool(*CompareFunc)(AType a, AType b)) {

		AType key;
		long j;

		for (long i = left + 1; i <= right; i++) {

			//��������� �������
			key = arr[i];

			//���������� �������
			j = i - 1;

			//�������� �������� ��������� ����� �������
			while (j >= left && CompareFunc(arr[j], key)) {
				//���� ������� key ������ ���� �����/������ arr[j]
				arr[j + 1] = arr[j];
				j--;
			}

			arr[j + 1] = key;
		}
	}

}