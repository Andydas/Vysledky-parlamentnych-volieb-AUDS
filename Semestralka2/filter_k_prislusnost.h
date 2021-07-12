#pragma once
#include "filter_male_fi.h"
#include "kandidat.h"
#include "kriterium_k_prislusnost.h"
#include "politicka_strana.h"


class FilterKPrislusnost : public FilterMaleFi<Kandidat*, bool>
{
public:
	FilterKPrislusnost(bool alpha, PolitickaStrana* objekt) :
		FilterMaleFi<Kandidat*, bool>(new KriteriumKPrislusnost(objekt), alpha) {}
};
