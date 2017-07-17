/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Tomislav Nikolov
* @idnumber 45211
* @task 4
* @compiler VC
*
*/
#ifndef __SIMULATION_HEADER_INCLUDED_
#define __SIMULATION_HEADER_INCLUDED_

#include <iostream>
#include <fstream>
#include "BinTreeBal.h"

class Data{
private:
	int key;
	char* str;
public:
	Data() : key(0), str(nullptr) {}
	Data(Data&);
	~Data() { key = 0; delete[]str; }
	Data& operator=(Data&);
	bool operator==(Data&)const;
	bool operator>=(Data&)const;
	bool operator<(Data&)const;
	void Set(int, char*);
	void SetOnlyKey(int);
	int GetKey()const{ return key; }
	char* GetStr()const{ return str; }
};

Data::Data(Data& obj)
{
	key = obj.key;
	str = new char[strlen(obj.str) + 1];
	unsigned i = 0;
	for (i = 0; i < strlen(obj.str); i++)
	{
		str[i] = obj.str[i];
	}
	str[i] = '\0';
}

Data& Data::operator=(Data& obj)
{
	if (this != &obj)
	{
		Set(obj.key, obj.str);
	}
	return *this;
}

void Data::Set(int k, char* s)
{
	key = k;
	if (str != nullptr)
	{
		delete[]str;
	}
	str = new char[strlen(s) + 1];
	unsigned i = 0;
	for (i = 0; i < strlen(s); i++)
	{
		str[i] = s[i];
	}
	str[i] = '\0';
}

void Data::SetOnlyKey(int k)
{
	key = k; 
	str = nullptr;
}

bool Data::operator==(Data& obj)const
{
	if (str==nullptr) return (key == obj.key);
	else return (key == obj.key&&strcmp(str, obj.str) == 0);
}

bool Data::operator>=(Data& obj)const
{
	return !(key < obj.key);
}

bool Data::operator<(Data& obj)const
{
	return (key < obj.key);
}

class Simulation{
private:
	BinTree<Data> MaTri;
	std::ifstream file;
	Data buff;
	int num;
	int size;
	char c[128];
public:
	Simulation();
	~Simulation();
	void FileOpen(char*);
	void Command(char*, int, char*);
	int RemovedByKey(Data&);
};

Simulation::Simulation()
{
	if (file.is_open())
	{
		file.close();
	}
	num = 0;
	size = 0;
}

Simulation::~Simulation()
{
	if (file.is_open())
	{
		file.close();
	}
	num = 0;
	size = 0;
}

void Simulation::FileOpen(char* name)
{
	if (file.is_open())
	{
		file.close();
	}
	file.open(name, std::ios::binary);
	while (file.good())
	{
		file.read((char*)(&num), sizeof(num));
		file.read((char*)(&size), sizeof(num));
		int i = 0;
		for (i = 0; i < size; i++)
		{
			file.read((char*)(&c[i]), sizeof(char));
		}
		c[i] = '\0';
		buff.Set(num, c);
		MaTri.AddEntry(buff);
	}
	MaTri.Balance();
}

void Simulation::Command(char* comm, int k, char* str)
{
	if (strcmp(comm, "add") == 0)
	{
		buff.Set(k, str);
		MaTri.AddEntry(buff);
	}
	else if (strcmp(comm, "remove") == 0)
	{
		buff.Set(k, str);
		if (MaTri.RemoveEntry(buff))
		{
			std::cout << "true" << std::endl;
		}
		else
		{
			std::cout << "false" << std::endl;
		}
	}
	else if (strcmp(comm, "removeall") == 0)
	{
		buff.SetOnlyKey(k);
		std::cout << RemovedByKey(buff) << std::endl;
	}
	else if (strcmp(comm, "search") == 0)
	{
		buff.Set(k, str);
		if (MaTri.SearchEntry(buff))
		{
			std::cout << "true" << std::endl;
		}
		else 
		{
			std::cout << "false" << std::endl;
		}
	}
}

int Simulation::RemovedByKey(Data& buff)
{
	int cnt = 0;
	while (MaTri.RemoveEntry(buff))
		cnt++;
	return cnt;
}

#endif