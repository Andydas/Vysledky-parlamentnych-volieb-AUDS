#pragma once
#include "filter_k_nazov.h"
#include <iostream>
#include "kandidat.h"
#include "filter_k_prislusnost.h"

class CitacParamFilterK
{
public:
	CitacParamFilterK(Table<int, Kandidat*>* kandidati, Table<int, PolitickaStrana*>* politickeStrany) : 
		kandidati_(kandidati), politickeStrany_(politickeStrany) {}
	FilterKNazov* nacitajFilterNazov();
	FilterKPrislusnost* nacitajFilterPrislusnost();
private:
	Table<int, Kandidat*>* kandidati_;
	Table<int, PolitickaStrana*>* politickeStrany_;
};