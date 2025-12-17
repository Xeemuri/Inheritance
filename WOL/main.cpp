//Wake On LAN
#include <iostream>
#include <fstream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	std::ifstream fin("201 RAW.txt");
	std::ofstream fout("201 WOL.txt");
	const int SIZE = 20;
	char ip_buffer[SIZE] = {};
	char mac_buffer[SIZE] = {};
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> ip_buffer;
			fin >> mac_buffer;
			fout << mac_buffer << "\t\t" << ip_buffer << endl;
		}
	}
	else
	{
		std::cerr << "Error: file not found." << endl;
	}
	fin.close();
	fout.close();
}