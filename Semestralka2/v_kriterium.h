#pragma once
#include "../structures/table/unsorted_sequence_table.h"
#include "../structures/table/table.h"
#include "kriterium.h"

using namespace structures;

template <typename O, typename T>
class VKriterium
{
public:
	virtual O vyber(Table<int, O>* table) = 0;

protected:
	VKriterium(Kriterium<O, T>* kriterium) : kriterium_(kriterium) {}
	~VKriterium() { delete kriterium_; kriterium_ = nullptr; }

protected:
	Kriterium<O, T>* kriterium_;
};

