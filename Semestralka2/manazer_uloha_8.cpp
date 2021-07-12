#include "manazer_uloha_8.h"
#include "filter_ps_vsetko.h"
#include "kriterium_ps_uspesnost.h"
#include "sorter_double.h"

ManazerUloha8::ManazerUloha8(Table<int, UzemnaJednotka*>* uzemneJednotky, Table<int, PolitickaStrana*>* politickeStrany):
	uzemneJednotky_(uzemneJednotky), politickeStrany_(politickeStrany),
	citacParamUJ_(new CitacParamFilterUJ(uzemneJednotky)), citacParamPS_(new CitacParamFilterPS(politickeStrany))
{
}

ManazerUloha8::~ManazerUloha8()
{
	delete citacParamPS_;
	delete citacParamUJ_;
	citacParamPS_ = nullptr;
	citacParamUJ_ = nullptr;
}

void ManazerUloha8::spusti()
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

	FilterPSNazov* filterPSNazov = citacParamPS_->nacitajFilterNazov();
	outputPS = filterPSNazov->filtruj(politickeStrany_);

	UnsortedSequenceTable<int, double>* tempResult = new UnsortedSequenceTable<int, double>();

	for (auto prvokPS : *outputPS)
	{
		for (auto prvokUJ : *outputUJ)
		{
			KriteriumPSUspesnost krit(prvokUJ->accessData());
			tempResult->insert(prvokUJ->accessData()->getKod(), krit.ohodnot(prvokPS->accessData()));
		}
	}

	int vzostupne;
	wcout << L"Ako zoradime?" << endl << L"1 - Vzostupne" << endl << "2 - Zostupne" << endl;
	wcin >> vzostupne;

	if (tempResult->size() == 0)
	{
		wcout << "nevyhovuje";
		return;
	}
	SorterDouble sorter(vzostupne == 1);
	sorter.sort(tempResult);

	wcout << endl << endl;
	wcout << "VYSLEDOK:" << endl << endl;

	for (auto prvok : *tempResult)
	{
		wcout << (*outputUJ)[prvok->getKey()]->getNazov() << L", uspesnost politickej strany: " << to_wstring(prvok->accessData()) << endl;
	}
	wcout << endl << endl;


	delete filterPSNazov;
	delete outputPS;
	delete outputUJ;
	delete tempResult;
	delete filterTyp;
	delete filterPrislusnost;
	delete filterUcast;
	delete filterVolici;
}
