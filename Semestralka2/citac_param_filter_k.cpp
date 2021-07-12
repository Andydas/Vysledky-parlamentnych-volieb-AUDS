#include "citac_param_filter_k.h"

FilterKNazov* CitacParamFilterK::nacitajFilterNazov()
{
	wstring input;
	wcout << L"Zadaj meno kandidata." << endl;
	wcin.get();
	getline(wcin, input);

	if (input == L"X" || input == L"x")
	{
		return nullptr;
	}
	return new FilterKNazov(input);
}

FilterKPrislusnost* CitacParamFilterK::nacitajFilterPrislusnost()
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

	wcout << L"Zadaj kod politickej strany za ktoru kandiduje." << endl;
	wcin >> input;

	return new FilterKPrislusnost(inputBool == L"1", (*politickeStrany_)[stoi(input)]);
}
