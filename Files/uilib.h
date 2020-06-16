#pragma once
#include "pch.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

//��������������� ������� ��� �������������� � �������������

class uilib
{ 
public:
	static bool readUserAnswer() //���������� ������ ������������ � ������� "��/���"
	{
		char answer;
		cout << " (y/n):";
		cin >> answer; //��������� �����
		while ((answer != 'n') && (answer != 'y')) //���� �� �� ����� ��������� (y ��� n)
		{
			//����������� � ������������ ���� ����������� ������
			cout << "\n������������ ����, ��������� ������� (y/n): ";
			cin >> answer;
		}
		readEoln(); //��������� ���������� \n
		return answer == 'y';
	}

	static void readEoln() //���������� ������������� ����� ����� � �������������� cin ������� ����� ������
	{
		string garbage;
		getline(cin, garbage);
	}

	template<typename T>
	static T readInRange(T min, T max) //���������� �������� � ������� �� min �� max
	{
		T elem;
		cin >> elem;
		while (elem < min && elem > max)
		{
			cout << "\n������������ ����. ��������� �������: ";
			cin >> elem;
		}
		readEoln();
		return elem;
	}

	static string inputFilename(bool toLoad = true) //���� ����� �����
		//toLoad � ������������� �� �������� ��� ����� ��� ������ �� ���� (false � �� ������ � ����)
	{
		fstream file; //����, ������� �� ����� �������� ���������
		string filename; //�������� ��� �����
		cout << "������� ��� �����: ";
		getline(cin, filename);
		if (toLoad) //���� ���� ����� ����������� ��� ������
			file.open(filename, ios_base::in); //�������� ������� �� ������
		else
			file.open(filename, ios_base::out); //����� � �� ������
		while (!file.is_open()) //���� ���� �� ��������� ������� (��� �������)
		{
			//����������� � ������������ ���������� ��� �����
			cout << "������������ ��� �����. ��������� ����: ";
			getline(cin, filename);
			if (toLoad)
				file.open(filename, ios_base::in);
			else
				file.open(filename, ios_base::out);
		}
		file.close();
		return filename;
	}

	static bool answerFromFile(string answer) //��������������� ������� ���������� �������� ��/��� �� ����� � ������������� ��� � bool
	{
		return answer == "��";
	}
};