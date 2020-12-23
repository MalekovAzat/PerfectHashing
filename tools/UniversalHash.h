#ifndef UNIVERSALHASH_H
#define UNIVERSALHASH_H

#include <iostream>

#include "UniformDistributionGenerator.h"
#include "defines.h"

class UniversalHash
{
public:
    UniversalHash(int m, int p = MAX_KEY_VALUE);
    int operator()(uint key) const;
    void updateParameters();

private:
    int m;
    unsigned long long p;
    unsigned long long a;
    unsigned long long b;
};

#endif // UNIVERSALHASH_H