#pragma once
#include "comparator.h"
#include "uzemna_jednotka.h"
#include "kriterium_uj.h"

template<typename O, typename T>
class ComparatorUJ : public Comparator<O>
{
public:
	ComparatorUJ(bool vzostupne, Kriterium<O, T>* kriterium) : Comparator<O>(vzostupne), kriterium_(kriterium) {}
	~ComparatorUJ() override { delete kriterium_; }
protected:
	int compare(O a, O b) override;
	Kriterium<O, T>* kriterium_;
};

template<typename O, typename T>
inline int ComparatorUJ<O, T>::compare(O a, O b)
{
	if (kriterium_->ohodnot(a) == kriterium_->ohodnot(b))
		return 0;
	else if (kriterium_->ohodnot(a) < kriterium_->ohodnot(b))
		return -1;
	else
		return 1;
}
