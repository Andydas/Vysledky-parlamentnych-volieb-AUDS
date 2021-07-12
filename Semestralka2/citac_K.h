#pragma once
#include "citac.h"
#include "kandidat.h"


class CitacK : public Citac<Kandidat*>
{
public:
	HashTable<int, Kandidat*>* citaj(std::string nazov) override;
	void napln(HashTable<int, Kandidat*>* table, std::string nazov) override;
private:
};

