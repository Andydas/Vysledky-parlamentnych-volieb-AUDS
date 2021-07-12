#pragma once
#include "filter_male_fi.h"
#include "uzemna_jednotka.h"
#include "kriterium_uj_typ.h"
#include "typ_UJ.h"

class FilterUJTyp : public FilterMaleFi<UzemnaJednotka*, TypUJ>
{
public:
	FilterUJTyp(TypUJ alpha) : FilterMaleFi<UzemnaJednotka*, TypUJ>(new KriteriumUJTyp(), alpha) {}
};