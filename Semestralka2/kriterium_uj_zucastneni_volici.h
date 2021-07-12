#pragma once
#include "kriterium_uj.h"
#include "uzemna_jednotka.h"

class KriteriumUJZucastneniVolici : public KriteriumUJ<int>
{
public:
	KriteriumUJZucastneniVolici() : KriteriumUJ<int>() {}
	int ohodnot(UzemnaJednotka* objekt) override { return objekt->getZucastneni(); }
};