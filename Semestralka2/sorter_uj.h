#pragma once
#include "../structures/table/sorting/quick_sort.h"
#include "uzemna_jednotka.h"

using namespace structures;

class SorterUJ : public QuickSort<int, UzemnaJednotka*>
{
public:
	SorterUJ(Comparator<UzemnaJednotka*>* cmp) : QuickSort<int, UzemnaJednotka*>(cmp), cmp_(cmp) {}
	//virtual ~SorterUJ() { delete cmp_; cmp_ = nullptr; }
private:
	Comparator<UzemnaJednotka*>* cmp_;

}; 