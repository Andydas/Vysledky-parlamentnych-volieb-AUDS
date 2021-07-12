#include "politicka_strana.h"

PolitickaStrana::PolitickaStrana(int kod, std::wstring nazov, std::wstring skratenyNazov) :
	kod_(kod), nazov_(nazov), skratenyNazov_(skratenyNazov), pomocnySucet_(0)
{
	platneHlasy_ = new HashTable<int, int>;
}

PolitickaStrana::~PolitickaStrana()
{
	delete platneHlasy_;
	platneHlasy_ = nullptr;
}

int PolitickaStrana::getPlatneHlasy(UzemnaJednotka* pUzemnaJednotka)
{
	if (platneHlasy_->containsKey(pUzemnaJednotka->getKod()))
	{
		return (*platneHlasy_)[pUzemnaJednotka->getKod()];
	}
	else
	{
		return 0;
	}
}

void PolitickaStrana::naplnUdaje(int kodObce, int platne)
{
	

	if (!platneHlasy_->containsKey(kodObce))
	{
		platneHlasy_->insert(kodObce, platne);
		if ((*uzemneJednotky_)[kodObce]->getPredok() != nullptr)
		{
			naplnUdaje((*uzemneJednotky_)[kodObce]->getPredok()->getKod(), platne);
		}
	}
	else
	{
		(*platneHlasy_)[kodObce] += platne;
		if ((*uzemneJednotky_)[kodObce]->getPredok() != nullptr)
		{
			naplnUdaje((*uzemneJednotky_)[kodObce]->getPredok()->getKod(), platne);
		}
	}
}

