#pragma once
#include "filter.h"

template <typename O, typename T>
class FilterVelkeFi : public Filter<O, T>
{
public:
	bool splnaFilter(O objekt);
	UnsortedSequenceTable<int, O>* filtruj(Table<int, O>* table);

protected:
	FilterVelkeFi(Kriterium<O, T>* kriterium, T min, T max);

protected:
	T min_, max_;
};


template<typename O, typename T>
inline FilterVelkeFi<O, T>::FilterVelkeFi(Kriterium<O, T>* kriterium, T min, T max) :
	Filter<O, T>(kriterium), min_(min), max_(max)
{
}

template<typename O, typename T>
inline bool FilterVelkeFi<O, T>::splnaFilter(O objekt)
{
	T temp = Filter<O, T>::kriterium_->ohodnot(objekt);
	if (temp >= min_ && temp <= max_)
		return true;
	else 
		return false;

}

template<typename O, typename T>
inline UnsortedSequenceTable<int, O>* FilterVelkeFi<O, T>::filtruj(Table<int, O>* table)
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
