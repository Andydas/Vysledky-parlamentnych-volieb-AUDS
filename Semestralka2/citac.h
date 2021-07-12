#pragma once
#include <string>
#include "../structures/table/hash_table.h"
using namespace structures;

template<typename T>
class Citac
{
protected:
	virtual HashTable<int, T>* citaj(std::string nazov) = 0;
	virtual void napln(HashTable<int, T>* table, std::string nazov) = 0;
};