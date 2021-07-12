#pragma once
#include "kriterium.h"
#include "kandidat.h"

template <typename T>
class KriteriumK : public Kriterium<Kandidat*, T>
{
public:
	virtual T ohodnot(Kandidat* objekt) = 0;
protected:
	KriteriumK() : Kriterium<Kandidat*, T>() {}
};

