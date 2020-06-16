/* Синявский А. Задача 12.
	Данные о файле представлены структурой с полями:
	каталог, имя файла, расширение, дата и время создания, атрибуты (только на чтение, скрытый, системный),
	признак удаления, количество выделенных секторов (размер сектора фиксирован константой).
	Поиск по каталогу, названию, дате, признаку удаления. */

#include "pch.h"
#include <iostream>
#include <string>
#include "filelib.h"
#include "containerlib.h"
#include "uilib.h"

using namespace std;

//компараторы для сравнения записей
bool catalogComp(File first, File second) //по каталогу
{
	return first.catalog_ < second.catalog_;
}

bool filenameComp(File first, File second) //по имени файла
{
	return first.filename_ < second.filename_;
}

bool dateComp(File first, File second) //по дате создания
{
	return first.creationDate_ < second.creationDate_;
}

bool deletiontagComp(File first, File second) //по признаку удаления
{
	return first.deletionTag_ < second.deletionTag_;
}

int menu() //меню
{
	cout << "Выберите действие с контейнером (введите цифру): \n";
	cout << "1 — загрузить из файла;\n";
	cout << "2 — сохранить в файл;\n";
	cout << "3 — вывести содержимое в консоль;\n";
	cout << "4 — добавить запись;\n";
	cout << "5 — удалить запись;\n";
	cout << "6 — изменить запись;\n";
	cout << "7 — поиск по критерию;\n";
	cout << "другая цифра — выход.\n";
	int answer;
	cin >> answer;
	uilib::readEoln();
	return answer;
}

int inputContainerIndex(Container<File> &container) //ввод индекса элемента контейнера
{
	cout << "Введите индекс записи в контейнере (от 0 до " << (container.size() - 1) << "): ";
	return uilib::readInRange(0, (container.size() - 1));
}

void findRecords(Container<File> container) //поиск записей в контейнере с выбором способа и критерия поиска 
{
	File searchFile; //файл для возможной записи найденной подпоследовательности (если пользователь захочет её сохранить)
	string field; //переменная для ввода значения критерия поиска (каталога, имени, даты, признака удаления)
	Container<File> foundContainer; //контейнер для найденной подпоследовательности
	cout << "Выберите метод поиска: \n";
	cout << "1 — линейный поиск;\n";
	cout << "2 — бинарный поиск;\n";
	int searchKind = uilib::readInRange(1, 2); 
	cout << "Выберите критерий поиска: \n";
	cout << "1 — каталог;\n";
	cout << "2 — имя файла;\n";
	cout << "3 — дата создания;\n";
	cout << "4 — признак удаления;\n";
	int searchCriterion = uilib::readInRange(1, 4);

	switch (searchCriterion) //в зависимости от выбранного пользователем поиска осуществляем линейный/бинарный поиск записей по соотв. критерию
	{
	case 1:
		searchFile.inputStringField(&File::setCatalog, "каталог файла"); //по каталогу
		if (searchKind == 1)
			foundContainer = container.linearSearch(searchFile, catalogComp);
		else
			foundContainer = container.binarySearch(searchFile, catalogComp);
		break;
	case 2:
		searchFile.inputStringField(&File::setFilename, "имя файла"); //по имени файла
		if (searchKind == 1)
			foundContainer = container.linearSearch(searchFile, filenameComp);
		else
			foundContainer = container.binarySearch(searchFile, filenameComp);
		break;
	case 3:
		searchFile.inputStringField(&File::setCreationDate, "дату создания файла в формате <ДД/ММ/ГГГГ ЧЧ:ММ>"); //по дате создания
		if (searchKind == 1)
			foundContainer = container.linearSearch(searchFile, dateComp);
		else
			foundContainer = container.binarySearch(searchFile, dateComp);
		break;
	case 4:
		searchFile.inputStringField(&File::setDeletionTag, "признак удаления"); //по признаку удаления
		if (searchKind == 1)
			foundContainer = container.linearSearch(searchFile, deletiontagComp);
		else
			foundContainer = container.binarySearch(searchFile, deletiontagComp);
		break;
	}

	cout << "Найденные записи: \n";
	foundContainer.show(); //выводим найденную подпоследовательность
	cout << "Сохранить эту подпоследовательность в файл?"; //узнаём желание пользователя на сохранение подпоследовательности
	if (uilib::readUserAnswer())
	foundContainer.save(uilib::inputFilename(false));
}

int main()
{
	system("chcp 1251");
	system("cls");
	Container<File> container; //основной контейнер
	string filename; //переменная для ввода имени файла
	File sampleFile; //файл


	int menuIndex = menu(); //в соответствии с выбранным пользователем пунктом меню осуществляем соотв. действие
	while (menuIndex > 0 && menuIndex < 8)
	{
		switch (menuIndex)
		{
		case 1:
			container.load(uilib::inputFilename());
			break;
		case 2:
			container.save(uilib::inputFilename(false));
			break;
		case 3:
			container.show();
			break;
		case 4:
			sampleFile.input();
			container.add(sampleFile);
			break;
		case 5:
			container.erase(inputContainerIndex(container));
			break;
		case 6:
			container.change(inputContainerIndex(container));
			break;
		case 7:
			findRecords(container);
			break;
		}
		menuIndex = menu();
	}
}