#include "UniformDistributionGenerator.h"

UniformDistributionGenerator& UniformDistributionGenerator::getInstance()
{
    static UniformDistributionGenerator instance;
    return instance;
}

UniformDistributionGenerator::UniformDistributionGenerator()
    : m_gen(std::random_device()())
    , m_distribA(1, MAX_KEY_VALUE - 1) // range [1, MAX_KEY_VALUE - 1]
    , m_distribB(0, MAX_KEY_VALUE - 1) //range [0, MAX_KEY_VALUE - 1]
{
}

int UniformDistributionGenerator::getA()
{
    return m_distribA(m_gen);
}

int UniformDistributionGenerator::getB()
{
    return m_distribB(m_gen);
}

int UniformDistributionGenerator::randValue()
{
    return m_distribB(m_gen);
}