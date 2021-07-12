#pragma once
#include "kriterium_ps.h"
#include "politicka_strana.h"
#include "uzemna_jednotka.h"

class KriteriumPSUspesnost : public KriteriumPS <double>
{
public:
    KriteriumPSUspesnost(UzemnaJednotka* uzemnaJednotka) : KriteriumPS<double>(), uzemnaJednotka_(uzemnaJednotka) {}
    double ohodnot(PolitickaStrana* objekt) override { return objekt->getPlatneHlasy(uzemnaJednotka_) / static_cast<double>(uzemnaJednotka_->getPlatneHlasy()) * 100; }
private:
    UzemnaJednotka* uzemnaJednotka_;
};
