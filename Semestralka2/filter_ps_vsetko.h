#pragma once
#include "filter_velke_fi.h"
#include "politicka_strana.h"
#include "kriterium_ps_cislo.h"


class FilterPSVsetko : public FilterVelkeFi<PolitickaStrana*, int>
{
public:
	FilterPSVsetko() :
		FilterVelkeFi<PolitickaStrana*, int>(new KriteriumPSCislo(), 0,100) {}
};