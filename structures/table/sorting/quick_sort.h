#pragma once

#include "sort.h"
#include "../unsorted_sequence_table.h"
#include "../../../Semestralka2/comparator.h"
#include <iostream>
#include <string>

namespace structures
{

	/// <summary> Triedenie Quick sort. </summary>
	/// <typeparam name = "K"> Kluc prvkov v tabulke. </typepram>
	/// <typeparam name = "T"> Typ dat ukladanych v tabulke. </typepram>
	template <typename K, typename T>
	class QuickSort : public Sort<K, T>
	{
	public:
		QuickSort(Comparator<T>* cmp) : cmp_(cmp) {}
		virtual ~QuickSort() { delete cmp_; cmp_ = nullptr; }
		/// <summary> Utriedi tabulku triedenim Quick sort. </summary>
		/// <param name = "table"> NonortedSequenceTable, ktoru ma utriedit. </param>
		void sort(UnsortedSequenceTable<K, T>* table) override;
	private:
		void quick(UnsortedSequenceTable<K, T>* table, int min, int max, Comparator<T>* cmp);
		void sort(UnsortedSequenceTable<K, T>* table, Comparator<T>* cmp);
		Comparator<T>* cmp_;
	};

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>* table)
	{
		this->sort(table, cmp_);
	}

	template<typename K, typename T>
	inline void QuickSort<K, T>::sort(UnsortedSequenceTable<K, T>* table, Comparator<T>* cmp)
	{
		//TODO 12: QuickSort
		
		quick(table, 0, table->size() - 1, cmp);

		//throw std::exception("QuickSort<K, T>::sort: Not implemented yet.");
	}
	template<typename K, typename T>
	inline void QuickSort<K, T>::quick(UnsortedSequenceTable<K, T>* table, int min, int max, Comparator<T>* cmp)
	{
		T pivot = table->getItemAtIndex(min + (max - min) / 2).accessData();
		int leftIndex = min;
		int rightIndex = max;

		while (leftIndex <= rightIndex)
		{
			while ((*cmp)(table->getItemAtIndex(leftIndex).accessData(), pivot) < 0)
				leftIndex++;
			
			while ((*cmp)(table->getItemAtIndex(rightIndex).accessData(), pivot) > 0)
				rightIndex--;
			
			if (leftIndex <= rightIndex)
			{
				table->swap(leftIndex, rightIndex);
				leftIndex++;
				rightIndex--;
			}
		}

		if (min < rightIndex)
			quick(table, min, rightIndex, cmp);

		if (leftIndex < max)
			quick(table, leftIndex, max, cmp);
	}
}