#pragma once
#include <string>
#include <iostream>

/*	ƒанные о файле представлены структурой с пол€ми: 
	каталог, им€ файла, расширение, дата и врем€ создани€, атрибуты (только на чтение, скрытый, системный), 
	признак удалени€, количество выделенных секторов (размер сектора фиксирован константой). */

using namespace std;

enum ATTR { READONLY, HIDDEN, SYSTEM };

class FileData
{
	private:
		string catalog;
		string fileName;
		string extension;
		string creationDate;
		bool attributes[3];
		bool isDeleted;
		int sectorsCount;

	public:
		FileData();
};

