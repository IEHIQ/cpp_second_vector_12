#pragma once
#include <string>
#include <iostream>
#include <iterator>
#include "datelib.h"
#include "uilib.h"

/* ������ � ����� ������������ ���������� � ������ :
�������, ��� �����, ����������, ���� � ����� ��������, ��������(������ �� ������, �������, ���������),
������� ��������, ���������� ���������� ��������(������ ������� ���������� ����������). */

using namespace std;

enum Attributes { READONLY, HIDDEN, SYSTEM }; //������������ ��� � ���������� �����

class File
{
private:
	string catalog_; //�������
	string filename_; //��� �����
	string extension_; //����������
	Date creationDate_; //���� �������� �����
	string deletionTag_; //������� ��������
	bool attributes_[3]; //������ � ����������
	int sectorsCount_; //���-�� ��������

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
	); //����������� �� ���������� �� ���������

	//��������� ��� ����� ������
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

	void show(); //����� ������� � ������� 
	void input(); //������ �� �������
	void change(); //��������� ������

	void inputStringField(bool (File::*func)(string), const char* msg); //��������������� ������� ��� ����� ���� ������� �� �������
	void inputAttribute(Attributes attr, const char* msg); //��� ����� �������� �� �������
	void inputSectors(); //��� ����� �������� ���-�� ��������

	//����������� ��� ��������� ������� (���������� � Files.cpp)
	friend bool catalogComp(File first, File second);
	friend bool filenameComp(File first, File second);
	friend bool dateComp(File first, File second);
	friend bool deletiontagComp(File first, File second);

	bool operator== (File second); //���������� ��������� ���������
	void operator= (File second); //���������� ��������� ������������
	friend ostream_iterator<string>& operator<< (ostream_iterator<string> &out, File &file); //���������� ��������� ������ � ����� ��� ���������� ������
	friend istream_iterator<string>& operator>> (istream_iterator<string> &in, File &file); //���������� ��������� ����� �� ������ ��� ���������� �����
};