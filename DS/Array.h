#pragma once
#include "XExecption.h"

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

		AType& operator[](long i) {

			//В случае выхода за границы
			//выбрасываем исключение
			if (i < 0 || i >= length) {
				throw XExecption("Index was out of array's border");
			}

			return arr[i];
		}

		//Перегруженный оператор присваивания
		Array operator=(const Array &a);

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
}