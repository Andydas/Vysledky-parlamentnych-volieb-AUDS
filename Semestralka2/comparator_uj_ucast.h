#pragma once
#include "uzemna_jednotka.h"
#include "comparator_uj.h"

class ComparatorUJUcast : public ComparatorUJ<UzemnaJednotka*, double>
{
public:
	ComparatorUJUcast(bool vzostupne) :
		ComparatorUJ<UzemnaJednotka*, double>(vzostupne, new KriteriumUJUcast()) {}

};