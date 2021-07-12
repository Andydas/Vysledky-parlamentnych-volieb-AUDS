#pragma once
#include "uzemna_jednotka.h"
#include <string>
#include "comparator_uj.h"

class ComparatorUJNazov : public ComparatorUJ<UzemnaJednotka*, std::wstring>
{
public:
	ComparatorUJNazov(bool vzostupne) :
		ComparatorUJ<UzemnaJednotka*, std::wstring>(vzostupne, new KriteriumUJNazov()) {}
};