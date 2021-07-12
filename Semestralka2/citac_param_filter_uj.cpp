#include "citac_param_filter_uj.h"


FilterUJNazov* CitacParamFilterUJ::nacitajFilterNazov()
{
	wstring input;
	wcout << L"Zadaj nazov uzemnej jednotky." << endl;
	wcin.get();
	getline(wcin, input);

	if (input == L"X" || input == L"x")
	{
		return nullptr;
	}
	return new FilterUJNazov(input);
}

FilterUJPrislusnost* CitacParamFilterUJ::nacitajFilterPrislusnost()
{
	bool temp;
	wstring inputBool;
	wstring input;

	wcout << L"Zadaj parameter prislusnosti, ma patrit? 1-ANO, 0-NIE" << endl;
	wcin >> inputBool;

	if (inputBool == L"X" || inputBool == L"x")
	{
		return nullptr;
	}

	wcout << L"Zadaj nazov uzemnej jednotky do ktorej ma patrit." << endl;
	wcin >> input;

	return new FilterUJPrislusnost(inputBool == L"1", (*uzemneJednotky_)[stoi(input)]);
}

FilterUJTyp* CitacParamFilterUJ::nacitajFilterTyp()
{
	wstring input;
	wcout << L"Zadaj typ uzemnej jednotky. 0 - STAT, 1 - KRAJ, 2 - OKRES, 3 - OBEC" << endl;
	wcin >> input;

	if (input == L"X" || input == L"x")
	{
		return nullptr;
	}
	return new FilterUJTyp(static_cast<TypUJ>(stoi(input)));
}

FilterUJVolici* CitacParamFilterUJ::nacitajFilterVolici()
{
	wstring inputMin;
	wstring inputMax;

	wcout << L"Zadaj dolnu hranicu pre pocet volicov." << endl;
	wcin >> inputMin;

	if (inputMin == L"X" || inputMin == L"x")
	{
		return nullptr;
	}

	wcout << L"Zadaj hornu hranicu pre pocet volicov." << endl;
	wcin >> inputMax;


	return new FilterUJVolici(stoi(inputMin), stoi(inputMax));
}

FilterUJUcast* CitacParamFilterUJ::nacitajFilterUcast()
{
	wstring inputMin;
	wstring inputMax;

	wcout << L"Zadaj dolnu hranicu pre ucast." << endl;
	wcin >> inputMin;

	if (inputMin == L"X" || inputMin == L"x")
	{
		return nullptr;
	}

	wcout << L"Zadaj dolnu hranicu pre ucast." << endl;
	wcin >> inputMax;


	return new FilterUJUcast(stod(inputMin), stod(inputMax));
}

