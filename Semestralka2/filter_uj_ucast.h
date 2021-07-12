#pragma once
#include "uzemna_jednotka.h"
#include "filter_velke_fi.h"
#include "kriterium_uj_ucast.h"

class FilterUJUcast : public FilterVelkeFi<UzemnaJednotka*, double>
{
public:
	FilterUJUcast(double min, double max) : FilterVelkeFi<UzemnaJednotka*, double>(new KriteriumUJUcast(), min, max) {}
};
