#pragma once
#include <iostream>
#include <ostream>
#include "Exception.h"

using namespace std;

namespace MyLib {
	//Класс массива
	template<typename AType> class Array
	{
		AType *arr;
		long int length;

		//Функция удаления массива
		void deleteArray() {
			if (length != 0) {
				delete[]arr;
			}
		}

	public:

		//Конструкторы
		Array();
		Array(long length);
		Array(const Array& a);

		//Деструктор
		~Array();

		//Функция доступа к размеру
		long getLength() {
			return length;
		}

		//Оператор индексации массива
		AType& operator[](long i) {

			//В случае выхода за границы
			//выбрасываем исключение
			if (i < 0 || i >= length) {
				throw Exception("Index was out of array's border");
			}

			return arr[i];
		}
		AType& operator[](long i)const {

			//В случае выхода за границы
			//выбрасываем исключение
			if (i < 0 || i >= length) {
				throw Exception("Index was out of array's border");
			}

			return arr[i];
		}

		//Перегруженный оператор присваивания
		Array operator=(const Array &a);

		//Функция изменения размера
		void resize(long newsize);

		//Оператор вывода массива в потоке вывода
		template<typename AType> friend ostream& operator<<(ostream &stream, const Array<AType> &A);

		//Математические операторы с массивом
		//+ объект
		template<typename VType> Array<AType> operator+(VType val);
		//+ Array
		Array operator+(const Array &A);
		//Объект + Array 
		template<typename AType, typename VType> friend Array<VType> operator+(VType val, const Array<AType> &A);


		//Логические операторы с массивом

		//Функция сортировки

	};

	template<typename AType> Array<AType>::Array() {
		arr = NULL;
		length = 0;
	}

	template<typename AType> Array<AType>::Array(long length) {
		//Выделение памяти под массив
		arr = new AType[length];
		this->length = length;
	}

	template<typename AType> Array<AType>::Array(const Array& a) {
		//Сначала очищаем память
		/*deleteArray();*/

		//Затем выделяем память заново с новым размером
		arr = new AType[a.length];
		length = a.length;

		//Затем копируем второй массив
		for (long i = 0; i < a.length; i++) {
			arr[i] = a.arr[i];
		}
	}

	template<typename AType> Array<AType>::~Array() {
		deleteArray();
	}

	template<typename AType> Array<AType> Array<AType>::operator=(const Array &a) {
		//Сначала очищаем память
		deleteArray();

		//Затем выделяем память заново с новым размером
		arr = new AType[a.length];
		length = a.length;

		//Затем копируем второй массив
		for (long i = 0; i < a.length; i++) {
			arr[i] = a.arr[i];
		}

		return *this;
	}

	template<typename AType> void Array<AType>::resize(long newsize) {
		
		//Новый массив
		AType *narr = new AType[newsize];

		//Копирование старого массива
		for (int i = 0; i < newsize && i < length; i++) {
			narr[i] = arr[i];
		}

		//Удаление старого массива
		delete[]arr;

		//Запоминание нового массива
		arr = narr;

		//Запоминаем новый размер
		length = newsize;

	}

	template<typename AType> ostream& operator<<(ostream &stream, const Array<AType> &A) {

		cout << '[';
		
		for (int i = 0; i < A.length; i++) {

			cout << A[i] 
				/*Если выводится последний элемент,
				то ничего не выводим, в обр. случае
				выводим запятую и пробел*/
				<< ((i == A.length - 1)? "" : ", ");
		}

		cout << "]\n";

		return stream;

	}

	template<typename AType>
	template<typename VType>
	Array<AType> Array<AType>::operator+(VType val)
	{
		//Array temp(length + 1);
		//
		////Прибавляем значение ко всем элементам
		//for (long i = 0; i < temp.length - 1; i++) {
		//	temp.arr[i] += val;
		//}

		Array temp = *this;
		temp.resize(temp.length + 1);
		temp[temp.length - 1] = val;

		return temp;
	}

	template<typename AType>
	Array<AType> Array<AType>::operator+(const Array &A)
	{
		//Новый массив
		Array temp(length + A.length);

		//Общий указатель на массивы и длина
		AType *temparr = arr;
		long l = length;

		//Соединяем массивы в новом
		for (long i = 0, j = 0; i < temp.length; i++, j++) {
			
			/*Когда закончим с одним масивом
			перейдем к другому*/
			if (j == l) {
				j = 0;
				temparr = A.arr;
				l = A.length;
			}

			temp.arr[i] = temparr[j];
			
			
		}

		return temp;
	}

	//Функция объединит значение и массив
	template<typename AType, typename VType>
	Array<VType> operator+(VType val, const Array<AType> &A) {

		Array<VType> temp(A.length + 1);
		temp[0] = val;

		//Соединяем с массивом A
		for (long i = 1; i < temp.length; i++) {
			temp.arr[i] = (VType)A.arr[i - 1];
		}

		return temp;
	}

	
}