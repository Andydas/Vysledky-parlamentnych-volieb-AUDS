#pragma once
#include "sorter_k.h"
#include "comparator_k_sucet.h"

class SorterKSucet : public SorterK
{
public:
	SorterKSucet(int vzostupne) : SorterK(new ComparatorKSucet(vzostupne)) {}

};