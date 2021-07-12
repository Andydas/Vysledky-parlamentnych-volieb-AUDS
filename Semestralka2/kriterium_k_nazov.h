#pragma once
#include "kriterium_k.h"
#include "kandidat.h"

class KriteriumKNazov : public KriteriumK<std::wstring>
{
public:
	KriteriumKNazov() : KriteriumK<std::wstring>() {}
	std::wstring ohodnot(Kandidat* objekt) override { return objekt->getMeno(); }
};