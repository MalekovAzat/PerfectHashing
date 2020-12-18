#include "UniversalHash.h"

UniversalHash::UniversalHash(int m, int p)
    : m(m)
    , p(MAX_KEY_VALUE)
    , a(Generator::getInstance().getA())
    , b(Generator::getInstance().getB())
{
}

int UniversalHash::operator()(uint key) const
{
    return ((a * key + b) % p) % m;
}

void UniversalHash::updateParameters()
{
    a = Generator::getInstance().getA();
    b = Generator::getInstance().getB();
}