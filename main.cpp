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
#include <iostream>
#include "Simulation.h"

int main()
{
	Simulation MaMan;
	char buff[128];
	std::cin >> buff;
	buff[strlen(buff)] = '\0';
	MaMan.FileOpen(buff);
	char comm[10];
	int key;
	while (!std::cin.eof())
	{
		std::cin >> comm >> key;
		std::cin.getline(buff, 128);
		comm[strlen(comm)] = '\0';
		for (unsigned i = 0; i < strlen(buff); i++)
			buff[i] = buff[i + 1];
		MaMan.Command(comm, key, buff);
	}
	return 0;
}