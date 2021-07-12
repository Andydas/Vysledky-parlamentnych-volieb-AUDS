#pragma once
#include "kriterium_k.h"
#include "politicka_strana.h"
#include <string>

class KriteriumKPrislusnost: public KriteriumK<bool>
{
public:
	KriteriumKPrislusnost(PolitickaStrana* politickaStrana) : KriteriumK<bool>(), politickaStrana_(politickaStrana) {}
	bool ohodnot(Kandidat* objekt) override { return objekt->getKod() / 1000 == politickaStrana_->getKod(); }
private:
	PolitickaStrana* politickaStrana_;
};