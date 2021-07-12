#pragma once
#include "comparator.h"
#include "politicka_strana.h"
#include "kriterium_ps.h"

class ComparatorDouble : public Comparator<double>
{
public:
	ComparatorDouble(bool vzostupne) : Comparator<double>(vzostupne){}
protected:
	int compare(double a, double b) override;
};

inline int ComparatorDouble::compare(double a, double b)
{
	if (a == b)
		return 0;
	else if (a < b)
		return -1;
	else
		return 1;
}