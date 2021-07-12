#pragma once
#include "filter_male_fi.h"
#include "politicka_strana.h"
#include "kriterium_ps_nazov.h"


class FilterPSNazov : public FilterMaleFi<PolitickaStrana*, std::wstring>
{
public:
	FilterPSNazov(std::wstring alpha) :
		FilterMaleFi<PolitickaStrana*, std::wstring>(new KriteriumPSNazov(), alpha) {}
};