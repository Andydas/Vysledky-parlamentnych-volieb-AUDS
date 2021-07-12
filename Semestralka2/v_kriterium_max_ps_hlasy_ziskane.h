#pragma once
#include "v_kriterium_max.h"
#include "politicka_strana.h"
#include "uzemna_jednotka.h"
#include "kriterium_ps_hlasy_ziskane.h"

class VKriteriumMaxPSHlasov : public VKriteriumMax<PolitickaStrana*, int>
{
public:
	VKriteriumMaxPSHlasov(UzemnaJednotka* objekt) : VKriteriumMax<PolitickaStrana*, int>(new KriteriumPSHlasyZiskane(objekt)){}
};