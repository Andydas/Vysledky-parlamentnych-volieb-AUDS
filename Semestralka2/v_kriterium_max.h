#pragma once
#include "v_kriterium.h"
#include "politicka_strana.h"
#include "uzemna_jednotka.h"
#include "kriterium_ps_hlasy_ziskane.h"

template<typename O, typename T>
class VKriteriumMax : public VKriterium<O, T>
{
public:
	O vyber(Table<int, O>* table) override;
protected:
	VKriteriumMax(Kriterium<O, T>* kriterium);

};

template<typename O, typename T>
inline VKriteriumMax<O, T>::VKriteriumMax(Kriterium<O, T>* kriterium):
	VKriterium<O, T>(kriterium)
{
}

template<typename O, typename T>
inline O VKriteriumMax<O, T>::vyber(Table<int, O>* table)
{
	O max = nullptr;
	for (auto prvok : *table)
	{
		if (max == nullptr)
			max = prvok->accessData();

		if (VKriterium<O, T>::kriterium_->ohodnot(max) < VKriterium<O, T>::kriterium_->ohodnot(prvok->accessData()))
		{
			max = prvok->accessData();
		}
	}
	return max;
}

