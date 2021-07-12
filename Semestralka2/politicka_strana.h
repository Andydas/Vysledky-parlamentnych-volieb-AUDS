#pragma once
#include <string>
#include "kandidat.h"
#include "uzemna_jednotka.h"
#include "../structures/table/hash_table.h"

using namespace structures;

class PolitickaStrana
{

public:
	PolitickaStrana(int kod, std::wstring nazov, std::wstring skratenyNazov);  
	~PolitickaStrana();
	int getKod() { return kod_; }
	std::wstring getNazov() { return nazov_; }
	int getPlatneHlasy(UzemnaJednotka* pUzemnaJednotka);
	int getPomocnySucet() { return pomocnySucet_; }
	void setUJ(HashTable<int, UzemnaJednotka*>* table) { uzemneJednotky_ = table; }
	void setPomocnySucet(int sum) { pomocnySucet_ = sum; }
	void naplnUdaje(int kodObce, int platne);
private:
	int kod_;
	std::wstring nazov_;
	std::wstring skratenyNazov_;
	HashTable<int, UzemnaJednotka*>* uzemneJednotky_; 
	HashTable<int, int>* platneHlasy_;						
	int pomocnySucet_;
};

