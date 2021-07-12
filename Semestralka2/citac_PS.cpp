#include "citac_PS.h"
#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <io.h>
#include <fcntl.h>
#include <sstream>

using namespace std;

//treba dorobit poznamku X
HashTable<int, PolitickaStrana*>* CitacPS::citaj(std::string nazov)
{

	static const int  CISLO_SUBJEKTU = 0;
	static const int  NAZOV = 1;
	static const int  SKRATENY_NAZOV = 2;
	static const int  POZNAMKA = 5;

	HashTable<int, PolitickaStrana*>* output = new HashTable<int, PolitickaStrana*>();

	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);


	ifstream vstup(nazov);
	wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(vstup.rdbuf());
	wistream subor(&conv);

	wstring riadok;
	int cisloPS = 0;
	wstring nazovPS;
	wstring kratkyNazovPS;
	wstring poznamka;
	getline(subor, riadok);

	while (getline(subor, riadok))
	{
		wstringstream ss(riadok);

		wstring stlpec;
		int index = 0;

		while (getline(ss, stlpec, L'|'))
		{
			if ((index >= CISLO_SUBJEKTU && index <= SKRATENY_NAZOV) || index == POZNAMKA)
			{
				if (index == CISLO_SUBJEKTU)
				{
					cisloPS = stoi(stlpec);
					index++;
				}
				else if (index == NAZOV)
				{
					nazovPS = stlpec;
					index++;
				}
				else if (index == SKRATENY_NAZOV)
				{
					kratkyNazovPS = stlpec;
					index++;
					if (!output->containsKey(cisloPS))
					{
						output->insert(cisloPS, new PolitickaStrana(cisloPS, nazovPS, kratkyNazovPS));
					}
				}
				else
				{
					poznamka = stlpec;
					index++;
					if (poznamka == L"X")
					{
						delete (*output)[cisloPS];
						output->remove(cisloPS);
					}
						
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

void CitacPS::napln(HashTable<int, PolitickaStrana*>* table, std::string nazov)
{

	static const int  KOD_OBCE = 0;
	static const int  CISLO_SUBKJEKTU = 2;
	static const int  PLATNE_HLASY = 3;
	static const int  PREDSNOSTNE_HLASY = 5;


	ifstream vstup(nazov);

	std::string riadok;
	int kodObce; //0
	int cisloPS; //2
	int platne; //3
	int prednostne; //5

	getline(vstup, riadok);

	while (getline(vstup, riadok))
	{
		stringstream ss(riadok);
		string stlpec;
		int index = 0;

		while (getline(ss, stlpec, '|'))
		{
			if (index == KOD_OBCE || index == CISLO_SUBKJEKTU || 
				index == PLATNE_HLASY || index == PREDSNOSTNE_HLASY)
			{
				if (index == KOD_OBCE)
				{
					kodObce = stoi(stlpec);
					index++;
				}
				else if (index == CISLO_SUBKJEKTU)
				{
					cisloPS = stoi(stlpec);
					index++;
				}
				else if (index == PLATNE_HLASY)
				{
					platne = stoi(stlpec);
					index++;
				}
				else //index ==5
				{
					prednostne = stoi(stlpec);
					index++;
					(*table)[cisloPS]->naplnUdaje(kodObce, platne);
				}
			}
			else
			{
				index++;
			}
		}
	}
}
