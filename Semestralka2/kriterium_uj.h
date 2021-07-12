#pragma once
#include "kriterium.h"
#include "uzemna_jednotka.h"

template <typename T>
class KriteriumUJ : public Kriterium<UzemnaJednotka*, T>
{
public:
	virtual T ohodnot(UzemnaJednotka* objekt) = 0;
protected:
	KriteriumUJ() : Kriterium<UzemnaJednotka*, T>() {}
};
