#pragma once
#include "../structures/table/table.h"
#include "../structures/table/hash_table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "politicka_strana.h"
#include "citac_param_filter_uj.h"
#include "citac_param_filter_ps.h"

using namespace structures;

class ManazerUloha5
{
public:
	ManazerUloha5(Table<int, UzemnaJednotka*>* uzemneJednotky, Table<int, PolitickaStrana*>* politickeStrany);
	~ManazerUloha5();
	void spusti();
private:
	Table<int, PolitickaStrana*>* politickeStrany_;
	Table<int, UzemnaJednotka*>* uzemneJednotky_;
	CitacParamFilterUJ* citacParamUJ_;
	CitacParamFilterPS* citacParamPS_;
};