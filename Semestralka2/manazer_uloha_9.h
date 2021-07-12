#pragma once
#include "../structures/table/table.h"
#include "../structures/table/hash_table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "kandidat.h"
#include "citac_param_filter_uj.h"
#include "citac_param_filter_ps.h"
#include "citac_param_filter_k.h"


using namespace structures;

class ManazerUloha9
{
public:
	ManazerUloha9(Table<int, UzemnaJednotka*>* uzemneJednotky, Table<int, PolitickaStrana*>* politickeStrany, Table<int, Kandidat*>* kandidati);
	~ManazerUloha9();
	void spusti();
private:
	Table<int, PolitickaStrana*>* politickeStrany_;
	Table<int, UzemnaJednotka*>* uzemneJednotky_;
	Table<int, Kandidat*>* kandidati_;
	CitacParamFilterUJ* citacParamUJ_;
	CitacParamFilterK* citacParamK_;
};