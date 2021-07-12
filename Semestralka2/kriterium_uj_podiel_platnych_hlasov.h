#pragma once
#include "kriterium_uj.h"
#include "uzemna_jednotka.h"
#include "typ_odovzdania.h"

class KriteriumUJPodielPlatnychHlasov : public KriteriumUJ<double>
{
public:
	KriteriumUJPodielPlatnychHlasov() : KriteriumUJ<double>() {}
	double ohodnot(UzemnaJednotka* objekt) override { return objekt->getPlatneHlasy() / static_cast<double>(objekt->getOdovzdaneObalky(TypOdovzdanie::SPOLU)) * 100; }
};
