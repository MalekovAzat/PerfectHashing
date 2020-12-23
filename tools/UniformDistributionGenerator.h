#ifndef UNIFORMDISTRIBUTIONGENERATOR_H
#define UNIFORMDISTRIBUTIONGENERATOR_H

#include <limits>
#include <random>
#include <iostream>

#include "defines.h"

class UniformDistributionGenerator
{
public:
    static UniformDistributionGenerator &getInstance();
    int getA();
    int getB();
    int randValue();

private:
    UniformDistributionGenerator();
    UniformDistributionGenerator(const UniformDistributionGenerator &) = delete;
    UniformDistributionGenerator &operator=(UniformDistributionGenerator &) = delete;

private:
    std::mt19937 m_gen;
    std::uniform_int_distribution<> m_distribA;
    std::uniform_int_distribution<> m_distribB;
};

#endif // !UNIFORMDISTRIBUTIONGENERATOR_H