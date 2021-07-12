#pragma once
#include "kriterium_uj.h"
#include "uzemna_jednotka.h"

class KriteriumUJVolici : public KriteriumUJ<int>
{
public:
	KriteriumUJVolici() : KriteriumUJ<int>() {}
	int ohodnot(UzemnaJednotka* objekt) override { return objekt->getVolici(); }
};
