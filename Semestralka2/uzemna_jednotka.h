#pragma once
#include "typ_UJ.h"
#include "typ_odovzdania.h"
#include <string>
#include <iostream>

using namespace std;
class UzemnaJednotka
{

public:
	UzemnaJednotka(int kod, wstring nazov, TypUJ typ, UzemnaJednotka* predok);
	
	int getKod() { return kod_; }
	UzemnaJednotka* getPredok() { return predok_; }
	wstring getNazov() { return nazov_; }
	TypUJ getTyp() { return typ_; }
	int getVolici() { return volici_; }
	int getZucastneni() { return zucastneni_; }
	int getOdovzdaneObalky(TypOdovzdanie sposob); 
	int getPlatneHlasy() { return platneHlasy_; }
	bool maPredka(UzemnaJednotka* predok);
	void vypisPredkov();

	void naplnUdaje(int volici, int zucastneni, int osobne, int cudzina, int platne);
private:

private:
	int kod_;
	wstring nazov_;
	TypUJ typ_;
	UzemnaJednotka* predok_;
	int volici_;
	int zucastneni_;
	int odovzdaneObalkyOsobne_;
	int odovzdaneObalkyCudzina_;
	int platneHlasy_;
};

