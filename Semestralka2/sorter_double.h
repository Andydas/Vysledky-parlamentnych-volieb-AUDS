#pragma once
#include "../structures/table/sorting/quick_sort.h"
#include "comparator_double.h"

using namespace structures;

class SorterDouble : public QuickSort<int, double>
{
public:
	SorterDouble(bool vzostupne) : QuickSort<int, double>(new ComparatorDouble(vzostupne)){}
private:

};