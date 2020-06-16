#pragma once
#include "pch.h"
#include "filelib.h"
#include <string>
#include "uilib.h"

const string FORBIDDEN_FE = "\\/?:*\"><|"; //�������, ����������� � ����� ����� � ����������
const string FORBIDDEN_C = "/?:*\"><|"; //�������, ����������� � ��������

const string ANSWERS[2] = { "���", "��" }; //������ ��� ������ � ����

using namespace std;

File::File( //�����������
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

bool checkCatalog(string catalog) //�������� �������� �� ������������
{
	//������� ���������, ����:
					//����� �������� � ������� ��� �������
					//������ ���� ������ � ��������� ��������� ����� (����� ����)
					//������ � ���������
					//������ � ��������� � �������� ����
					//� �������� (������� � 3 �������) �� ���������� ����������� �������� (FORBIDDEN_C)
	return (catalog.length() >= 3) && (catalog[0] >= 'A' && catalog[0] <= 'Z' && catalog[1] == ':' && catalog[2] == '\\' && catalog[catalog.length() - 1] == '\\') &&
		(catalog.substr(3, catalog.npos).find_first_of(FORBIDDEN_C) == string::npos);
}

bool checkFilename(string filename) //�������� ����� ����� �� ������������
{
	//��� ����� ���������, ����:
				//��� ��������
				//� �� ��� ����������� �������� (FORBIDDEN_FE)
	return (filename != "") && (filename.find_first_of(FORBIDDEN_FE) == string::npos);
}

bool checkExtension(string extension) //�������� ���������� �� ������������
{
	//���������� ���������, ���� � �� ��� ����������� �������� (FORBIDDEN_FE)
	return extension.find_first_of(FORBIDDEN_FE) == string::npos;
}

bool checkDeletionTag(string deletionTag) //�������� �������� �������� �� ������������
{
	//������� �������� ���������, ���� � ��� ��� �������� (��� ������ �������� ���������� �� ����� ��� ������ ���������� ������)
	return deletionTag.find_first_of(' ') == string::npos;
}

//---------------------------------------------------------------------------------------------------------------
//����� ���� ���������, ������� ���������� �����. ���� ����� ��� �� ������������� ��� � �����. ��������, ���� ��� ���������

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

void File::show() //����� ������� � �������
{
	cout << "����: " << catalog_ << filename_ << '.' << extension_ << '\n';
	cout << "���� ��������: " << creationDate_ << '\n';
	cout << "������� ��������: " << deletionTag_ << '\n';
	cout << "������ ��� ������: " << ANSWERS[attributes_[0]] << '\n';
	cout << "�������: " << ANSWERS[attributes_[1]] << '\n';
	cout << "���������: " << ANSWERS[attributes_[2]] << '\n';
	cout << "���-�� ��������: " << sectorsCount_ << '\n';
}

void File::inputAttribute(Attributes attr, const char* msg) //��������������� ������� ��� ����� �������� �� �������
{
	cout << '\n' << msg;
	//������������� ��������������� ������� � ��������, �������� ������������� (��/���)
	setAttribute(attr, uilib::readUserAnswer());
}

void File::inputSectors() //��������������� ������� ��� ����� �������� ���-�� ��������
{
	int sectors;
	cout << "\n������� ���-�� ��������: ";
	cin >> sectors;
	while (!setSectorsCount(sectors))
	{
		cout << "\n������������ ���-�� ��������, ��������� ����: ";
		cin >> sectors;
	}
}

void File::inputStringField(bool (File::*setFunction)(string), const char* msg) //��������������� ������� ��� ����� ���� ������� �� �������
//� ������� ��������� ����������� ������, � ������� �������������� �������� ��������� �������� 
//� ��������� ���������������� ���� ������� � ��� ��������, ���� ��� ���������
{
	string field; //���������� ��� �����
	cout << "������� " << msg <<": ";
	getline(cin, field);
	while (!(this->*setFunction)(field))
	{
		cout << "\n����������� ����, ��������� �������: ";
		getline(cin, field);
	} //������������ ������ ��������, ���� ��� �� �������� ����������
}

void File::input() //������ �� �������
{ 
	//��������������� ��������� ������ ����

	inputStringField(&File::setCatalog, "������� �����");

	inputStringField(&File::setFilename, "��� �����");

	inputStringField(&File::setExtension, "���������� �����");

	inputStringField(&File::setCreationDate, "���� �������� ����� � ������� <��/��/���� ��:��>");

	inputStringField(&File::setDeletionTag, "������� ��������");

	inputAttribute(READONLY, "������ ��� ������?");
	
	inputAttribute(HIDDEN, "�������?");

	inputAttribute(SYSTEM, "���������?");

	inputSectors();

	cout << '\n';
	uilib::readEoln();
}

bool File::operator== (File second) //���������� ��������� ���������
{
	return (this->catalog_ + this->filename_ + this->extension_) == (second.catalog_ + second.filename_ + second.extension_);
	//������������ ������ ����� ���� �������� (������� + ��� + ����������)
}

void File::operator= (File second) //���������� ��������� ������������
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

ostream_iterator<string>& operator<< (ostream_iterator<string> &out, File &file) //���������� ��������� ������ � ����� ��� ���������� ������
{
	//��������� ��������������� ������������� �������� ����� ������� (� ����������� ��������� �� 1 ����� ������� ������������)
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

istream_iterator<string>& operator>> (istream_iterator<string>& in, File &file) //���������� ��������� ����� �� ������ ��� ���������� �����
{
	//����� ������� ��������������� ������������� �������� ��������� (� ����������� ��������� �� 1 ����� ������� ������������)
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

void File::change() //��������� �������
{
	//�������� ���� �������, � ������������ � ������� ������������
	cout << "����� ���� �� ������ ��������? (������� �����)\n";
	cout << "1 � �������;\n";
	cout << "2 � ��� �����;\n";
	cout << "3 � ����������;\n";
	cout << "4 � ���� ��������;\n";
	cout << "5 � ������� ��������;\n";
	cout << "6 � ������� '������ ��� ������';\n";
	cout << "7 � ������� '�������'\n";
	cout << "8 � ������� '���������'\n";
	cout << "9 � ���-�� ��������\n";
	int answer = uilib::readInRange(1, 9);
	switch (answer)
	{
	case 1: 
		inputStringField(&File::setCatalog, "����� �������");
		break;
	case 2: 
		inputStringField(&File::setFilename, "����� ��� �����");
		break;
	case 3: 
		inputStringField(&File::setExtension, "����� ����������");
		break;
	case 4: 
		inputStringField(&File::setCreationDate, "����� ���� ��������");
		break;
	case 5: 
		inputStringField(&File::setDeletionTag, "����� ������� ��������");
		break;
	case 6: 
		inputAttribute(READONLY, "������ ��� ������?");
		break;
	case 7: 
		inputAttribute(HIDDEN, "�������?");
		break;
	case 8: 
		inputAttribute(SYSTEM, "���������?");
		break;
	case 9: 
		inputSectors();
		break;
	}
}