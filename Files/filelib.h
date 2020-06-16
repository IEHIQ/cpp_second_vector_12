#pragma once
#include <string>
#include <iostream>
#include <iterator>
#include "datelib.h"
#include "uilib.h"

/* Данные о файле представлены структурой с полями :
каталог, имя файла, расширение, дата и время создания, атрибуты(только на чтение, скрытый, системный),
признак удаления, количество выделенных секторов(размер сектора фиксирован константой). */

using namespace std;

enum Attributes { READONLY, HIDDEN, SYSTEM }; //перечислимый тип с атрибутами файла

class File
{
private:
	string catalog_; //каталог
	string filename_; //имя файла
	string extension_; //расширение
	Date creationDate_; //дата создания файла
	string deletionTag_; //признак удаления
	bool attributes_[3]; //массив с атрибутами
	int sectorsCount_; //кол-во секторов

public:
	File(
		string catalog = "D:\\",
		string filename = "untitled",
		string extension = "txt",
		string creationDate = "1/1/1970 00:00",
		string deletionTag = "unknown",
		bool isReadonly = false,
		bool isHidden = false,
		bool isSystem = false,
		int sectorsCount = 0
	); //конструктор со значениями по умолчанию

	//аксессоры для полей класса
	string getCatalog();
	bool setCatalog(string catalog);

	string getFilename();
	bool setFilename(string filename);

	string getExtension();
	bool setExtension(string extension);

	string getCreationDate();
	bool setCreationDate(string creationDate);

	string getDeletionTag();
	bool setDeletionTag(string deletionTag);

	bool isReadonly();

	bool isHidden();

	bool isSystem();

	void setAttribute(Attributes attribute, bool enabled = true);

	int getSectorsCount();
	bool setSectorsCount(int sectorsCount);

	void show(); //вывод объекта в консоль 
	void input(); //чтение из консоли
	void change(); //изменение записи

	void inputStringField(bool (File::*func)(string), const char* msg); //вспомогательная функция для ввода поля объекта из консоли
	void inputAttribute(Attributes attr, const char* msg); //для ввода атрибута из консоли
	void inputSectors(); //для ввода значения кол-ва секторов

	//компараторы для сравнения записей (определены в Files.cpp)
	friend bool catalogComp(File first, File second);
	friend bool filenameComp(File first, File second);
	friend bool dateComp(File first, File second);
	friend bool deletiontagComp(File first, File second);

	bool operator== (File second); //перегрузка оператора сравнения
	void operator= (File second); //перегрузка оператора присваивания
	friend ostream_iterator<string>& operator<< (ostream_iterator<string> &out, File &file); //перегрузка оператора вывода в поток для итераторов вывода
	friend istream_iterator<string>& operator>> (istream_iterator<string> &in, File &file); //перегрузка оператора ввода из потока для итераторов ввода
};