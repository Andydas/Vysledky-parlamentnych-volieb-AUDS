#include "manazer_uloha_5.h"
#include "filter_ps_nazov.h"
#include "kriterium_ps_hlasy_ziskane.h"
#include "kriterium_uj_zucastneni_volici.h"
#include "kriterium_uj_podiel_platnych_hlasov.h"
#include "filter_ps_vsetko.h"

ManazerUloha5::ManazerUloha5(Table<int, UzemnaJednotka*>* uzemneJednotky, Table<int, PolitickaStrana*>* politickeStrany) :
	uzemneJednotky_(uzemneJednotky), politickeStrany_(politickeStrany), 
	citacParamUJ_(new CitacParamFilterUJ(uzemneJednotky_)), citacParamPS_(new CitacParamFilterPS(politickeStrany_))
{

}

ManazerUloha5::~ManazerUloha5()
{
	delete citacParamUJ_;
	delete citacParamPS_;
}



void ManazerUloha5::spusti()
{
	wcout << L"Nacitaj parametre filtra pre uzemnu jednotku" << endl;
	FilterUJTyp* filterTyp = citacParamUJ_->nacitajFilterTyp();
	FilterUJNazov* filterUJNazov = citacParamUJ_->nacitajFilterNazov();
	FilterUJUcast* filterUcast = citacParamUJ_->nacitajFilterUcast();
	FilterUJVolici* filterVolici = citacParamUJ_->nacitajFilterVolici();

	wcout << L"Nacitaj parametre filtra pre politicky subjekt" << endl;
	FilterPSNazov* filterPSNazov = citacParamPS_->nacitajFilterNazov();

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

	if (filterPSNazov == nullptr)
	{
		FilterPSVsetko filterVsetko;
		outputPS = filterVsetko.filtruj(politickeStrany_);
	}
	else
	{
		outputPS = filterPSNazov->filtruj(politickeStrany_);
	}


	KriteriumUJVolici kritVolici;
	KriteriumUJZucastneniVolici kritZucastneni;
	KriteriumUJUcast kritUcast;
	KriteriumUJPodielPlatnychHlasov kritPodiel;
	
	wcout << endl << endl;
	wcout << "VYSLEDOK:" << endl << endl;
	for (auto prvokPS : *outputPS)
	{

		
		for (auto prvokUJ : *outputUJ)
		{
			wcout << endl;
			wcout << prvokPS->accessData()->getNazov() << endl;
			wcout << prvokUJ->accessData()->getNazov() << endl;
			KriteriumPSHlasyZiskane* kritPSHlasy = new KriteriumPSHlasyZiskane(prvokUJ->accessData());
			wcout << kritPSHlasy->ohodnot(prvokPS->accessData()) << L" ziskanych hlasov" << endl;
			wcout << kritVolici.ohodnot(prvokUJ->accessData()) << L" volicov, " << endl
				<< kritZucastneni.ohodnot(prvokUJ->accessData()) << L" zucastnenych volicov, " << endl
				<< kritUcast.ohodnot(prvokUJ->accessData()) << L"% ucast, " << endl
				<< kritPodiel.ohodnot(prvokUJ->accessData()) << L"% podiel platnych hlasov." << endl;

			wcout << endl;
			wcout << endl;
			delete kritPSHlasy;
		}

	}
		
	
	delete outputUJ;
	delete outputPS;
	delete filterPSNazov;
	delete filterTyp;
	delete filterUJNazov;
	delete filterUcast;
	delete filterVolici;
}
