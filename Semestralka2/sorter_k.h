#pragma once
#include "../structures/table/sorting/quick_sort.h"
#include "politicka_strana.h"

using namespace structures;

class SorterK : public QuickSort<int, Kandidat*>
{
public:
	SorterK(Comparator<Kandidat*>* cmp) : QuickSort<int, Kandidat*>(cmp), cmp_(cmp) {}
	//~SorterPS() { cmp_ = nullptr; }
private:
	Comparator<Kandidat*>* cmp_;

};