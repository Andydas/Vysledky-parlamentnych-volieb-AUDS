#pragma once
#include "uzemna_jednotka.h"
#include "filter_velke_fi.h"
#include "kriterium_uj_volici.h"

class FilterUJVolici : public FilterVelkeFi<UzemnaJednotka*, int>
{
public:
	FilterUJVolici(int min, int max) : FilterVelkeFi<UzemnaJednotka*, int>(new KriteriumUJVolici(), min, max) {}
};
