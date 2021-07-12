#pragma once
#include "../structures/table/sorting/quick_sort.h"
#include "politicka_strana.h"

using namespace structures;

class SorterPS : public QuickSort<int, PolitickaStrana*>
{
public:
	SorterPS(Comparator<PolitickaStrana*>* cmp) : QuickSort<int, PolitickaStrana*>(cmp), cmp_(cmp) {}
	//~SorterPS() { cmp_ = nullptr; }
private:
	Comparator<PolitickaStrana*>* cmp_;

};