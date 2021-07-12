#pragma once
#pragma once
#include "kriterium_ps.h"
#include "politicka_strana.h"

class KriteriumPSSucet : public KriteriumPS<int>
{
public:
    KriteriumPSSucet() : KriteriumPS<int>() {}
    int ohodnot(PolitickaStrana* objekt) override { return objekt->getPomocnySucet(); }
private:
};