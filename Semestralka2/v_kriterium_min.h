#pragma once
#include "v_kriterium.h"
#include "politicka_strana.h"
#include "uzemna_jednotka.h"
#include "kriterium_ps_hlasy_ziskane.h"

template<typename O, typename T>
class VKriteriumMin : public VKriterium<O, T>
{
public:
	O vyber(Table<int, O>* table) override;

protected:
	VKriteriumMin(Kriterium<O, T>* kriterium);
};

template<typename O, typename T>
inline VKriteriumMin<O, T>::VKriteriumMin(Kriterium<O, T>* kriterium):
	VKriterium<O, T>(kriterium)
{
}

template<typename O, typename T>
inline O VKriteriumMin<O, T>::vyber(Table<int, O>* table)
{
	O min = nullptr;
	for (auto prvok : *table)
	{
		if (min == nullptr)
			min = prvok->accessData();

		if (VKriterium<O, T>::kriterium_->ohodnot(min) > VKriterium<O, T>::kriterium_->ohodnot(prvok->accessData()))
		{
			min = prvok->accessData();
		}
	}
	return min;
}

