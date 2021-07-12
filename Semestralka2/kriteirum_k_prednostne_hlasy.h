#pragma once
#include "kriterium_k.h"
#include "uzemna_jednotka.h"
#include <string>

class KriteriumKPrednostneHlasy : public KriteriumK<int>
{
public:
	KriteriumKPrednostneHlasy(UzemnaJednotka* uzemnaJednotka) : KriteriumK<int>(), uzemnaJednotka_(uzemnaJednotka) {}
	int ohodnot(Kandidat* objekt) override { return objekt->getPlatneHlasy(uzemnaJednotka_); }
private:
	UzemnaJednotka* uzemnaJednotka_;
};