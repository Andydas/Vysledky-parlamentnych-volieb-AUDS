#include "app.h"
#include "citac_uj.h"
#include "citac_ps.h"
#include <string>
#include <iostream>
#include "citac_K.h"
#include "typ_UJ.h"
#include "manazer_uloha_3.h"
#include "../structures/table/sorting/quick_sort.h"
#include "manazer_uloha_4.h"
#include "v_kriterium_min_ps_hlasy_ziskane.h"
#include "comparator_uj_nazov.h"
#include "sorter_uj_nazov.h"
#include "manazer_uloha_5.h"
#include "manazer_uloha_6.h"
#include "manazer_uloha_7.h"
#include "manazer_uloha_8.h"
#include <stdlib.h>
#include "filter_k_prislusnost.h"
#include "manazer_uloha_9.h"
#include "manazer_uloha_10.h"

using namespace std;
using namespace structures;

App::App()
{
	uzemneJednotky_ = nullptr;
	politickeStrany_ = nullptr;
	kandidati_ = nullptr;
	nacitajTabulky();
	hlavneMenu();
}

App::~App()
{
	clear();
	delete uzemneJednotky_;
	delete politickeStrany_;
	delete kandidati_;

	uzemneJednotky_ = nullptr;
	politickeStrany_ = nullptr;
	kandidati_ = nullptr;
}


void App::hlavneMenu()
{
	while (true)
	{
		//system("cls");
		int vyber;
		wcout << "Vyber si ulohu: " << endl;
		wcout << "3  - Vypisanie informacii o UJ" << endl;
		wcout << "4  - Zoradenie UJ podla filtra " << endl;
		wcout << "5  - Vysledky PS vo zvolenych UJ " << endl;
		wcout << "6  - Zoradenie PS podla vysledkov vo zvolenych UJ" << endl;
		wcout << "7  - Vypisanie VKriterii pre PS vo zvolenych UJ" << endl;
		wcout << "8  - Zoradenie UJ podla uspesnosti zvoleneho PS" << endl;
		wcout << "9  - Vypisanie vysledkov K za PS v UJ" << endl;
		wcout << "10 - Zoradenie vysledkov K za PS v UJ" << endl;
		wcout << "0 Ukonci program" << endl;
		wcin >> vyber;
		if (vyber == 0)
		{
			break;
		}
		while (vyber < 3 || vyber > 10 || vyber == 1 || vyber == 2)
		{
			wcout << "Neplatna volba, opakuj" << endl;
			wcin >> vyber;
		}
		
		spustiUlohu(vyber);
	}
}

void App::nacitajTabulky()
{
	nacitajUJ();
	nacitajPS();
	nacitajK();
}

void App::spustiUlohu(int uloha)
{
	static const int TRETIA = 3;
	static const int STVRTA = 4;
	static const int PIATA = 5;
	static const int SIESTA = 6;
	static const int SIEDMA = 7;
	static const int OSMA = 8;
	static const int DEVIATA = 9;

	if (uloha == TRETIA)
	{
		ManazerUloha3 manzer3(uzemneJednotky_);
		manzer3.spusti();
	}
	else if (uloha == STVRTA)
	{
		ManazerUloha4 manzer4(uzemneJednotky_);
		manzer4.spusti();
	}
	else if (uloha == PIATA)
	{
		ManazerUloha5 manzer5(uzemneJednotky_, politickeStrany_);
		manzer5.spusti();
	}
	else if (uloha == SIESTA)
	{
		ManazerUloha6 manzer6(uzemneJednotky_, politickeStrany_);
		manzer6.spusti();
	}
	else if (uloha == SIEDMA)
	{
		ManazerUloha7 manzer7(uzemneJednotky_, politickeStrany_);
		manzer7.spusti();
	}
	else if(uloha == OSMA)
	{
		ManazerUloha8 manzer8(uzemneJednotky_, politickeStrany_);
		manzer8.spusti();
	}
	else if(uloha == DEVIATA)
	{
		ManazerUloha9 manzer9(uzemneJednotky_, politickeStrany_, kandidati_);
		manzer9.spusti();
	}
	else 
	{
		ManazerUloha10 manzer10(uzemneJednotky_, politickeStrany_, kandidati_);
		manzer10.spusti();
	}
	

}

void App::nacitajUJ()
{
	CitacUJ citac;
	uzemneJednotky_ = citac.citaj("CSV/NRSR_2020_SK_tab0c.csv");
	citac.napln(uzemneJednotky_, "CSV/NRSR_2020_SK_tab02e.csv");
}

void App::nacitajPS()
{
	CitacPS citac;
	politickeStrany_ = citac.citaj("CSV/NRSR_2020_SK_tab0a.csv");

	if (uzemneJednotky_ == nullptr)
	{
		wcout << L"Najskor nacitaj udaje do politickej strany." << endl;
		return;
	}
	for (auto prvok : *politickeStrany_)
	{
		prvok->accessData()->setUJ(uzemneJednotky_);
	}

	citac.napln(politickeStrany_, "CSV/NRSR_2020_SK_tab03f.csv");
}

void App::nacitajK()
{
	CitacK citac;
	kandidati_ = citac.citaj("CSV/NRSR_2020_SK_tab0b.csv");

	if (uzemneJednotky_ == nullptr)
	{
		wcout << L"Najskor nacitaj udaje do kandidata." << endl;
		return;
	}
	for (auto prvok : *kandidati_)
	{
		prvok->accessData()->setUJ(uzemneJednotky_);
	}
	citac.napln(kandidati_, "CSV/NRSR_2020_SK_tab07f.csv");
}

void App::testik()
{


	/*for (auto prvok : *kandidati_)
	{
		wcout << prvok->accessData()->getMeno() << endl;
	}*/


	//test vyberoveho kriteria
	/*VKriteriumMinPSHlasov* vk = new VKriteriumMinPSHlasov((*uzemneJednotky_)[1]);

	wcout << vk->vyber(politickeStrany_)->getNazov() << L" "<< vk->vyber(politickeStrany_)->getPlatneHlasy((*uzemneJednotky_)[0]);*/

	
	/*FilterUJPrislusnost* filter = new FilterUJPrislusnost(true, (*uzemneJednotky_)[502]);

	UnsortedSequenceTable<int, UzemnaJednotka*>* output = nullptr;
	
	output = filter->filtruj(uzemneJednotky_);

	KriteriumUJNazov* krit = new KriteriumUJNazov();

	

	ComparatorUJNazov* komp = new ComparatorUJNazov(true);
	QuickSort<int, UzemnaJednotka*>* sorter = new QuickSort<int, UzemnaJednotka*>(komp);
	sorter->sort(output);

	for (auto prvok : *output)
	{
		wcout << krit->ohodnot(prvok->accessData()) << endl;
	}

	delete filter;
	delete output;
	delete krit;*/
	/*delete komp;
	delete sorter;*/

	/*SorterUJNazov* sorter = new SorterUJNazov(true);
	delete sorter;*/

	/*UnsortedSequenceTable<int, UzemnaJednotka*>* output = nullptr;
	FilterUJPrislusnost* filter = new FilterUJPrislusnost(true, (*uzemneJednotky_)[0]);
	output = filter->filtruj(uzemneJednotky_);
	delete filter;
	KriteriumUJPrislusnost krit((*uzemneJednotky_)[502]);
	
	for (auto prvok : *output)
	{
		wcout<< prvok->accessData()->getNazov() << endl;
		wcout << to_wstring(krit.ohodnot(prvok->accessData())) << endl;
		wcout << endl;
		wcout << endl;
	}
	delete output;*/



	/*ManazerUloha6 manazer(uzemneJednotky_, politickeStrany_);
	wcout << L"****************************************************************" << endl;
	wcout << L"VARIANT A" << endl;
	wcout << L"****************************************************************" << endl;
	manazer.spusti();*/
	/*wcout << L"****************************************************************" << endl;
	wcout << L"VARIANT B" << endl;
	wcout << L"****************************************************************" << endl;
	manazer.variantB(TypUJ::OBEC, true, (*uzemneJednotky_)[502], 1, 100, 1, 100000);
	wcout << L"****************************************************************" << endl;
	wcout << L"VARIANT C" << endl;
	wcout << L"****************************************************************" << endl;
	manazer.variantC(TypUJ::OBEC, true, (*uzemneJednotky_)[502], 1, 100, 1, 100000);*/

}


void App::clear()
{
	if (uzemneJednotky_ != nullptr)
	{
		for (auto prvok : *uzemneJednotky_)
		{
			delete prvok->accessData();
		}
	}
	if (politickeStrany_ != nullptr)
	{
		for (auto prvok : *politickeStrany_)
		{
			delete prvok->accessData();
		}
	}
	if (kandidati_ != nullptr)
	{
		for (auto prvok : *kandidati_)
		{
			delete prvok->accessData();
		}
	}
}
