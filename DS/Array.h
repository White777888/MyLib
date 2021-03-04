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

		//Функция для сортировки вставками
		void insertion_sort(AType *arr, long left, long right, bool(*CompareFunc)(AType a, AType b) = AscOrd);

		//Функция для сортировки слиянием
		void merge_sort(AType *arr, long left, long right, bool(*CompareFunc)(AType a, AType b) = AscOrd);
		//Функция, которая будет непосредственно сливать два массива
		void merge(AType *arr, long left, long middle, long right, bool(*CompareFunc)(AType a, AType b) = AscOrd);

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

		//Математические операторы для добавления элементов
		//+ объект
		template<typename VType> Array<AType> operator+(VType val);
		//+ Array
		Array operator+(const Array &A);
		//Объект + Array 
		template<typename AType, typename VType> friend Array<VType> operator+(VType val, const Array<AType> &A);

		//+ объект
		template<typename VType> Array<AType> operator+=(VType val);
		//+ Array
		Array operator+=(const Array &A);
		
		//Унарный минус
		Array operator-();

		//Операторы сравнения
		bool operator==(const Array &A);
		bool operator!=(const Array &A);

		//Оператор запятая
		Array operator,(Array &A);

		//Функции сортировки
		//Функция возвращающая true, если a > b
		static bool AscOrd(AType a, AType b) {
			return a > b;
		}
		static bool DescOrd(AType a, AType b) {
			return a < b;
		}
		/*Основную работу будет выполнять функция
		сортировки слиянием, но на небольших размерах массива
		будет работать функция сортировки вставками*/
		
		//Сортировка вставками
		void InsertSort(bool(*CompareFunc)(AType a, AType b) = AscOrd);
		//Сортировка слиянием
		void MergeSort(bool(*CompareFunc)(AType a, AType b) = AscOrd);
		
		//Получение подмассива
		Array SubArray(long left, long right);
		
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

	template<typename AType> template<typename VType> Array<AType> Array<AType>::operator+=(VType val) {

		//Расширяем
		this->resize(length + 1);
		//Присваиваем последнему элементу
		this->arr[length - 1] = val;
		//Возвращаем
		return *this;
	}
	template<typename AType> Array<AType> Array<AType>::operator+=(const Array &A) {
		
		//Старая длина
		long l = length;

		//Расширяем массив
		this->resize(length + A.length);

		//Копируем массив A в конец
		for (long i = l, j = 0; i < this->length; i++, j++) {

			this->arr[i] = A[j];
		}

		return *this;
	}

	//Функция меняет знак каждого элемента массива
	template<typename AType> Array<AType> Array<AType>::operator-() {
		for (int i = 0; i < length; i++) {
			arr[i] = -arr[i];
		}
		return *this;
	}

	//Операторы сравнения
	template<typename AType>
	inline bool Array<AType>::operator==(const Array & A)
	{
		//Если длины не равны, то массивы не равны
		if (length != A.length) {
			return false;
		}

		//Если есть неравные элементы, то массивы не равны
		for (long i = 0; i < length; i++) {
			if (arr[i] != A[i]) {
				return false;
			}
		}

		//Если и длины и элементы равны, то массивы равны
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

	//Функция сортировки слиянием
	template<typename AType>
	void Array<AType>::MergeSort(bool(*CompareFunc)(AType a, AType b))
	{
		merge_sort(arr, 0, length - 1, CompareFunc);
	}
	
	//Функция возвращает подмассив
	template<typename AType>
	Array<AType> Array<AType>::SubArray(long left, long right)
	{
		//Проверка на адекватность границ
		if (left < 0 || right >= length) {
			throw Exception("Incorrect borders");
		}
		if (left > right) {
			throw Exception("left > right!");
		}

		//Массив соответствующего размера
		Array temp(right - left + 1);

		for (int i = 0; i < temp.length; i++) {
			temp[i] = this->arr[left + i];
		}

		return temp;
	}
	//Функция разбиения массива и последующего слияния
	template<typename AType>
	void Array<AType>::merge_sort(AType * arr, long left, long right, bool(*CompareFunc)(AType a, AType b))
	{
		if ((right - left + 1) <= 15) {
			insertion_sort(arr, left, right, CompareFunc);
		}
		else if (left < right) {

			//Нашли середину массива
			long middle = (left + right) / 2;

			//Рекурсивный вызов
			//1
			merge_sort(arr, left, middle, CompareFunc);
			//2
			merge_sort(arr, middle + 1, right, CompareFunc);

			//Слияние подмассивов
			merge(arr, left, middle, right, CompareFunc);
		}
	}
	//Функция слияния двух массивов
	template<typename AType>
	void Array<AType>::merge(
		AType * arr, long left, long middle, long right, bool(*CompareFunc)(AType a, AType b)){
		//Размеры подмассивов
		long s1 = middle - left + 1;
		long s2 = right - middle;

		//Динамические массивы
		AType *a1 = new AType[s1];
		AType *a2 = new AType[s2];

		//Копируем данные из arr
		for (long i = 0; i < s1; i++) {
			a1[i] = arr[left + i];
		}
		for (long i = 0; i < s2; i++) {
			a2[i] = arr[(middle + 1) + i];
		}

		//Указатели на следующие доставаемые элементы массивов
		long na1 = 0, na2 = 0;

		for (long i = left; i <= right; i++) {

			//Если первый подмассив закончился
			//тогда копипуем весь второй и уходим
			if (na1 == s1) {
				for (; i <= right; i++) {
					arr[i] = a2[na2++];
				}
				break;
			}
			//Если второй подмассив закончился
			//тогда копипуем весь первый и уходим
			if (na2 == s2) {
				for (; i <= right; i++) {
					arr[i] = a1[na1++];
				}
				break;
			}

			//Записываем в выходную последовательность
			//меньшее значение
			if (CompareFunc(a2[na2], a1[na1])) {
				arr[i] = a1[na1++];
			}
			else {
				arr[i] = a2[na2++];
			}
		}

		//Очищаем память для массивов
		delete[]a1;
		delete[]a2;

	}

	//Функция сортировки вставками
	template<typename AType>
	void Array<AType>::InsertSort(bool(*CompareFunc)(AType a, AType b))
	{
		insertion_sort(arr, 0, length - 1, CompareFunc);
	}
	template<typename AType> void Array<AType>::insertion_sort(AType *arr, long left, long right, bool(*CompareFunc)(AType a, AType b)) {

		AType key;
		long j;

		for (long i = left + 1; i <= right; i++) {

			//Запомнили элемент
			key = arr[i];

			//Установили счетчик
			j = i - 1;

			//Начинаем смещение элементов слева направо
			while (j >= left && CompareFunc(arr[j], key)) {
				//Если элемент key должен быть левее/правее arr[j]
				arr[j + 1] = arr[j];
				j--;
			}

			arr[j + 1] = key;
		}
	}

}