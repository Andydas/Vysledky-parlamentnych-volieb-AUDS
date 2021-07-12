#include "manazer_uloha_7.h"
#include "filter_ps_vsetko.h"
#include "v_kriterium_max_ps_hlasy_ziskane.h"
#include "v_kriterium_min_ps_hlasy_ziskane.h"

ManazerUloha7::ManazerUloha7(Table<int, UzemnaJednotka*>* uzemneJednotky, Table<int, PolitickaStrana*>* politickeStrany):
	uzemneJednotky_(uzemneJednotky), politickeStrany_(politickeStrany),
	citacParamUJ_(new CitacParamFilterUJ(uzemneJednotky))
{
}

ManazerUloha7::~ManazerUloha7()
{
	delete citacParamUJ_;
	citacParamUJ_ = nullptr;
}

void ManazerUloha7::spusti()
{
	wcout << L"Nacitaj parametre filtra pre uzemnu jednotku" << endl;
	FilterUJTyp* filterTyp = citacParamUJ_->nacitajFilterTyp();
	FilterUJNazov* filterUJNazov = citacParamUJ_->nacitajFilterNazov();
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
	if (filterUJNazov != nullptr)
	{
		if (indexUJ == 0)
		{
			outputUJ = filterUJNazov->filtruj(uzemneJednotky_);
			indexUJ++;
		}
		else
		{
			tempUJ = outputUJ;
			outputUJ = filterUJNazov->filtruj(outputUJ);
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

	wcout << endl << endl;
	wcout << "VYSLEDOK:" << endl << endl;

	for (auto prvok : * outputUJ)
	{
		wcout << prvok->accessData()->getNazov() << endl;
		VKriteriumMaxPSHlasov kritMax(prvok->accessData());
		wcout<< L"Najviac ziskanych hlasov: "<<kritMax.vyber(politickeStrany_)->getNazov()<<endl;
		VKriteriumMinPSHlasov kritMin(prvok->accessData());
		wcout << L"Najmenej ziskanych hlasov: " << kritMin.vyber(politickeStrany_)->getNazov() << endl;
		wcout << endl << endl;
	}



	delete filterTyp;
	delete filterUJNazov;
	delete filterUcast;
	delete filterVolici;
	delete outputUJ;
	delete outputPS;
}
