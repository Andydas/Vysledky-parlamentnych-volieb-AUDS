#include "manazer_uloha_4.h"
#include "filter_uj_nazov.h"
#include "filter_uj_prislusnost.h"
#include "filter_uj_typ.h"
#include "filter_uj_volici.h"
#include "filter_uj_ucast.h"
#include "comparator_uj_nazov.h"
#include "comparator_uj_volici.h"
#include "comparator_uj_ucast.h"
#include "../structures/table/sorting/quick_sort.h"
#include "sorter_uj_nazov.h"
#include "sorter_uj_volici.h"
#include "sorter_uj_ucast.h"

using namespace structures;

ManazerUloha4::ManazerUloha4(Table<int, UzemnaJednotka*>* uzemneJednotky) :
	uzemneJednotky_(uzemneJednotky), citacParam_(new CitacParamFilterUJ(uzemneJednotky_))
{
}

void ManazerUloha4::spusti()
{
	FilterUJTyp* filterTyp = citacParam_->nacitajFilterTyp();
	FilterUJPrislusnost* filterPrislusnost = citacParam_->nacitajFilterPrislusnost();
	FilterUJUcast* filterUcast = citacParam_->nacitajFilterUcast();
	FilterUJVolici* filterVolici = citacParam_->nacitajFilterVolici();

	UnsortedSequenceTable<int, UzemnaJednotka*>* output = nullptr;
	UnsortedSequenceTable<int, UzemnaJednotka*>* temp = nullptr;

	int index = 0;

	if (filterTyp != nullptr)
	{
		output = filterTyp->filtruj(uzemneJednotky_);
		index++;
	}
	if (filterPrislusnost != nullptr)
	{
		if (index == 0)
		{
			output = filterPrislusnost->filtruj(uzemneJednotky_);
			index++;
		}
		else
		{
			temp = output;
			output = filterPrislusnost->filtruj(output);
			delete temp;
			index++;
		}
	}
	if (filterUcast != nullptr)
	{
		if (index == 0)
		{
			output = filterUcast->filtruj(uzemneJednotky_);
			index++;
		}
		else
		{
			temp = output;
			output = filterUcast->filtruj(output);
			delete temp;
			index++;
		}
	}
	if (filterVolici != nullptr)
	{
		if (index == 0)
		{
			output = filterVolici->filtruj(uzemneJednotky_);
			index++;
		}
		else
		{
			temp = output;
			output = filterVolici->filtruj(output);
			delete temp;
			index++;
		}
	}

	if (index == 0)
	{
		FilterUJPrislusnost* filter = new FilterUJPrislusnost(true, (*uzemneJednotky_)[0]);
		output = filter->filtruj(uzemneJednotky_);
		delete filter;
	}

	int vzostupne;
	wcout << L"Ako zoradime?" << endl << L"1 - Vzostupne" << endl << "2 - Zostupne" << endl;
	wcin >> vzostupne;

	wcout << L"Zadaj podla ktoreho kriteria chces zoradit vystup." << endl
		<< L"1 - Nazov" << endl << L"2 - Volici" << endl << L"3 - Ucast" << endl;
	int inputKriterium;
	wcin >> inputKriterium;


	wcout << endl << endl;
	wcout << "VYSLEDOK:" << endl << endl;

	if (inputKriterium == 1)
	{
		SorterUJNazov* sortNazov = new SorterUJNazov(vzostupne);

		if (output->size() != 0)
		{
			sortNazov->sort(output);
			for (auto prvok : *output)
			{
				//nazov a vyssie uzemne celky
				wcout << prvok->accessData()->getNazov() << endl;
				//L" - Hodnota kriteria: " << krit->ohodnot(prvok->accessData()) << endl;

			}
		}
		delete sortNazov;
	}
	else if (inputKriterium == 2)
	{
		SorterUJVolici* sortVolici = new SorterUJVolici(vzostupne);

		if (output->size() != 0)
		{
			sortVolici->sort(output);
			for (auto prvok : *output)
			{
				//nazov a vyssie uzemne celky
				wcout << prvok->accessData()->getNazov() << endl;
				//L" - Hodnota kriteria: " << krit->ohodnot(prvok->accessData()) << endl;

			}
		}
		delete sortVolici;
	}
	else 
	{
		SorterUJUcast* sortUcast = new SorterUJUcast(vzostupne);

		if (output->size() != 0)
		{
			sortUcast->sort(output);
			for (auto prvok : *output)
			{
				//nazov a vyssie uzemne celky
				wcout << prvok->accessData()->getNazov() << endl;
				//L" - Hodnota kriteria: " << krit->ohodnot(prvok->accessData()) << endl;

			}
		}
		delete sortUcast;
	}
	wcout << endl << endl;
	

	delete filterTyp;
	delete filterPrislusnost;
	delete filterUcast;
	delete filterVolici;
	delete output;
}
