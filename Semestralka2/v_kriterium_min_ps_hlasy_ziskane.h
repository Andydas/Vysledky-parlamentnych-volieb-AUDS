#pragma once
#include "v_kriterium_min.h"
#include "politicka_strana.h"
#include "uzemna_jednotka.h"
#include "kriterium_ps_hlasy_ziskane.h"

class VKriteriumMinPSHlasov : public VKriteriumMin<PolitickaStrana*, int>
{
public:
	VKriteriumMinPSHlasov(UzemnaJednotka* objekt) : VKriteriumMin<PolitickaStrana*, int>(new KriteriumPSHlasyZiskane(objekt)) {}
};