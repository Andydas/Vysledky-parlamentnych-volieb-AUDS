#include "manazer_uloha_6.h"
#include "kriterium_ps_hlasy_ziskane.h"
#include "filter_ps_vsetko.h"
#include "sorter_ps_sucet.h"

ManazerUloha6::ManazerUloha6(Table<int, UzemnaJednotka*>* uzemneJednotky, Table<int, PolitickaStrana*>* politickeStrany):
	uzemneJednotky_(uzemneJednotky), politickeStrany_(politickeStrany),
	citacParamUJ_(new CitacParamFilterUJ(uzemneJednotky_)), citacParamPS_(new CitacParamFilterPS(politickeStrany_))
{
}

ManazerUloha6::~ManazerUloha6()
{
	delete citacParamUJ_;
	delete citacParamPS_;
	citacParamPS_ = nullptr;
	citacParamUJ_ = nullptr;
}

void ManazerUloha6::spusti()
{

	wcout << L"Nacitaj parametre filtra pre uzemnu jednotku" << endl;
	FilterUJTyp* filterTyp = citacParamUJ_->nacitajFilterTyp();
	FilterUJPrislusnost* filterPrislusnost = citacParamUJ_->nacitajFilterPrislusnost();
	FilterUJUcast* filterUcast = citacParamUJ_->nacitajFilterUcast();
	FilterUJVolici* filterVolici = citacParamUJ_->nacitajFilterVolici();

	UnsortedSequenceTable<int, UzemnaJednotka*>* outputUJ = nullptr;
	UnsortedSequenceTable<int, UzemnaJednotka*>* tempUJ = nullptr;
	UnsortedSequenceTable<int, PolitickaStrana*>* outputPS = nullptr;

	int indexUJ = 0;

	if (filterTyp != nullptr)
	{
		outputUJ = filterTyp->filtruj(uzemneJednotky_);
		indexUJ++;
	}
	if (filterPrislusnost != nullptr)
	{
		if (indexUJ == 0)
		{
			outputUJ = filterPrislusnost->filtruj(uzemneJednotky_);
			indexUJ++;
		}
		else
		{
			tempUJ = outputUJ;
			outputUJ = filterPrislusnost->filtruj(outputUJ);
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

	FilterPSVsetko filterVsetko;
	outputPS = filterVsetko.filtruj(politickeStrany_);

	


	for (auto prvokPS : *outputPS)
	{
		int suma = 0;
		for (auto prvokUJ : *outputUJ)
		{
			KriteriumPSHlasyZiskane krit(prvokUJ->accessData());
			suma += krit.ohodnot(prvokPS->accessData());
		}
		prvokPS->accessData()->setPomocnySucet(suma);
		//wcout << prvokPS->accessData()->getNazov() << L" " << to_wstring(suma) << endl;
	}

	int vzostupne;
	wcout << L"Ako zoradime?" << endl << L"1 - Vzostupne" << endl << "2 - Zostupne" << endl;
	wcin >> vzostupne;

	SorterPSSucet* sorter = new SorterPSSucet(vzostupne == 1);
	sorter->sort(outputPS);

	wcout << endl << endl;
	wcout << "VYSLEDOK:" << endl << endl;


	for (auto prvokPS : *outputPS)
	{
		wcout << prvokPS->accessData()->getNazov() << endl;
		wcout << L"Pocet hlasov celkovo : " << prvokPS->accessData()->getPomocnySucet() << endl;
		
		for (auto prvokUJ : *outputUJ)
		{
			KriteriumPSHlasyZiskane krit(prvokUJ->accessData());
			wcout << prvokUJ->accessData()->getNazov() << L": " << krit.ohodnot(prvokPS->accessData())<< L" hlasov." << endl;
		}
		wcout << endl;
		wcout << endl;
	}

	delete sorter;
	delete filterTyp;
	delete filterUcast;
	delete filterVolici;
	delete filterPrislusnost;
	delete outputPS;
	delete outputUJ;
}
