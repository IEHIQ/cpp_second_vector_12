#pragma once
#include <string>

using namespace std;

//����� ���� � ������� <��/��/���� ��:��>

class Date
{
private:
	short day_; //����
	short month_; //�����
	short year_; //���
	short hours_; //����
	short minutes_; //������

public:
	//������������ � ������������
	Date();
	Date(string strDate);
	Date(const char* strDate);

	bool trySetDateFromStr(string date); //�������, �������������� ������� �������� ������ � ����
	//���������� ���������� ���������� ��� ����
	bool operator== (Date second);
	bool operator!= (Date second);
	bool operator< (Date second);
	bool operator> (Date second);
	void operator= (Date second);
	void operator= (string strDate);
	//����� ���������� ���������� ���������� �����/������
	friend ostream& operator<< (ostream& out, Date date);
	friend istream& operator>> (istream& in, Date date);
	string toStr(); //������� ���� � ������
};

