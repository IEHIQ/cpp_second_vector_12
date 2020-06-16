#pragma once
#include "pch.h"
#include "filelib.h"
#include <string>
#include "uilib.h"

const string FORBIDDEN_FE = "\\/?:*\"><|"; //символы, запрещённые в имени файла и расширении
const string FORBIDDEN_C = "/?:*\"><|"; //символы, запрещённые в каталоге

const string ANSWERS[2] = { "нет", "да" }; //ответы для запись в файл

using namespace std;

File::File( //конструктор
	string catalog,
	string filename,
	string extension,
	string creationDate,
	string deletionTag,
	bool isReadonly,
	bool isHidden,
	bool isSystem,
	int sectorsCount
	)
{
	setCatalog(catalog);
	setFilename(filename);
	setExtension(extension);
	setCreationDate(creationDate);
	attributes_[0] = isReadonly;
	attributes_[1] = isHidden;
	attributes_[2] = isSystem;
	deletionTag_ = deletionTag;
	setSectorsCount(sectorsCount);
}

bool checkCatalog(string catalog) //проверка каталога на корректность
{
	//каталог корректен, если:
					//длина каталога — минимум три символа
					//первая знак строки — заглавная латинская буква (метка тома)
					//второй — двоеточие
					//третий и последний — обратный слэш
					//в каталоге (начиная с 3 символа) не содержится запрещённых символов (FORBIDDEN_C)
	return (catalog.length() >= 3) && (catalog[0] >= 'A' && catalog[0] <= 'Z' && catalog[1] == ':' && catalog[2] == '\\' && catalog[catalog.length() - 1] == '\\') &&
		(catalog.substr(3, catalog.npos).find_first_of(FORBIDDEN_C) == string::npos);
}

bool checkFilename(string filename) //проверка имени файла на корректность
{
	//имя файла корректно, если:
				//оно непустое
				//в нём нет запрещённых символов (FORBIDDEN_FE)
	return (filename != "") && (filename.find_first_of(FORBIDDEN_FE) == string::npos);
}

bool checkExtension(string extension) //проверка расширения на корректность
{
	//расширение корректно, если в нём нет запрещённых символов (FORBIDDEN_FE)
	return extension.find_first_of(FORBIDDEN_FE) == string::npos;
}

bool checkDeletionTag(string deletionTag) //проверка признака удаления на корректность
{
	//признак удаления корректен, если в нем нет пробелов (это сильно упрощает считывание из файла при помощи итераторов потока)
	return deletionTag.find_first_of(' ') == string::npos;
}

//---------------------------------------------------------------------------------------------------------------
//далее идут аксессоры, которые возвращают соотв. поле файла или же устанавливают его в опред. значение, если оно корректно

string File::getCatalog() { return catalog_; }

bool File::setCatalog(string catalog)
{
	if (checkCatalog(catalog))
	{
		catalog_ = catalog;
		return true;
	}
	return false;
}

string File::getFilename() { return filename_; }

bool File::setFilename(string filename)
{
	if (checkFilename(filename))
	{
		filename_= filename;
		return true;
	}
	return false;
}

string File::getExtension() { return extension_; }

bool File::setExtension(string extension)
{
	if (checkExtension(extension))
	{
		extension_ = extension;
		return true;
	}
	return false;
}

string File::getCreationDate() { return creationDate_.toStr(); }

bool File::setCreationDate(string creationDate) { return creationDate_.trySetDateFromStr(creationDate); }

string File::getDeletionTag() { return deletionTag_; }

bool File::setDeletionTag(string deletionTag) 
{ 
	if (checkDeletionTag(deletionTag))
	{
		deletionTag_ = deletionTag;
		return true;
	}
	return false;
}

bool File::isReadonly() { return attributes_[0]; }

bool File::isHidden() { return attributes_[1]; }

bool File::isSystem() { return attributes_[2]; }

void File::setAttribute(Attributes attribute, bool enabled) { attributes_[static_cast<int>(attribute)] = enabled; }

int File::getSectorsCount() { return sectorsCount_; }

bool File::setSectorsCount(int sectorsCount)
{
	if (sectorsCount >= 0)
	{
		sectorsCount_ = sectorsCount;
		return true;
	}
	return false;
}

//---------------------------------------------------------------------------------------------------------------

void File::show() //вывод объекта в консоль
{
	cout << "Файл: " << catalog_ << filename_ << '.' << extension_ << '\n';
	cout << "Дата создания: " << creationDate_ << '\n';
	cout << "Признак удаления: " << deletionTag_ << '\n';
	cout << "Только для чтения: " << ANSWERS[attributes_[0]] << '\n';
	cout << "Скрытый: " << ANSWERS[attributes_[1]] << '\n';
	cout << "Системный: " << ANSWERS[attributes_[2]] << '\n';
	cout << "Кол-во секторов: " << sectorsCount_ << '\n';
}

void File::inputAttribute(Attributes attr, const char* msg) //вспомогательная функция для ввода атрибута из консоли
{
	cout << '\n' << msg;
	//устанавливаем соответствующий атрибут в значение, введённое пользователем (да/нет)
	setAttribute(attr, uilib::readUserAnswer());
}

void File::inputSectors() //вспомогательная функция для ввода значения кол-ва секторов
{
	int sectors;
	cout << "\nВведите кол-во секторов: ";
	cin >> sectors;
	while (!setSectorsCount(sectors))
	{
		cout << "\nНекорректное кол-во секторов, повторите ввод: ";
		cin >> sectors;
	}
}

void File::inputStringField(bool (File::*setFunction)(string), const char* msg) //вспомогательная функция для ввода поля объекта из консоли
//в функцию передаётся определённый сеттер, в котором осуществляется проверка введённого значения 
//и установка соответствующего поля объекта в это значение, если оно корректно
{
	string field; //переменная для ввода
	cout << "Введите " << msg <<": ";
	getline(cin, field);
	while (!(this->*setFunction)(field))
	{
		cout << "\nНеправльный ввод, повторите попытку: ";
		getline(cin, field);
	} //пользователь вводит значение, пока оно не окажется корректным
}

void File::input() //чтение из консоли
{ 
	//последовательно считываем каждое поле

	inputStringField(&File::setCatalog, "каталог файла");

	inputStringField(&File::setFilename, "имя файла");

	inputStringField(&File::setExtension, "расширение файла");

	inputStringField(&File::setCreationDate, "дату создания файла в формате <ДД/ММ/ГГГГ ЧЧ:ММ>");

	inputStringField(&File::setDeletionTag, "признак удаления");

	inputAttribute(READONLY, "Только для чтения?");
	
	inputAttribute(HIDDEN, "Скрытый?");

	inputAttribute(SYSTEM, "Системный?");

	inputSectors();

	cout << '\n';
	uilib::readEoln();
}

bool File::operator== (File second) //перегрузка оператора сравнения
{
	return (this->catalog_ + this->filename_ + this->extension_) == (second.catalog_ + second.filename_ + second.extension_);
	//сравниваются полные имена двух объектов (каталог + имя + расширение)
}

void File::operator= (File second) //перегрузка оператора присваивания
{
	catalog_ = second.catalog_;
	filename_ = second.filename_;
	extension_ = second.extension_;
	creationDate_ = second.creationDate_;
	deletionTag_ = second.deletionTag_;
	attributes_[0] = second.attributes_[0];
	attributes_[1] = second.attributes_[1];
	attributes_[2] = second.attributes_[2];
	sectorsCount_ = second.sectorsCount_;
}

ostream_iterator<string>& operator<< (ostream_iterator<string> &out, File &file) //перегрузка оператора вывода в поток для итераторов вывода
{
	//итератору последовательно присваиваются значения полей объекта (с увеличением итератора на 1 после каждого присваивания)
	*out = file.catalog_ + '\n'; out++;
	*out = file.filename_ + '\n'; out++;
	*out = file.extension_ + '\n'; out++;
	*out = file.creationDate_.toStr() + '\n'; out++;
	*out = file.deletionTag_ + '\n'; out++;
	*out = ANSWERS[file.attributes_[0]] + '\n'; out++;
	*out = ANSWERS[file.attributes_[1]] + '\n'; out++;
	*out = ANSWERS[file.attributes_[2]] + '\n'; out++;
	*out = to_string(file.sectorsCount_) + '\n'; out++;

	return out;
}

istream_iterator<string>& operator>> (istream_iterator<string>& in, File &file) //перегрузка оператора ввода из потока для итераторов ввода
{
	//полям объекта последовательно присваиваются значения итератора (с увеличением итератора на 1 после каждого присваивания)
	string field;
	file.catalog_ = *in;
	file.filename_ = *(++in); 
	file.extension_ = *(++in);
	field = *(++in) + ' ';
	field += *(++in);
	file.creationDate_ = (field);
	file.deletionTag_ = *(++in);
	file.attributes_[0] = uilib::answerFromFile(*(++in));
	file.attributes_[1] = uilib::answerFromFile(*(++in));
	file.attributes_[2] = uilib::answerFromFile(*(++in));
	file.sectorsCount_ = stoi(*(++in));

	return in;
}

void File::change() //изменение объекта
{
	//изменяем поле объекта, в соответствии с выбором пользователя
	cout << "Какое поле вы хотите поменять? (введите цифру)\n";
	cout << "1 — каталог;\n";
	cout << "2 — имя файла;\n";
	cout << "3 — расширение;\n";
	cout << "4 — дата создания;\n";
	cout << "5 — признак удаления;\n";
	cout << "6 — атрибут 'только для чтения';\n";
	cout << "7 — атрибут 'скрытый'\n";
	cout << "8 — атрибут 'системный'\n";
	cout << "9 — кол-во секторов\n";
	int answer = uilib::readInRange(1, 9);
	switch (answer)
	{
	case 1: 
		inputStringField(&File::setCatalog, "новый каталог");
		break;
	case 2: 
		inputStringField(&File::setFilename, "новое имя файла");
		break;
	case 3: 
		inputStringField(&File::setExtension, "новое расширение");
		break;
	case 4: 
		inputStringField(&File::setCreationDate, "новую дату создания");
		break;
	case 5: 
		inputStringField(&File::setDeletionTag, "новый признак удаления");
		break;
	case 6: 
		inputAttribute(READONLY, "Только для чтения?");
		break;
	case 7: 
		inputAttribute(HIDDEN, "Скрытый?");
		break;
	case 8: 
		inputAttribute(SYSTEM, "Системный?");
		break;
	case 9: 
		inputSectors();
		break;
	}
}