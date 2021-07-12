#include "manazer_uloha_3.h"
#include "filter_uj_nazov.h"
#include "filter_uj_prislusnost.h"
#include "filter_uj_typ.h"
#include "filter_uj_volici.h"
#include "filter_uj_ucast.h"
#include "kriterium_uj_zucastneni_volici.h"
#include "kriterium_uj_odovzdane_obalky.h"
#include "kriterium_uj_podiel_platnych_hlasov.h"
#include "../structures/table/sorting/quick_sort.h"
#include "comparator_uj.h"
#include "comparator_uj_nazov.h"

ManazerUloha3::ManazerUloha3(Table<int, UzemnaJednotka*>* uzemneJednotky) : 
	uzemneJednotky_(uzemneJednotky), citacParam_(new CitacParamFilterUJ(uzemneJednotky))
{
}



void ManazerUloha3::spusti()
{
	FilterUJTyp* filterTyp = citacParam_->nacitajFilterTyp();
	FilterUJPrislusnost* filterPrislusnost = citacParam_->nacitajFilterPrislusnost();

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


	if (index == 0)
	{
		FilterUJPrislusnost* filter = new FilterUJPrislusnost(true, (*uzemneJednotky_)[0]);
		output = filter->filtruj(uzemneJednotky_);
		delete filter;
	}

	wcout << L"Zadaj dodatocny filter." << endl
		<< L"1 - Nazov" << endl << L"2 - Volici" << endl << L"3 - Ucast" << endl;
	int inputKriterium;
	wcin >> inputKriterium;

	if (inputKriterium == 1)
	{
		FilterUJNazov* filterNazov = citacParam_->nacitajFilterNazov();

		if (output->size() != 0)
		{
			if (filterNazov != nullptr)
			{
				if (index == 0)
				{
					output = filterNazov->filtruj(uzemneJednotky_);
					index++;
				}
				else
				{
					temp = output;
					output = filterNazov->filtruj(output);
					delete temp;
					index++;
				}
			}
			
		}
		delete filterNazov;
	}
	else if (inputKriterium == 2)
	{
		FilterUJVolici* filterVolici = citacParam_->nacitajFilterVolici();

		if (output->size() != 0)
		{
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
			
		}
		delete filterVolici;
	}
	else
	{
		FilterUJUcast* filterUcast = citacParam_->nacitajFilterUcast();

		if (output->size() != 0)
		{
			if (filterPrislusnost != nullptr)
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
			
		}
		delete filterUcast;
	}

	wcout << endl << endl;
	wcout << "VYSLEDOK:" << endl << endl;

	vystup(output);

	delete filterTyp;
	delete filterPrislusnost;
	delete output;
	
}


void ManazerUloha3::vystup(Table<int, UzemnaJednotka*>* table)
{
	if (table->size() == 0)
	{
		wcout << L"filtrom nezodpoveda ziaden vystup" << endl;
		wcout << endl;
		return;
	}

	KriteriumUJNazov kritNazov;
	KriteriumUJUcast kritUcast;
	KriteriumUJVolici kritVolici;
	KriteriumUJZucastneniVolici kritZucastneni;
	KriteriumUJOdovzdaneObalky kritZucastneniOsobne(TypOdovzdanie::OSOBNE);
	KriteriumUJOdovzdaneObalky kritZucastneniCudzina(TypOdovzdanie::CUDZINA);
	KriteriumUJOdovzdaneObalky kritZucastneniSpolu(TypOdovzdanie::SPOLU);
	KriteriumUJPodielPlatnychHlasov kritPodiel;

	for (auto prvok : *table)
	{
		//nazov a vyssie uzemne celky
		wcout << L"Uzemna jednotka: " << kritNazov.ohodnot(prvok->accessData()) << endl;
		wcout << L"Vyssie uzemne celky: ";

		UzemnaJednotka* predok = prvok->accessData()->getPredok();
		while (predok != nullptr)
		{
			wcout << kritNazov.ohodnot(predok) << L", ";
			predok = predok->getPredok();
		}
		wcout << endl;
		wcout << L"Ucast: " << kritUcast.ohodnot(prvok->accessData()) << endl;
		wcout << L"Volici: " << kritVolici.ohodnot(prvok->accessData()) << endl;
		wcout << L"Zucastneni volici: " << kritZucastneni.ohodnot(prvok->accessData()) << endl;
		wcout << L"Odovzdane obalky osobne: " << kritZucastneniOsobne.ohodnot(prvok->accessData()) << endl;
		wcout << L"Odovzdane obalky z cudziny: " << kritZucastneniCudzina.ohodnot(prvok->accessData()) << endl;
		wcout << L"Odovzdane obalky spolu: " << kritZucastneniSpolu.ohodnot(prvok->accessData()) << endl;
		wcout << L"Podiel platnych hlasov: " << kritPodiel.ohodnot(prvok->accessData()) << endl;
		wcout << endl << endl;
	}
}
