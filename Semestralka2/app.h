#pragma once
#include "../structures/table/hash_table.h"
#include "uzemna_jednotka.h"
#include "politicka_strana.h"
using namespace structures;

class App
{

public:
	App();
	~App();
	void testik();

private:
	void hlavneMenu();
	void nacitajTabulky();
	void spustiUlohu(int uloha);
	void clear();
	void nacitajUJ();
	void nacitajPS();
	void nacitajK();

private:
	HashTable<int, UzemnaJednotka*>* uzemneJednotky_;
	HashTable<int, PolitickaStrana*>* politickeStrany_;
	HashTable<int, Kandidat*>* kandidati_;
};

