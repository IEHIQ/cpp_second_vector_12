#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
using namespace std;

//шаблонный класс для контейнера и операций над ним

template <typename T>
class Container
{
private: 
	vector<T> container_; //в качестве контейнера используется вектор

public:
	Container linearSearch(T elem, bool (*comp)(T first, T second)) //линейный поиск элемента elem в контейнере
	{
		Container result; //результат поиска (подпоследовательность)
		for (T elem2 : container_) //для каждого элемента контейнера
			if (!comp(elem2, elem) && !comp(elem, elem2)) //выполняется сравнение элемента контейнера с элементом elem 
				//с помощью соответствующего компаратора (по соответствующему критерию)
				result.add(elem2); //если элементы совпадают по критерию, добавляем соотв. элемент контейнера в контейнер с результатом
		return result; //возвращаем контейнер с результатом поиска
	}

	Container binarySearch(T &elem, bool (*comp)(T first, T second)) //бинарный поиск
	{
		bool flag = false; //флаг поиска (найден ли элемент)
		Container result; //результат
		int left = 0; //левая граница поиска
		int right = container_.size(); //правая
		int mid = container_.size() / 2; //середина

		sort(container_.begin(), container_.end(), comp); //сортируем контейнер с помощью компаратора (по критерию)
		while ((left <= right) && !flag) //пока левая граница не пересеклась с правой или мы не попали в нужный элемент
		{
			mid = (left + right) / 2; //находим середину текущего отрезка поиска
			if (comp(elem, container_.at(mid))) //если нужный элемент меньше серединного
				right = mid - 1; //правая граница становится на место середины отрезка - 1
			else
				if (comp(container_.at(mid), elem)) //если больше
					left = mid + 1; //левая становится на середину + 1
				else
					flag = true; //иначе — элемент найден
		}
		if (flag) //если элемент найден
		{
			int i = mid; //становимся на позицию найденного элемента
			//и сохраняем нужные нам элементы в диапазоне одного найденного 
			//(т.к. в контейнере несколько элементов могут совпадать по определённому критерию, например, по каталогу)
			while ((i >= 0) && !comp(elem, container_.at(i)) && !comp(container_.at(i), elem)) //находим все элементы слева от позиции
			{
				result.add(container_.at(i));
				i--;
			}

			i = mid + 1;
			while ((i < container_.size()) && !comp(elem, container_.at(i)) && !comp(container_.at(i), elem)) //и справа
			{
				result.add(container_.at(i));
				i++;
			}
		}
		return result;
	}

	void add(T elem) //добавление элемента в контейнер
	{
		container_.push_back(elem);
	}

	void change(int index) //изменение элемента по индексу
	{
		if ((index >= 0) && (index < container_.size())) //если индекс корректен
			container_.at(index).change(); //изменяем этот объект
	}

	void erase(int index) //удаление объекта по индексу
	{
		if ((index >= 0) && (index < container_.size())) //если индекс корректен
			container_.erase(container_.begin() + index); //удаляем этот объект
	}

	void load(string filename) //загрузка контейнера из файла при помощи потоковых итераторов
	{
		ifstream in; //файл, из которого считываем
		in.open(filename);
		container_.clear(); //очищаем контейнер
		T elem;
		istream_iterator<string> begin = in; //потоковый итератор начала файла
		istream_iterator<string> end; //потоковый итератор конца файла
		istream_iterator<string> it; //итератор текущей позиции считывания
		for (it = begin; it != end; it++) //проходим итератором от начала до конца
		{
			it >> elem; //считываем элемент при помощи итератора (этот оператор перегружен для такого считывания)
			add(elem); //помещаем элемент в контейнер
		}
		in.close(); //закрываем файл
		cout << "Контейнер успешно загружен.\n";
	}

	void save(string filename) //сохранение контейнера в файл при помощи потоковых итераторов
	{
		ofstream out; //файл для сохранения
		out.open(filename);
		ostream_iterator<string> outIt(out, ""); //потоковый итератор файла
		for (T elem : container_) //для каждого элемента контейнера
			outIt << elem; //сохраняем его в файл (этот оператор перегружен для такой записи с итератором)
		out.close(); //закрываем файл
		cout << "Контейнер успешно сохранён.\n";
	}

	void show() //вывод контейнера в консоль
	{
		cout << '\n';
		int index = 0;
		for (T elem : container_) //для каждого элемента контенера
		{
			cout << '#' << index++ << '\n'; //выводим его индекс
			elem.show(); //и сам элемент
		}
		cout << '\n';
	}

	int size() //кол-во элементов в контейнере
	{
		return container_.size();
	}
};

