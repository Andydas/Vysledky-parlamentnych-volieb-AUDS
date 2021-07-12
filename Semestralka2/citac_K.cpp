#include "citac_K.h"
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
#include <string>
#include <codecvt>
#include <sstream>

HashTable<int, Kandidat*>* CitacK::citaj(std::string nazov)
{
	static const int  CISLO_SUBJEKTU = 0;
	static const int  CISLO_KANDIDATA = 1;
	static const int  MENO = 2;
	static const int  PRIEZVISKO = 3;
	static const int  POZNAMKA = 8;

	HashTable<int, Kandidat*>* output = new HashTable<int, Kandidat*>;

	_setmode(_fileno(stdin), _O_U16TEXT);
	_setmode(_fileno(stdout), _O_U16TEXT);


	ifstream vstup(nazov);
	wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(vstup.rdbuf());
	wistream subor(&conv);

	wstring riadok;
	int cisloPS = 0;
	int cisloK = 0;
	wstring meno;
	wstring priezvisko;
	wstring poznamka;

	getline(subor, riadok);

	while (getline(subor, riadok))
	{	
		wstringstream ss(riadok);
		wstring stlpec;
		int index = 0;

		while (getline(ss, stlpec, L'|'))
		{
			if (index == CISLO_SUBJEKTU || index==CISLO_KANDIDATA || 
				index <= MENO || index== PRIEZVISKO || index == POZNAMKA)
			{
				if (index == CISLO_SUBJEKTU)
				{
					cisloPS = stoi(stlpec) * 1000;
					index++;
				}
				else if (index == CISLO_KANDIDATA)
				{
					cisloK = stoi(stlpec);
					index++;
				}
				else if (index == MENO)
				{
					meno = stlpec;
					index++;
				}
				else if (index == PRIEZVISKO)
				{
					priezvisko = stlpec;
					index++;
					if (!output->containsKey(cisloPS + cisloK))
					{
						output->insert(cisloPS + cisloK, new Kandidat(cisloPS + cisloK, meno, priezvisko));
					}
					
				}
				else 
				{	
					poznamka = stlpec;
					index++;
					if (poznamka == L"X")
					{
						delete(*output)[cisloPS + cisloK];
						output->remove(cisloPS + cisloK);						
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

void CitacK::napln(HashTable<int, Kandidat*>* table, std::string nazov)
{
	static const int  KOD_OBCE = 0;
	static const int  CISLO_SUBKJEKTU = 2;
	static const int  CISLO_KANDIDATA = 3;
	static const int  PLATNE_HLASY = 4;
	static const int  POZNAMKA = 5;


	ifstream vstup(nazov);

	std::string riadok;
	int kodObce; //0
	int cisloPS; //2
	int cisloK; //3
	int platne; //4
	wstring poznamka;

	getline(vstup, riadok);

	while (getline(vstup, riadok))
	{
		stringstream ss(riadok);
		string stlpec;
		int index = 0;

		while (getline(ss, stlpec, '|'))
		{
			if (index == KOD_OBCE || index == CISLO_SUBKJEKTU ||
				index == CISLO_KANDIDATA || index == PLATNE_HLASY ||
				index == POZNAMKA)
			{
				if (index == KOD_OBCE)
				{
					kodObce = stoi(stlpec);
					index++;
				}
				else if (index == CISLO_SUBKJEKTU)
				{
					cisloPS = stoi(stlpec) * 1000;
					index++;
				}
				else if (index == CISLO_KANDIDATA)
				{
					cisloK = stoi(stlpec);
					index++;
				}
				else //index ==5
				{
					platne = stoi(stlpec);
					index++;
					if ((*table).containsKey(cisloPS + cisloK))
					{
						(*table)[cisloPS + cisloK]->naplnUdaje(kodObce, platne);
					}
					
				}
			}
			else
			{
				index++;
			}
		}
	}
}
