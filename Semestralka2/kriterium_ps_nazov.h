#pragma once
#include "kriterium_ps.h"
#include "politicka_strana.h"

class KriteriumPSNazov : public KriteriumPS<std::wstring>
{
public:
	KriteriumPSNazov() : KriteriumPS<std::wstring>() {}
	std::wstring ohodnot(PolitickaStrana* objekt) override { return objekt->getNazov(); }
};
