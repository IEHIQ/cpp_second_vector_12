#pragma once
#include "pch.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//вспомогательные функции для взаимодействия с пользователем

class uilib
{ 
public:
	static bool readUserAnswer() //считывание ответа пользователя в формате "да/нет"
	{
		char answer;
		cout << " (y/n):";
		cin >> answer; //считываем ответ
		while ((answer != 'n') && (answer != 'y')) //пока он не будет корректен (y или n)
		{
			//запрашиваем у пользователя ввод корректного ответа
			cout << "\nНеправильный ввод, повторите попытку (y/n): ";
			cin >> answer;
		}
		readEoln(); //считываем оставшийся \n
		return answer == 'y';
	}

	static void readEoln() //считывание оставающегося после ввода с использованием cin символа конца строки
	{
		string garbage;
		getline(cin, garbage);
	}

	template<typename T>
	static T readInRange(T min, T max) //считывание значения в отрезке от min до max
	{
		T elem;
		cin >> elem;
		while (elem < min && elem > max)
		{
			cout << "\nНеправильный ввод. Повторите попытку: ";
			cin >> elem;
		}
		readEoln();
		return elem;
	}

	static string inputFilename(bool toLoad = true) //ввод имени файла
		//toLoad — предназначено ли вводимое имя файла для чтения из него (false — на запись в него)
	{
		fstream file; //файл, который мы будем пытаться открывать
		string filename; //вводимое имя файла
		cout << "Введите имя файла: ";
		getline(cin, filename);
		if (toLoad) //если файл будет открываться для чтения
			file.open(filename, ios_base::in); //пытаемся открыть на чтение
		else
			file.open(filename, ios_base::out); //иначе — на запись
		while (!file.is_open()) //пока файл не получится открыть (или создать)
		{
			//запрашиваем у пользователя корректное имя файла
			cout << "Некорректное имя файла. Повторите ввод: ";
			getline(cin, filename);
			if (toLoad)
				file.open(filename, ios_base::in);
			else
				file.open(filename, ios_base::out);
		}
		file.close();
		return filename;
	}

	static bool answerFromFile(string answer) //вспомогательная функция считывания значения да/нет из файла и трансформация его в bool
	{
		return answer == "да";
	}
};