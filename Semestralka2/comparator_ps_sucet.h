#pragma once
#include "politicka_strana.h"
#include "comparator_ps.h"
#include "kriteirum_ps_sucet.h"

class ComparatorPSSucet : public ComparatorPS<PolitickaStrana*, int>
{
public:
	ComparatorPSSucet(int vzostupne) :
		ComparatorPS<PolitickaStrana*, int>(vzostupne, new KriteriumPSSucet()) {}

};