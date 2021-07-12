#pragma once
#include "politicka_strana.h"
#include "comparator_ps.h"
#include "kriterium_k_sucet.h"

class ComparatorKSucet : public ComparatorPS<Kandidat*, int>
{
public:
	ComparatorKSucet(int vzostupne) :
		ComparatorPS<Kandidat*, int>(vzostupne, new KriteriumKSucet()) {}

};