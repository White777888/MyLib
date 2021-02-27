#pragma once
#include "XExecption.h"

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

		AType& operator[](long i) {

			//� ������ ������ �� �������
			//����������� ����������
			if (i < 0 || i >= length) {
				throw XExecption("Index was out of array's border");
			}

			return arr[i];
		}

		//������������� �������� ������������
		Array operator=(const Array &a);

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
}