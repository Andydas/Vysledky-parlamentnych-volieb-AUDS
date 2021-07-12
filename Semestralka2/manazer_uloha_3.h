#pragma once
#include "../structures/table/table.h"
#include "../structures/table/hash_table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "uzemna_jednotka.h"
#include "citac_param_filter_uj.h"

using namespace structures;

class ManazerUloha3
{
public:
	ManazerUloha3(Table<int, UzemnaJednotka*>* uzemneJednotky);
	~ManazerUloha3() { delete citacParam_; }
	void spusti();
	
	void vystup(Table<int, UzemnaJednotka*>* table);
private:
	Table<int, UzemnaJednotka*>* uzemneJednotky_;
	CitacParamFilterUJ* citacParam_;
};