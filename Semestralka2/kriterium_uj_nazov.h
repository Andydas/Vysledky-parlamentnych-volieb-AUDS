#pragma once
#include "kriterium_uj.h"
#include <string>

class KriteriumUJNazov : public KriteriumUJ<std::wstring>
{
public:
	KriteriumUJNazov() : KriteriumUJ<std::wstring>() {}
	std::wstring ohodnot(UzemnaJednotka* objekt) override { return objekt->getNazov(); }
	//int porovnaj(std::wstring other);
private:
};

