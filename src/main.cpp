#include <iostream>
#include <list>
#include <vector>
#include <set>
#include <random>
#include <fstream>
#include <chrono>

#include "../tools/UniversalHash.h"
#include "../tools/UniformDistributionGenerator.h"
#include "../tools/defines.h"
#include "../hash_tables/OpenHashTable.h"
#include "../hash_tables/PerfectHashTable.h"
#include "../hash_tables/SquareSizeTable.h"

void experiment1();
void experiment2();
void experiment3();
unsigned int converter(std::string str);
std::set<unsigned int> getData();
std::set<uint> getRandomData(int size);

int main()
{
    UniformDistributionGenerator::getInstance();

    experiment1();
    experiment2();
    experiment3();
}

void experiment1()
{
    std::cout << "exp1 " << std::endl;
    std::set<uint> data = getRandomData(10000000);
    std::vector<uint> keys(data.begin(), data.end());
    std::cout << keys.size() << std::endl;

    std::vector<double> compressionList = {2.0, 2.5, 3.0, 3.5, 4.0, 4.5, 5.0};

    PerfectHashTable *newHashTable = new PerfectHashTable(keys.size());

    std::ofstream fileExp1;
    fileExp1.open("exp1.txt");

    for (double compression : compressionList)
    {
        auto begin = std::chrono::steady_clock::now();
        std::cout << "Compression: " << compression << std::endl;
        int sizeOfTable = newHashTable->preprocessing(keys, compression);
        std::cout << "Done for compression: " << compression << std::endl;
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

        std::string result = std::to_string(compression) + "," + std::to_string(elapsed_ms.count()) + "," + std::to_string(sizeOfTable) + "\n";
        fileExp1 << result;
    }

    fileExp1.close();
    delete newHashTable;
}

void experiment2()
{
    std::cout << "exp2 " << std::endl;

    std::vector<int> expSizes = {1, 10, 100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000,10000};

    PerfectHashTable *perfectTable;
    SquareSizeTable *squareTable;

    std::ofstream fileExp2;
    fileExp2.open("exp2.txt");

    for (int expSize : expSizes)
    {
        std::cout << "Size: " << expSize << std::endl;

        std::set<uint> data = getRandomData(expSize);
        std::vector<uint> keys(data.begin(), data.end());

        perfectTable = new PerfectHashTable(expSize);
        squareTable = new SquareSizeTable(expSize * expSize);

        auto begin = std::chrono::steady_clock::now();
        perfectTable->preprocessing(keys, 4);
        auto end = std::chrono::steady_clock::now();
        auto elapsedPerfectMs = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

        begin = std::chrono::steady_clock::now();
        for (uint key : keys)
        {
            squareTable->insert(key, "HELL");
        }
        end = std::chrono::steady_clock::now();
        auto elapseSquaretMs = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

        std::string result = std::to_string(expSize) + "," + std::to_string(elapsedPerfectMs) + "," + std::to_string(elapseSquaretMs) + "\n";
        fileExp2 << result;
        delete perfectTable;
        delete squareTable;
    }

    fileExp2.close();
}

void experiment3()
{
    std::cout << "exp3 " << std::endl;

    std::vector<int> searchingCountVector = {1, 10, 100, 500, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000};

    PerfectHashTable *perfectTable = new PerfectHashTable(10000);
    SquareSizeTable *squareTable = new SquareSizeTable(10000 * 10000);

    std::ofstream fileExp3;
    fileExp3.open("exp3.txt");

    std::set<uint> data = getRandomData(10000);
    std::vector<uint> keys(data.begin(), data.end());

    perfectTable->preprocessing(keys, 4);
    for (uint key : keys)
    {
        squareTable->insert(key, "MORE HELL");
    }

    for (int searchCount : searchingCountVector)
    {
        auto begin = std::chrono::steady_clock::now();
        for (int i = 0; i < searchCount; i++)
        {
            perfectTable->search(keys[i]);
        }
        auto end = std::chrono::steady_clock::now();
        auto elapsePerfectMs = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();

        begin = std::chrono::steady_clock::now();
        for (int i = 0; i < searchCount; i++)
        {
            squareTable->search(keys[i]);
        }
        end = std::chrono::steady_clock::now();
        auto elapseSquareMs = std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count();
        fileExp3 << std::to_string(searchCount) << "," << elapsePerfectMs << "," << elapseSquareMs << "\n";
    }
    fileExp3.close();

    delete perfectTable;
    delete squareTable;
}

unsigned int converter(std::string str)
{
    int size = str.size();
    unsigned long long convertedValue = 0;

    for (int i = size - 1; i >= 0; i--)
    {
        convertedValue += ((int)str[i] - 96) * pow(27, size - i - 1);
    }

    return convertedValue;
}

std::set<unsigned int> getData()
{
    std::set<unsigned int> translatedKey;

    std::ifstream in;
    std::string inputLine;
    setlocale(LC_ALL, "Russian");

    in.open("../data/words_alpha.txt");
    if (in.is_open())
    {
        while (getline(in, inputLine))
        {
            unsigned long long convertedValue = converter(inputLine);
            if (convertedValue < MAX_KEY_VALUE && convertedValue > 0)
            {
                translatedKey.insert(convertedValue);
            }
        }
    }

    return translatedKey;
}

std::set<uint> getRandomData(int size)
{
    std::set<uint> keys;

    while (keys.size() != size)
    {
        std::random_device rd;
        std::uniform_int_distribution<> distrib(0, MAX_KEY_VALUE);

        uint newKey = distrib(rd);
        keys.insert(newKey);
    }
    return keys;
}