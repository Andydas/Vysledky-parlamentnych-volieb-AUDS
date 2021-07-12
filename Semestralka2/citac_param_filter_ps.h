#pragma once
#include "filter_ps_nazov.h"
#include <iostream>
#include "politicka_strana.h"

class CitacParamFilterPS
{
public:
	CitacParamFilterPS(Table<int, PolitickaStrana*>* politickeStrany) : politickeStrany_(politickeStrany) {}
	FilterPSNazov* nacitajFilterNazov();
private:
	Table<int, PolitickaStrana*>* politickeStrany_;
};