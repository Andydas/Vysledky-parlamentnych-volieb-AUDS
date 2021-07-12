#include "uzemna_jednotka.h"


UzemnaJednotka::UzemnaJednotka(int kod, wstring nazov, TypUJ typ, UzemnaJednotka* predok) :
	kod_(kod), nazov_(nazov), typ_(typ), predok_(predok)
{
	volici_ = 0;
	zucastneni_ = 0;
	odovzdaneObalkyOsobne_ = 0;
	odovzdaneObalkyCudzina_ = 0;
	platneHlasy_ = 0;
}

int UzemnaJednotka::getOdovzdaneObalky(TypOdovzdanie sposob)
{
	switch (sposob)
	{
	case TypOdovzdanie::OSOBNE:
		return odovzdaneObalkyOsobne_;
	case TypOdovzdanie::CUDZINA:
		return odovzdaneObalkyCudzina_;
	case TypOdovzdanie::SPOLU:
		return odovzdaneObalkyCudzina_ + odovzdaneObalkyOsobne_;
	}
}

bool UzemnaJednotka::maPredka(UzemnaJednotka* predok)
{
	if (predok == predok_)
	{
		return true;
	}
	else if(predok_ != nullptr)
	{
			return predok_->maPredka(predok);
	}
	else
	{
		return false;
	}
}

void UzemnaJednotka::vypisPredkov()
{
	if (predok_ != nullptr)
	{
		wcout << predok_->getNazov() << endl;
		predok_->vypisPredkov();
	}
	else
	{
		return;
	}
}

void UzemnaJednotka::naplnUdaje(int volici, int zucastneni, int osobne, int cudzina, int platne)
{
	volici_ += volici;
	zucastneni_ += zucastneni;
	odovzdaneObalkyOsobne_ += osobne;
	odovzdaneObalkyCudzina_ += cudzina;
	platneHlasy_ += platne;

	if (predok_ != nullptr)
	{
		predok_->naplnUdaje(volici, zucastneni, osobne, cudzina, platne);
	}
}
