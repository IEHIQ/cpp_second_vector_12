#pragma once
#include <string>

using namespace std;

//класс даты в формате <ДД/ММ/ГГГГ ЧЧ:ММ>

class Date
{
private:
	short day_; //день
	short month_; //месяц
	short year_; //год
	short hours_; //часы
	short minutes_; //минуты

public:
	//конструкторы с перегрузками
	Date();
	Date(string strDate);
	Date(const char* strDate);

	bool trySetDateFromStr(string date); //функция, осуществляющая попытку перевода строки к дате
	//перегрузки логических операторов для даты
	bool operator== (Date second);
	bool operator!= (Date second);
	bool operator< (Date second);
	bool operator> (Date second);
	void operator= (Date second);
	void operator= (string strDate);
	//также перегрузка операторов потокового ввода/вывода
	friend ostream& operator<< (ostream& out, Date date);
	friend istream& operator>> (istream& in, Date date);
	string toStr(); //перевод даты в строку
};

