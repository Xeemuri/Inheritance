//Wake On LAN
#include <iostream>
#include <fstream>
using namespace std;

void main()
{
	setlocale(LC_ALL, "");
	std::ifstream fin("201 RAW.txt");
	std::ofstream fout_wol("201 WOL.txt");
	std::ofstream fout_dhcpd("201.dhcpd.txt");
	const int SIZE = 20;
	char ip_buffer[SIZE] = {};
	char mac_buffer[SIZE] = {};
	int cnt = 1;
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			fin >> ip_buffer;
			fin >> mac_buffer;
			fout_wol << mac_buffer << "\t\t" << ip_buffer << endl;

			fout_dhcpd << "host-" << cnt++ << endl;
			fout_dhcpd << "{" << endl;
			fout_dhcpd << "\thardware ethernet\t" << mac_buffer << endl;
			fout_dhcpd << "\tfixed-address\t" << ip_buffer << endl;
			fout_dhcpd << "}" << endl << endl;
		}
	}
	else
	{
		std::cerr << "Error: file not found." << endl;
	}
	fin.close();
	fout_wol.close();
}