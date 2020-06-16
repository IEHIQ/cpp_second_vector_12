#pragma once
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
using namespace std;

//��������� ����� ��� ���������� � �������� ��� ���

template <typename T>
class Container
{
private: 
	vector<T> container_; //� �������� ���������� ������������ ������

public:
	Container linearSearch(T elem, bool (*comp)(T first, T second)) //�������� ����� �������� elem � ����������
	{
		Container result; //��������� ������ (���������������������)
		for (T elem2 : container_) //��� ������� �������� ����������
			if (!comp(elem2, elem) && !comp(elem, elem2)) //����������� ��������� �������� ���������� � ��������� elem 
				//� ������� ���������������� ����������� (�� ���������������� ��������)
				result.add(elem2); //���� �������� ��������� �� ��������, ��������� �����. ������� ���������� � ��������� � �����������
		return result; //���������� ��������� � ����������� ������
	}

	Container binarySearch(T &elem, bool (*comp)(T first, T second)) //�������� �����
	{
		bool flag = false; //���� ������ (������ �� �������)
		Container result; //���������
		int left = 0; //����� ������� ������
		int right = container_.size(); //������
		int mid = container_.size() / 2; //��������

		sort(container_.begin(), container_.end(), comp); //��������� ��������� � ������� ����������� (�� ��������)
		while ((left <= right) && !flag) //���� ����� ������� �� ����������� � ������ ��� �� �� ������ � ������ �������
		{
			mid = (left + right) / 2; //������� �������� �������� ������� ������
			if (comp(elem, container_.at(mid))) //���� ������ ������� ������ �����������
				right = mid - 1; //������ ������� ���������� �� ����� �������� ������� - 1
			else
				if (comp(container_.at(mid), elem)) //���� ������
					left = mid + 1; //����� ���������� �� �������� + 1
				else
					flag = true; //����� � ������� ������
		}
		if (flag) //���� ������� ������
		{
			int i = mid; //���������� �� ������� ���������� ��������
			//� ��������� ������ ��� �������� � ��������� ������ ���������� 
			//(�.�. � ���������� ��������� ��������� ����� ��������� �� ������������ ��������, ��������, �� ��������)
			while ((i >= 0) && !comp(elem, container_.at(i)) && !comp(container_.at(i), elem)) //������� ��� �������� ����� �� �������
			{
				result.add(container_.at(i));
				i--;
			}

			i = mid + 1;
			while ((i < container_.size()) && !comp(elem, container_.at(i)) && !comp(container_.at(i), elem)) //� ������
			{
				result.add(container_.at(i));
				i++;
			}
		}
		return result;
	}

	void add(T elem) //���������� �������� � ���������
	{
		container_.push_back(elem);
	}

	void change(int index) //��������� �������� �� �������
	{
		if ((index >= 0) && (index < container_.size())) //���� ������ ���������
			container_.at(index).change(); //�������� ���� ������
	}

	void erase(int index) //�������� ������� �� �������
	{
		if ((index >= 0) && (index < container_.size())) //���� ������ ���������
			container_.erase(container_.begin() + index); //������� ���� ������
	}

	void load(string filename) //�������� ���������� �� ����� ��� ������ ��������� ����������
	{
		ifstream in; //����, �� �������� ���������
		in.open(filename);
		container_.clear(); //������� ���������
		T elem;
		istream_iterator<string> begin = in; //��������� �������� ������ �����
		istream_iterator<string> end; //��������� �������� ����� �����
		istream_iterator<string> it; //�������� ������� ������� ����������
		for (it = begin; it != end; it++) //�������� ���������� �� ������ �� �����
		{
			it >> elem; //��������� ������� ��� ������ ��������� (���� �������� ���������� ��� ������ ����������)
			add(elem); //�������� ������� � ���������
		}
		in.close(); //��������� ����
		cout << "��������� ������� ��������.\n";
	}

	void save(string filename) //���������� ���������� � ���� ��� ������ ��������� ����������
	{
		ofstream out; //���� ��� ����������
		out.open(filename);
		ostream_iterator<string> outIt(out, ""); //��������� �������� �����
		for (T elem : container_) //��� ������� �������� ����������
			outIt << elem; //��������� ��� � ���� (���� �������� ���������� ��� ����� ������ � ����������)
		out.close(); //��������� ����
		cout << "��������� ������� �������.\n";
	}

	void show() //����� ���������� � �������
	{
		cout << '\n';
		int index = 0;
		for (T elem : container_) //��� ������� �������� ���������
		{
			cout << '#' << index++ << '\n'; //������� ��� ������
			elem.show(); //� ��� �������
		}
		cout << '\n';
	}

	int size() //���-�� ��������� � ����������
	{
		return container_.size();
	}
};

