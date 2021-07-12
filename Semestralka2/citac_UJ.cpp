#include "citac_UJ.h"
#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <sstream>


using namespace structures;

HashTable<int, UzemnaJednotka*>* CitacUJ::citaj(std::string nazov)
{
	static const int KOD_KRAJA = 0;
	static const int NAZOV_KRAJA = 1;
	static const int KOD_OKRESU = 4;
	static const int NAZOV_OKRESU = 5;
	static const int KOD_OBCE = 6;
	static const int NAZOV_OBCE = 7;

	HashTable<int, UzemnaJednotka*>* output = new HashTable<int, UzemnaJednotka*>();
	
	output->insert(0, new UzemnaJednotka(0, L"Slovensko", TypUJ::STAT, nullptr));

	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);

	ifstream vstup(nazov);
	wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(vstup.rdbuf());
	wistream subor(&conv);

	wstring riadok;
	int kraj;
	wstring nkraj;
	int okres;
	wstring nokres;
	int obec;
	wstring nobec;
	int typ;

	getline(subor, riadok);
	                                 
	while (getline(subor, riadok))
	{
		wstringstream ss(riadok);
		wstring stlpec;
		int index = 0;

		while (getline(ss, stlpec, L'|'))
		{
			if (index == KOD_KRAJA || index == NAZOV_KRAJA)
			{
				if (index == KOD_KRAJA)
				{
					kraj = stoi(stlpec);
					index++;
				}
				else
				{
					nkraj = stlpec;
					index++;
					if (!output->containsKey(kraj))
							output->insert(kraj, new UzemnaJednotka(kraj, nkraj, TypUJ::KRAJ, (*output)[0]));

				}
			}
			else if (index == KOD_OKRESU || index == NAZOV_OKRESU)
			{
				if (index == KOD_OKRESU)
				{
					okres = stoi(stlpec);
					index++;
				}
				else
				{
					nokres = stlpec;
					index++;
					if (!output->containsKey(okres))
							output->insert(okres, new UzemnaJednotka(okres, nokres, TypUJ::OKRES, (*output)[kraj]));
				}
			}
			else if (index == KOD_OBCE || index == NAZOV_OBCE)
			{
				if (index == KOD_OBCE)
				{
					obec = stoi(stlpec);
					index++;
				}
				else
				{
					nobec = stlpec;
					index++;
					output->insert(obec, new UzemnaJednotka(obec, nobec, TypUJ::OBEC, (*output)[okres]));
				}
			}
			else
			{
				index++;
			}
		}
	}
	return output;
}

void CitacUJ::napln(HashTable<int, UzemnaJednotka*>* table, std::string nazov)
{
	static const int KOD_OBCE = 0;
	static const int VOLICI = 2;
	static const int ZUCASTNENI = 3;
	static const int OSOBNE = 5;
	static const int CUDZINA = 7;
	static const int PLATNE = 9;

	ifstream vstup(nazov);

	std::string riadok;
	int kodObce; //0
	int volici; //2
	int zucastneni; //3
	int osobne; //5
	int cudzina; //7
	int platne; //9

	getline(vstup, riadok);
	
	while (getline(vstup, riadok))
	{
		stringstream ss(riadok);
		string stlpec;
		int index = 0;

		while (getline(ss, stlpec, '|'))
		{
			if (index == KOD_OBCE || index == VOLICI || index == ZUCASTNENI || 
				index == OSOBNE || index == CUDZINA || index == PLATNE)
			{
				if (index == KOD_OBCE)
				{
					kodObce = stoi(stlpec);
					index++;
				}
				else if (index == VOLICI)
				{
					volici = stoi(stlpec);
					index++;
				}
				else if (index == ZUCASTNENI)
				{
					zucastneni = stoi(stlpec);
					index++;
				}
				else if (index == OSOBNE)
				{
					osobne = stoi(stlpec);
					index++;
				}
				else if (index == CUDZINA)
				{
					cudzina = stoi(stlpec);
					index++;
				}
				else //index ==9
				{
					platne = stoi(stlpec);
					index++;
					(*table)[kodObce]->naplnUdaje(volici, zucastneni, osobne, cudzina, platne);
				}
			}
			else
			{
				index++;
			}
		}
	}

}
