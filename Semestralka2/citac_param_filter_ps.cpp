#include "citac_param_filter_ps.h"

FilterPSNazov* CitacParamFilterPS::nacitajFilterNazov()
{
	wstring input;
	wcout << L"Zadaj nazov politickej strany." << endl;
	wcin.get();
	getline(wcin, input);

	if (input == L"X" || input == L"x")
	{
		return nullptr;
	}
	return new FilterPSNazov(input);
}