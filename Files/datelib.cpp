#include "pch.h"
#include "datelib.h"

const string AVALIABLE_D = "1234567890:/ "; //�������, ��������� � ����

//������������ � ������������
Date::Date()
{
	//��������� ���� � 1/1/1970 00:00
	day_ = 1;
	month_ = 1;
	year_ = 1970;
	hours_ = 0;
	minutes_ = 0;
}

//��� ���������� ��� ������ � ���������� ��������
Date::Date(string strDate) { this -> trySetDateFromStr(strDate); }

Date::Date(const char* strDate) { this -> trySetDateFromStr(strDate); }

bool Date::trySetDateFromStr(string date) //�������, �������������� ������� �������� ������ � ���� 
{
	//���� ��������� ����������, ����:
				//����� � �� 12 �� 16 �������� (�������� � ������ 3 ��� 03 � ���, ������, ����� � �������)
				//���������� ������ ����������� ������� (AVALIABLE_D)
				//��������� ���������� ������������ ������ � ���������
				//���� � �� 1 �� 31
				//����� � �� 1 �� 12
				//��� �� 1970 �� 2020
				//���� � �� 0 �� 23
				//������ � �� 0 �� 59
	//����� ������ �������� ����������� �� ����� ������������ ������������, 
	//��� ����� ���������� � ������, � ������������ �� �������������� ���������������� ���������
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
							//���� ���� ���������, ���������� � � ������
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


//���������� ���������� ���������� ��� ����
bool Date::operator== (Date second) //���������
{
	//��������������� ������������ ��� ����
	return (year_ == second.year_) && (month_ == second.month_) && (day_ == second.day_) && (hours_ == second.hours_) && (minutes_ == second.minutes_);
}

bool Date::operator!= (Date second) //�����������
{
	//��������� �� ���������
	return !(*this == second);
}

bool Date::operator<(Date second) //������
{
	if (*this != second) //������� ������� �� �����������
		//����� ��������������� ���������� ���� ����, ������, ���, ����� � �����
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

bool Date::operator> (Date second) //������
{
	//����������� � ��������� "������"
	return (*this != second) and !(*this < second);
}

void Date::operator= (Date second) //������������
{
	//��������������� ������������� �������� ���� �����
	day_ = second.day_;
	month_ = second.month_;
	year_ = second.year_;
	minutes_ = second.minutes_;
	hours_ = second.hours_;
}

string Date::toStr() //������� � ������
{
	return to_string(day_) + '/' + to_string(month_) + '/' + to_string(year_) + ' ' + to_string(hours_) + ':' + to_string(minutes_);
}

void Date::operator= (string strDate) //������������ ��� ������
{
	this->trySetDateFromStr(strDate);
}

ostream& operator<< (ostream &out, Date date) //�������� ������
{
	out << date.toStr(); //������� ����, ����������� � ������
	return out;
}

istream& operator>> (istream& in, Date date) //�������� �����
{
	string strDate;
	in >> strDate; //��������� ������� � ������
	date = strDate; //��������� ������ � ����
	return in;
}