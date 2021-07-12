#pragma once
#include "sorter_uj.h"
#include "comparator_uj_nazov.h"

class SorterUJNazov : public SorterUJ
{
public:
	SorterUJNazov(bool vzostupne) : SorterUJ(new ComparatorUJNazov(vzostupne)) {}

};