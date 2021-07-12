#pragma once
#include "kriterium.h"
#include "politicka_strana.h"

template <typename T>
class KriteriumPS : public Kriterium<PolitickaStrana*, T>
{
public:
	virtual T ohodnot(PolitickaStrana* objekt) = 0;
protected:
	KriteriumPS() : Kriterium<PolitickaStrana*, T>() {}
	
};

