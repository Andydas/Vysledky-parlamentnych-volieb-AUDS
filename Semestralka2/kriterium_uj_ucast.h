#pragma once
#include "kriterium_uj.h"
class KriteriumUJUcast : public KriteriumUJ<double>
{
public:
	KriteriumUJUcast() : KriteriumUJ<double>() {}
	double ohodnot(UzemnaJednotka* objekt) override { return objekt->getZucastneni() / static_cast<double>(objekt->getVolici()) * 100; }
};

 