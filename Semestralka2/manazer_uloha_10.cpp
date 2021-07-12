#include "manazer_uloha_10.h"
#include "kriteirum_k_prednostne_hlasy.h"
#include "sorter_k_sucet.h"

ManazerUloha10::ManazerUloha10(Table<int, UzemnaJednotka*>* uzemneJednotky, Table<int, PolitickaStrana*>* politickeStrany, Table<int, Kandidat*>* kandidati):
	uzemneJednotky_(uzemneJednotky), kandidati_(kandidati), politickeStrany_(politickeStrany), 
	citacParamK_(new CitacParamFilterK(kandidati, politickeStrany)), citacParamUJ_(new CitacParamFilterUJ(uzemneJednotky))
{
}

ManazerUloha10::~ManazerUloha10()
{
	delete citacParamK_;
	citacParamK_ = nullptr;
	delete citacParamUJ_;
	citacParamUJ_ = nullptr;
}

void ManazerUloha10::spusti()
{
	wcout << L"Nacitaj parametre filtra pre uzemnu jednotku" << endl;
	FilterUJTyp* filterTyp = citacParamUJ_->nacitajFilterTyp();
	FilterUJPrislusnost* filterUJPrislusnost = citacParamUJ_->nacitajFilterPrislusnost();
	FilterUJUcast* filterUcast = citacParamUJ_->nacitajFilterUcast();
	FilterUJVolici* filterVolici = citacParamUJ_->nacitajFilterVolici();
	wcout << L"Nacitaj parametre filtra pre kandidata" << endl;
	FilterKPrislusnost* filterKPrislusnost = citacParamK_->nacitajFilterPrislusnost();

	UnsortedSequenceTable<int, UzemnaJednotka*>* outputUJ = nullptr;
	UnsortedSequenceTable<int, UzemnaJednotka*>* tempUJ = nullptr;
	UnsortedSequenceTable<int, Kandidat*>* outputK = nullptr;

	//filtrujem uzemne jednotky
	int indexUJ = 0;

	if (filterTyp != nullptr)
	{
		outputUJ = filterTyp->filtruj(uzemneJednotky_);
		indexUJ++;
	}
	if (filterUJPrislusnost != nullptr)
	{
		if (indexUJ == 0)
		{
			outputUJ = filterUJPrislusnost->filtruj(uzemneJednotky_);
			indexUJ++;
		}
		else
		{
			tempUJ = outputUJ;
			outputUJ = filterUJPrislusnost->filtruj(outputUJ);
			delete tempUJ;
			indexUJ++;
		}
	}
	if (filterUcast != nullptr)
	{
		if (indexUJ == 0)
		{
			outputUJ = filterUcast->filtruj(uzemneJednotky_);
			indexUJ++;
		}
		else
		{
			tempUJ = outputUJ;
			outputUJ = filterUcast->filtruj(outputUJ);
			delete tempUJ;
			indexUJ++;
		}
	}
	if (filterVolici != nullptr)
	{
		if (indexUJ == 0)
		{
			outputUJ = filterVolici->filtruj(uzemneJednotky_);
			indexUJ++;
		}
		else
		{
			tempUJ = outputUJ;
			outputUJ = filterVolici->filtruj(outputUJ);
			delete tempUJ;
			indexUJ++;
		}
	}
	if (indexUJ == 0)
	{
		FilterUJPrislusnost* filter = new FilterUJPrislusnost(true, (*uzemneJednotky_)[0]);
		outputUJ = filter->filtruj(uzemneJednotky_);
		delete filter;
	}

	outputK = filterKPrislusnost->filtruj(kandidati_);


	for (auto prvokK : *outputK)
	{
		int suma = 0;
		for (auto prvokUJ : *outputUJ)
		{
			KriteriumKPrednostneHlasy krit(prvokUJ->accessData());
			suma += krit.ohodnot(prvokK->accessData());
		}
		prvokK->accessData()->setPomocnySucet(suma);
	}

	int vzostupne;
	wcout << L"Ako zoradime?" << endl << L"1 - Vzostupne" << endl << "2 - Zostupne" << endl;
	wcin >> vzostupne;

	SorterKSucet* sorter = new SorterKSucet(vzostupne == 1);
	sorter->sort(outputK);

	wcout << endl << endl;
	wcout << "VYSLEDOK:" << endl << endl;


	for (auto prvokK : *outputK)
	{
		wcout << prvokK->accessData()->getMeno() << L", kandidat za politicku stranu: " <<
			(*politickeStrany_)[prvokK->getKey() / 1000]->getNazov() << endl;

		wcout << L"Pocet prednostnych hlasov celkovo : " << prvokK->accessData()->getPomocnySucet() << endl;

		for (auto prvokUJ : *outputUJ)
		{
			KriteriumKPrednostneHlasy krit(prvokUJ->accessData());
			wcout << prvokUJ->accessData()->getNazov() << L": " << krit.ohodnot(prvokK->accessData()) << L" hlasov." << endl;
		}
		wcout << endl;
		wcout << endl;
	}

	delete sorter;
	delete filterTyp;
	delete filterUcast;
	delete filterVolici;
	delete filterUJPrislusnost;
	delete filterKPrislusnost;
	delete outputK;
	delete outputUJ;
}
