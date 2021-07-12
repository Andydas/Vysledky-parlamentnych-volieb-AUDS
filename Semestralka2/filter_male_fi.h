#pragma once
#include "filter.h"

template <typename O, typename T>
class FilterMaleFi : public Filter<O, T>
{
public:
	bool splnaFilter(O objekt);
	UnsortedSequenceTable<int, O>* filtruj(Table<int, O>* table);
protected:
	FilterMaleFi(Kriterium<O, T>* kriterium, T alpha);
protected:
	T alpha_;
};

template<typename O, typename T>
inline FilterMaleFi<O, T>::FilterMaleFi(Kriterium<O, T>* kriterium, T alpha) :
	Filter<O, T>(kriterium), alpha_(alpha)
{
}

template<typename O, typename T>
inline bool FilterMaleFi<O, T>::splnaFilter(O objekt)
{
	return Filter<O, T>::kriterium_->ohodnot(objekt) == alpha_;
}

template<typename O, typename T>
inline UnsortedSequenceTable<int, O>* FilterMaleFi<O, T>::filtruj(Table<int, O>* table)
{
	UnsortedSequenceTable<int, O>* output = new UnsortedSequenceTable<int, O>();
		for (auto prvok : *table)
		{
			if (splnaFilter(prvok->accessData()))
			{
				output->insert(prvok->getKey(), prvok->accessData());
			}
		}
		return output;
}


