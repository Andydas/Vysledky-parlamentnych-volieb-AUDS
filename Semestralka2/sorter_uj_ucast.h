#pragma once
#include "sorter_uj.h"
#include "comparator_uj_ucast.h"

class SorterUJUcast : public SorterUJ
{
public:
	SorterUJUcast(bool vzostupne) : SorterUJ(new ComparatorUJUcast(vzostupne)) {}
};