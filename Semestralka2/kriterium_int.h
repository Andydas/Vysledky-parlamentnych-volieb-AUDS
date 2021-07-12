#pragma once
#include "kriterium.h"

template <typename T>
class KriteriumK : public Kriterium<int, int>
{
public:
	virtual T ohodnot(Kandidat* objekt) = 0;
protected:
	KriteriumK() : Kriterium<Kandidat*, T>() {}
};

