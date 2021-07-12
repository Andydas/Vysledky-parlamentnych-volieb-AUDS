#pragma once
#include "sorter_ps.h"
#include "comparator_ps_sucet.h"

class SorterPSSucet : public SorterPS
{
public:
	SorterPSSucet(bool vzostupne) : SorterPS(new ComparatorPSSucet(vzostupne)) {}

};