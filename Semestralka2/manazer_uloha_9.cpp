#include "manazer_uloha_9.h"
#include "kriteirum_k_prednostne_hlasy.h"
#include "kriterium_uj_zucastneni_volici.h"
#include "kriterium_uj_podiel_platnych_hlasov.h"

ManazerUloha9::ManazerUloha9(Table<int, UzemnaJednotka*>* uzemneJednotky, Table<int, PolitickaStrana*>* politickeStrany, Table<int, Kandidat*>* kandidati) :
	uzemneJednotky_(uzemneJednotky), politickeStrany_(politickeStrany), kandidati_(kandidati),
	citacParamUJ_(new CitacParamFilterUJ(uzemneJednotky)), citacParamK_(new CitacParamFilterK(kandidati, politickeStrany))
{
}

ManazerUloha9::~ManazerUloha9()
{
	delete citacParamUJ_;
	citacParamUJ_ = nullptr;
	delete citacParamK_;
	citacParamK_ = nullptr;
}

void ManazerUloha9::spusti()
{
	wcout << L"Nacitaj parametre filtra pre uzemnu jednotku" << endl;
	FilterUJTyp* filterTyp = citacParamUJ_->nacitajFilterTyp();
	FilterUJNazov* filterUJNazov = citacParamUJ_->nacitajFilterNazov();
	FilterUJUcast* filterUcast = citacParamUJ_->nacitajFilterUcast();
	FilterUJVolici* filterVolici = citacParamUJ_->nacitajFilterVolici();
	wcout << L"Nacitaj parametre filtra pre kandidata" << endl;
	FilterKNazov* filterKNazov = citacParamK_->nacitajFilterNazov();

	UnsortedSequenceTable<int, UzemnaJednotka*>* outputUJ = nullptr;
	UnsortedSequenceTable<int, UzemnaJednotka*>* tempUJ = nullptr;
	UnsortedSequenceTable<int, Kandidat*>* outputK = nullptr;

	KriteriumKNazov kritNazov;
	KriteriumUJVolici kritVolici;
	KriteriumUJZucastneniVolici kritZucastneni;
	KriteriumUJUcast kritUcast;
	KriteriumUJPodielPlatnychHlasov kritPodiel;

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

	outputK = filterKNazov->filtruj(kandidati_);

	if (indexUJ == 0)
	{
		FilterUJPrislusnost* filter = new FilterUJPrislusnost(true, (*uzemneJednotky_)[0]);
		outputUJ = filter->filtruj(uzemneJednotky_);
		delete filter;
	}

	wcout << endl << endl;
	wcout << "VYSLEDOK:" << endl << endl;

	for (auto prvokK : *outputK)
	{
		wcout << prvokK->accessData()->getMeno() << L", kandidat za politicku stranu: " << 
			(*politickeStrany_)[prvokK->getKey()/1000]->getNazov() << endl;
		wcout << L"************************************************************" << endl;

		for (auto prvokUJ : *outputUJ)
		{
			wcout << prvokUJ->accessData()->getNazov() << endl;
			KriteriumKPrednostneHlasy kritHlasy(prvokUJ->accessData());
			wcout << kritHlasy.ohodnot(prvokK->accessData()) << L" prednostnych hlasov." << endl;
			wcout << kritVolici.ohodnot(prvokUJ->accessData()) << L" volicov, " << endl
				<< kritZucastneni.ohodnot(prvokUJ->accessData()) << L" zucastnenych volicov, " << endl
				<< kritUcast.ohodnot(prvokUJ->accessData()) << L"% ucast, " << endl
				<< kritPodiel.ohodnot(prvokUJ->accessData()) << L"% podiel platnych hlasov." << endl;

			wcout << endl << endl;
		}
	}
	
	delete filterKNazov;
	delete filterTyp;
	delete filterUJNazov;
	delete filterUcast;
	delete filterVolici;
	delete outputUJ;
	delete outputK;
}
