#pragma once
#include "kriterium_uj.h"
#include "uzemna_jednotka.h"
#include "typ_odovzdania.h"

class KriteriumUJOdovzdaneObalky : public KriteriumUJ<int>
{
public:
	KriteriumUJOdovzdaneObalky(TypOdovzdanie sposob) : KriteriumUJ<int>(), sposob_(sposob) {}
	int ohodnot(UzemnaJednotka* objekt) override { return objekt->getOdovzdaneObalky(sposob_); }

private:
	TypOdovzdanie sposob_;
};
