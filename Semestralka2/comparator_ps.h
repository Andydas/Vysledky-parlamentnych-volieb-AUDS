#pragma once
#include "comparator.h"
#include "politicka_strana.h"
#include "kriterium_ps.h"

template<typename O, typename T>
class ComparatorPS : public Comparator<O>
{
public:
	ComparatorPS(bool vzostupne, Kriterium<O, T>* kriterium) : Comparator<O>(vzostupne), kriterium_(kriterium) {}
	~ComparatorPS() override { delete kriterium_; }
protected:
	int compare(O a, O b) override;
	Kriterium<O, T>* kriterium_;
};

template<typename O, typename T>
inline int ComparatorPS<O, T>::compare(O a, O b)
{
	if (kriterium_->ohodnot(a) == kriterium_->ohodnot(b))
		return 0;
	else if (kriterium_->ohodnot(a) < kriterium_->ohodnot(b))
		return -1;
	else
		return 1;
}
