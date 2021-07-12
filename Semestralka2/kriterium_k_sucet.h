#pragma once
#pragma once
#include "kriterium_k.h"
#include "kandidat.h"

class KriteriumKSucet : public KriteriumK<int>
{
public:
    KriteriumKSucet() : KriteriumK<int>() {}
    int ohodnot(Kandidat* objekt) override { return objekt->getPomocnySucet(); }
private:
};