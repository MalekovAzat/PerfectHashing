#include "UniversalHash.h"

UniversalHash::UniversalHash(int p, int m, int a, int b)
    : p(p)
    , m(m)
    , a(a)
    , b(b)
{
}

int UniversalHash::operator()(int key) const
{
    return ((unsigned long long int)(a * key + b) % p) % m;    
}
