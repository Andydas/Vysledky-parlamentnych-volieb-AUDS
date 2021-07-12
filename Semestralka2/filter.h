#pragma once
#include "kriterium.h"
#include "../structures/table/unsorted_sequence_table.h"
#include "../structures/table/hash_table.h"

using namespace structures;

template <typename O, typename T>
class Filter
{
public:
	virtual bool splnaFilter(O objekt) = 0;
	virtual UnsortedSequenceTable<int, O>* filtruj(Table<int, O>* table) = 0;

protected:
	Filter(Kriterium<O, T>* kriterium) : kriterium_(kriterium) {}
	~Filter() { delete kriterium_; kriterium_ = nullptr; }

protected:
	Kriterium<O, T>* kriterium_;
};

