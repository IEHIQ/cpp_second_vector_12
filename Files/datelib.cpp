#include "pch.h"
#include "datelib.h"

const string AVALIABLE_D = "1234567890:/ "; //символы, доступные в дате

//конструкторы с перегрузками
Date::Date()
{
	//дефолтная дата — 1/1/1970 00:00
	day_ = 1;
	month_ = 1;
	year_ = 1970;
	hours_ = 0;
	minutes_ = 0;
}

//две перегрузки для строки и строкового литерала
Date::Date(string strDate) { this -> trySetDateFromStr(strDate); }

Date::Date(const char* strDate) { this -> trySetDateFromStr(strDate); }

bool Date::trySetDateFromStr(string date) //функция, осуществляющая попытку перевода строки к дате 
{
	//дата считается корректной, если:
				//длина — от 12 до 16 символов (различия в записи 3 или 03 в дне, месяце, часах и минутах)
				//содержатся только разрешённые символы (AVALIABLE_D)
				//соблюдено корректное расположения слешей и двоеточия
				//день — от 1 до 31
				//месяц — от 1 до 12
				//год от 1970 до 2020
				//часы — от 0 до 23
				//минуты — от 0 до 59
	//далее строка поэтапно разбивается на части относительно разделителей, 
	//эти части приводятся к числам, и определяется их принадлежность соответствующему диапазону
	if ((date.length() >= 12) && (date.length() <= 16) && (date.find_first_not_of(AVALIABLE_D) == string::npos))
	{
		int day = stoi(date.substr(0, date.find('/')));
		if ((day > 0) && (day < 32))
		{
			date = date.substr(date.find('/') + 1, date.npos);
			int month = stoi(date.substr(0, date.find('/')));
			if ((month > 0) && (month < 13))
			{
				date = date.substr(date.find('/') + 1, date.npos);
				int year = stoi(date.substr(0, date.find(' ')));
				if ((year >= 1970) && (year < 2021))
				{
					date = date.substr(date.find(' ') + 1, date.npos);
					int hours = stoi(date.substr(0, date.find(':')));
					if ((hours >= 0) && (hours < 24))
					{
						date = date.substr(date.find(':') + 1, date.npos);
						int minutes = stoi(date);
						if ((minutes >= 0) && (minutes < 60))
						{
							//если дата корректна, записываем её в объект
							day_ = day;
							month_ = month;
							year_ = year;
							hours_ = hours;
							minutes_ = minutes;
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}


//перегрузки логических операторов для даты
bool Date::operator== (Date second) //равенство
{
	//последовательно сравниваются все поля
	return (year_ == second.year_) && (month_ == second.month_) && (day_ == second.day_) && (hours_ == second.hours_) && (minutes_ == second.minutes_);
}

bool Date::operator!= (Date second) //неравенство
{
	//отрицание от равнества
	return !(*this == second);
}

bool Date::operator<(Date second) //меньше
{
	if (*this != second) //сначала смотрим на неравенство
		//далее последовательно сравниваем поля года, месяца, дня, часов и минут
		if (year_ != second.year_)
			return (year_ < second.year_);
		else
			if (month_ != second.month_)
				return (month_ < second.month_);
			else
				if (day_ != second.day_)
					return (day_ < second.day_);
				else
					if (hours_ != second.hours_)
						return (hours_ < second.hours_);
					else
						return (minutes_ < second.minutes_);
	return false;
}

bool Date::operator> (Date second) //больше
{
	//неравенство и отрицание "меньше"
	return (*this != second) and !(*this < second);
}

void Date::operator= (Date second) //присваивание
{
	//последовательно присваиваются значения всех полей
	day_ = second.day_;
	month_ = second.month_;
	year_ = second.year_;
	minutes_ = second.minutes_;
	hours_ = second.hours_;
}

string Date::toStr() //перевод в строку
{
	return to_string(day_) + '/' + to_string(month_) + '/' + to_string(year_) + ' ' + to_string(hours_) + ':' + to_string(minutes_);
}

void Date::operator= (string strDate) //присваивание для строки
{
	this->trySetDateFromStr(strDate);
}

ostream& operator<< (ostream &out, Date date) //оператор вывода
{
	out << date.toStr(); //выводим дату, переведённую в строку
	return out;
}

istream& operator>> (istream& in, Date date) //оператор ввода
{
	string strDate;
	in >> strDate; //считываем сначала в строку
	date = strDate; //переводим строку в дату
	return in;
}