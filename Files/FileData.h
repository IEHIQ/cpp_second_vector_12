#pragma once
#include <string>
#include <iostream>

/*	������ � ����� ������������ ���������� � ������: 
	�������, ��� �����, ����������, ���� � ����� ��������, �������� (������ �� ������, �������, ���������), 
	������� ��������, ���������� ���������� �������� (������ ������� ���������� ����������). */

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

