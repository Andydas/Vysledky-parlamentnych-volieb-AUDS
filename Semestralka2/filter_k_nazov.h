#pragma once
#include "filter_male_fi.h"
#include "kandidat.h"
#include "kriterium_k_nazov.h"


class FilterKNazov : public FilterMaleFi<Kandidat*, std::wstring>
{
public:
	FilterKNazov(std::wstring alpha) :
		FilterMaleFi<Kandidat*, std::wstring>(new KriteriumKNazov(), alpha) {}
};
