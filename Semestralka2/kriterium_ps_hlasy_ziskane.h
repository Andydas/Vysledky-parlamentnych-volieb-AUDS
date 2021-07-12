#pragma once
#include "kriterium_ps.h"
#include "politicka_strana.h"
#include "uzemna_jednotka.h"

class KriteriumPSHlasyZiskane : public KriteriumPS<int>
{
public:
    KriteriumPSHlasyZiskane(UzemnaJednotka* uzemnaJednotka) : KriteriumPS<int>(), uzemnaJednotka_(uzemnaJednotka) {}
    int ohodnot(PolitickaStrana* objekt) override { return objekt->getPlatneHlasy(uzemnaJednotka_); }
private:
    UzemnaJednotka* uzemnaJednotka_;
};