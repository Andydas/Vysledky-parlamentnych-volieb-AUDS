#pragma once
#include "sorter_uj.h"
#include "comparator_uj_volici.h"

class SorterUJVolici : public SorterUJ
{
public:
	SorterUJVolici(bool vzostupne) : SorterUJ(new ComparatorUJVolici(vzostupne)) {}
};