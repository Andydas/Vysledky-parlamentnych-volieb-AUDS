#pragma once
#include <string>
#include "uzemna_jednotka.h"
#include "../structures/table/hash_table.h"

using namespace structures;
using namespace std;

class Kandidat
{
public:
	Kandidat(int kod, wstring meno, wstring priezvisko);
	~Kandidat();
	wstring getMeno();
	int getKod() { return kod_; }
	int getPlatneHlasy(UzemnaJednotka* pUzemnaJednotka);
	int getPomocnySucet() { return pomocnySucet_; }
	void setUJ(HashTable<int, UzemnaJednotka*>* table) { uzemneJednotky_ = table; }
	void setPomocnySucet(int sum) { pomocnySucet_ = sum; }
	void naplnUdaje(int kodObce, int platne);

private:
	wstring meno_, priezvisko_;
	int kod_;
	HashTable<int, UzemnaJednotka*>* uzemneJednotky_;
	HashTable<int, int>* platneHlasy_;
	int pomocnySucet_;
};

