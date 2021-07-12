#pragma once
#include "../structures/table/table.h"
#include "../structures/table/hash_table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "uzemna_jednotka.h"
#include "citac_param_filter_uj.h"

using namespace structures;

class ManazerUloha4
{
public:
	ManazerUloha4(Table<int, UzemnaJednotka*>* uzemneJednotky);
	~ManazerUloha4() { delete citacParam_; }
	void spusti();
private:
	Table<int, UzemnaJednotka*>* uzemneJednotky_;
	CitacParamFilterUJ* citacParam_;
};