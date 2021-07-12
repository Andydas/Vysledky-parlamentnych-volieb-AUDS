#pragma once
#include "citac.h"
#include "uzemna_jednotka.h"

class CitacUJ : public Citac<UzemnaJednotka*>
{
public:
	HashTable<int, UzemnaJednotka*>* citaj(std::string nazov) override;
	void napln(HashTable<int, UzemnaJednotka*>* table, std::string nazov) override;
private:
};

