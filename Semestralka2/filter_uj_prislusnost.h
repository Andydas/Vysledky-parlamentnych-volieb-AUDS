#pragma once
#include "filter_male_fi.h"
#include "uzemna_jednotka.h"
#include "kriterium_uj_prislusnost.h"


class FilterUJPrislusnost : public FilterMaleFi<UzemnaJednotka*, bool>
{
public:
	FilterUJPrislusnost(bool alpha, UzemnaJednotka* objekt) :
		FilterMaleFi<UzemnaJednotka*, bool>(new KriteriumUJPrislusnost(objekt), alpha) {}
};