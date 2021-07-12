#pragma once
#include "filter_uj_nazov.h"
#include "filter_uj_prislusnost.h"
#include "filter_uj_typ.h"
#include "filter_uj_volici.h"
#include "filter_uj_ucast.h"
#include <iostream>

class CitacParamFilterUJ
{
public:
	CitacParamFilterUJ(Table<int, UzemnaJednotka*>* uzemneJednotky) : uzemneJednotky_(uzemneJednotky) {}
	FilterUJNazov* nacitajFilterNazov();
	FilterUJPrislusnost* nacitajFilterPrislusnost();
	FilterUJTyp* nacitajFilterTyp();
	FilterUJVolici* nacitajFilterVolici();
	FilterUJUcast* nacitajFilterUcast();
private:
	Table<int, UzemnaJednotka*>* uzemneJednotky_;
};