#pragma once
#include "kriterium_uj.h"
#include "uzemna_jednotka.h"

class KriteriumUJPocetPlatnychHlasov : public KriteriumUJ<int>
{
public:
	KriteriumUJPocetPlatnychHlasov() : KriteriumUJ<int>() {}
	int ohodnot(UzemnaJednotka* objekt) override { return objekt->getPlatneHlasy(); }
};
