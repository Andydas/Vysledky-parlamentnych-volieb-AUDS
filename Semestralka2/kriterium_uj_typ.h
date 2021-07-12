#pragma once
#include "kriterium_uj.h"
#include "uzemna_jednotka.h"
#include "typ_UJ.h"

class KriteriumUJTyp : public KriteriumUJ<TypUJ>
{
public:
	KriteriumUJTyp() : KriteriumUJ<TypUJ>() {}
	TypUJ ohodnot(UzemnaJednotka* objekt) override { return objekt->getTyp(); }
};

