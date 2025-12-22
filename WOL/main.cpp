//Wake On LAN
#include <iostream>
#include <fstream>
using namespace std;

//#define WOL
#define DHCPD
void main()
{
#ifdef WOL
	setlocale(LC_ALL, "");
	std::ifstream fin("201 RAW.txt");
	std::ofstream fout_wol("201.WOL.txt");
	std::ofstream fout_dhcpd("201.dhcpd.txt");
	const int SIZE = 18;
	char ip_buffer[SIZE] = {};
	char mac_buffer[SIZE] = {};
	if (fin.is_open())
	{
		int cnt = 1;
		while (!fin.eof())
		{
			fin >> ip_buffer;
			fin >> mac_buffer;
			cout << ip_buffer << '\t' << mac_buffer << endl;
			fout_wol << mac_buffer << "\t\t" << ip_buffer << endl;

		}
	}
	else
	{
		std::cerr << "Error: file not found." << endl;
	}
	fin.close();
	fout_wol.close();
#endif // WOL
	std::ifstream fin("201 RAW.txt");
	std::ofstream fout("201.dhcpd");
	fin.close();
	if (fin.is_open())
	{
		const int IP_BUFFER_SIZE = 16;
		const int MAC_BUFFER_SIZE = 18;
		char sz_IP_buffer[IP_BUFFER_SIZE] = {};
		char sz_MAC_buffer[MAC_BUFFER_SIZE] = {};
		for(int i = 1; !fin.eof();i++)
		{
			fin >> sz_IP_buffer >> sz_MAC_buffer;
			cout << "host-" << i << endl;
			cout << "{\n";
			cout << "\thardware ethernet:\t" << sz_MAC_buffer << ";\n";
			cout << "\tfixed-address:\t" << sz_IP_buffer << ";\n";
			cout << "}\n";
		}
	}
	else
	{
		std::cerr << "Error: file not found" << endl;
	}
	fout.close();
	fin.close();
			/*fout_dhcpd << "host-" << cnt++ << endl;
			fout_dhcpd << "{" << endl;
			fout_dhcpd << "\thardware ethernet\t" << mac_buffer << endl;
			fout_dhcpd << "\tfixed-address\t" << ip_buffer << endl;
			fout_dhcpd << "}" << endl << endl;
	fout_dhcpd.close();*/
	//system("notepad 201.WOL.txt");
}