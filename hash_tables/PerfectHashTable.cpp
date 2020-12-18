#include "PerfectHashTable.h"

#include "../tools/UniformDistributionGenerator.h"
<<<<<<< HEAD
=======

//  (rand() % (maxKeyValue - 1) + 1), rand() % maxKeyValue) - вставь как 3 и 4 параметр в UniversalHash
>>>>>>> 9e0db3a28f74b9fa3cdb3d1d4f470bb6c5c511fb

PerfectHashTable::PerfectHashTable(int size, int maxKeyValue)
    : maxKeyValue(maxKeyValue), size(size), hashFunctionLvl1(size)
{
<<<<<<< HEAD
=======
    // надо придумать ленивую инициализацию
    // знаем сколько ключе будем вставлять -> нужно создать таблицу такого размера
    // далее считаем кол-во коллизий, и если оно больше чем квадрат от кол-ва то пересобираем таблицу
>>>>>>> 9e0db3a28f74b9fa3cdb3d1d4f470bb6c5c511fb
    lvl2HashTables = new SquareSizeTable *[size];
}

int PerfectHashTable::insert(int key, std::string value)
{
    int lvl1Hash = hashFunctionLvl1(key);
    if (lvl2HashTables[lvl1Hash] != nullptr)
    {
        return lvl2HashTables[lvl1Hash]->insert(key, value);
    }

    return NodeStates::NOT_INSERTED;
}

Node PerfectHashTable::search(int key)
{
    uint lvl1Hash = hashFunctionLvl1(key);

    if (lvl2HashTables[lvl1Hash] != nullptr)
    {
        return lvl2HashTables[lvl1Hash]->search(key);
    }
    return Node(NodeStates::NOT_FOUNDED);
}

int del(std::string value)
{
    // int lvl1Hash = hashFunctionLvl1()
    // кроме как перебора по всем зачениям идей пока нет
    return NodeStates::NOT_FOUNDED;
}

int PerfectHashTable::preprocessing(int size, Node **nodes, int compression)
{
    int *countInSubTables = new int[size];

    int squadSum = 0;
    bool rightSize = false;

    while (!rightSize)
    {
        squadSum = 0;
        hashFunctionLvl1 = UniversalHash(size);

        for (int i = 0; i < size; i++)
        {
            countInSubTables[i] = 0;
        }

        // считаем размеры для вторичных таблицы
        for (int i = 0; i < size; i++)
        {
            int hashValue = hashFunctionLvl1(nodes[i]->key);
            countInSubTables[hashValue]++;
        }

        for (int i = 0; i < size; i++)
        {
            squadSum += countInSubTables[i] * countInSubTables[i];
        }
        rightSize = (squadSum < compression * size);
    }

    for (int i = 0; i < size; i++)
    {
        int subtableSize = countInSubTables[i] * countInSubTables[i];
        // std::cout<< "For !@#" << i <<" size is: "<< subtableSize<<std::endl;
        lvl2HashTables[i] = new SquareSizeTable(subtableSize);
    }

    for (int i = 0; i < size; i++)
    {
        int lvl1Key = hashFunctionLvl1(nodes[i]->key);
        lvl2HashTables[lvl1Key]->insert(nodes[i]->key, nodes[i]->value);
    }
    return squadSum;
}

int PerfectHashTable::preprocessing(std::vector<unsigned int> keys, int compression)
{
    int *countInSubTables = new int[size];

    int squadSum = 0;
    bool rightSize = false;

    while (!rightSize)
    {
        squadSum = 0;
        hashFunctionLvl1 = UniversalHash(size);

        for (int i = 0; i < size; i++)
        {
            countInSubTables[i] = 0;
        }

        for(uint key : keys)
        {   
            int hashValue = hashFunctionLvl1(key);
            countInSubTables[hashValue]++;
        }

        for (int i = 0; i < size; i++)
        {
            squadSum += countInSubTables[i] * countInSubTables[i];
        }
    
        rightSize = (squadSum < compression * size);
    }

    for (int i = 0; i < size; i++)
    {
        int subtableSize = countInSubTables[i] * countInSubTables[i];
        lvl2HashTables[i] = new SquareSizeTable(subtableSize);
    }

    for(uint key: keys)
    {
        int lvl1Key = hashFunctionLvl1(key);
        lvl2HashTables[lvl1Key]->insert(key, "EmptyString");
    }
    return squadSum;
}