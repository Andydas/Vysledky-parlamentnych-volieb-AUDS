#pragma once
#include "kriterium_uj.h"
#include "uzemna_jednotka.h"

class KriteriumUJPrislusnost : public KriteriumUJ<bool>
{
public:
	KriteriumUJPrislusnost(UzemnaJednotka* predok) : KriteriumUJ<bool>(), predok_(predok) {}
	bool ohodnot(UzemnaJednotka* objekt) override { return objekt->maPredka(predok_); }
private:
	UzemnaJednotka* predok_;
};

