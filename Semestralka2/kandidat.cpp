#include "kandidat.h"

Kandidat::Kandidat(int kod, wstring meno, wstring priezvisko) :
	 kod_(kod), meno_(meno), priezvisko_(priezvisko) 
{
	platneHlasy_ = new HashTable<int, int>;
}

Kandidat::~Kandidat()
{
	delete platneHlasy_;
	platneHlasy_ = nullptr;
}

wstring Kandidat::getMeno()
{
	wstring vystup;
	vystup = meno_ + L" " + priezvisko_;
	return vystup;
}

int Kandidat::getPlatneHlasy(UzemnaJednotka* pUzemnaJednotka)
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

void Kandidat::naplnUdaje(int kodObce, int platne)
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
