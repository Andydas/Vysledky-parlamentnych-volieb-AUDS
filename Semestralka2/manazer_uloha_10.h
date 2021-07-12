#pragma once
#include "../structures/table/table.h"
#include "../structures/table/hash_table.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "politicka_strana.h"
#include "citac_param_filter_uj.h"
#include "citac_param_filter_ps.h"
#include "citac_param_filter_k.h"

using namespace structures;

class ManazerUloha10
{
public:
	ManazerUloha10(Table<int, UzemnaJednotka*>* uzemneJednotky, Table<int, PolitickaStrana*>* politickeStrany, Table<int, Kandidat*>* kandidati);
	~ManazerUloha10();
	void spusti();
private:
	Table<int, Kandidat*>* kandidati_;
	Table<int, UzemnaJednotka*>* uzemneJednotky_;
	Table<int, PolitickaStrana*>* politickeStrany_;
	CitacParamFilterUJ* citacParamUJ_;
	CitacParamFilterK* citacParamK_;
};