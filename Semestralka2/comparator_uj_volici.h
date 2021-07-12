#pragma once
#include "uzemna_jednotka.h"
#include "comparator_uj.h"

class ComparatorUJVolici : public ComparatorUJ<UzemnaJednotka*, int>
{
public:
	ComparatorUJVolici(bool vzostupne) : 
		ComparatorUJ<UzemnaJednotka*, int>(vzostupne, new KriteriumUJVolici()) {}

};
