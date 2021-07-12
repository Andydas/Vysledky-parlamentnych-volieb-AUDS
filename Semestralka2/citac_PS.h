#pragma once
#include "citac.h"
#include "../structures/table/hash_table.h"
#include "politicka_strana.h"

using namespace structures;

class CitacPS : public Citac<PolitickaStrana*>
{
public:
	HashTable<int, PolitickaStrana*>* citaj(std::string nazov) override;
	void napln(HashTable<int, PolitickaStrana*>* table, std::string nazov) override;
private:
};

