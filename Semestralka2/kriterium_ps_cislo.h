#pragma once
#include "kriterium_ps.h"
#include "politicka_strana.h"
#include "uzemna_jednotka.h"

class KriteriumPSCislo : public KriteriumPS<int>
{
public:
    KriteriumPSCislo() : KriteriumPS<int>() {}
    int ohodnot(PolitickaStrana* objekt) override { return objekt->getKod(); }
private:
};