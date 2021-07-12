#pragma once
#include "filter_male_fi.h"
#include "uzemna_jednotka.h"
#include "kriterium_uj_nazov.h"


class FilterUJNazov : public FilterMaleFi<UzemnaJednotka*, std::wstring>
{
public:
	FilterUJNazov(std::wstring alpha) : 
		FilterMaleFi<UzemnaJednotka*, std::wstring>(new KriteriumUJNazov(), alpha) {}
};
 