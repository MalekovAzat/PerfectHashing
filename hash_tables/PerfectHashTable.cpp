#include "PerfectHashTable.h"
#define p 100000

InternalHashTable::InternalHashTable(int size)
    :AbstractHashTable()
    , size(size)
    , hashFunction(new UniversalHash(p, size, (rand() % (p - 1) + 1), rand() % p))
{
    storage = new Node *[size];
    for (int i = 0; i < size; i++)
    {
        storage[i] = new Node();
    }
}

InternalHashTable::InternalHashTable(int size, UniversalHash *hashFunctionLvl2)
    : size(size)
{
    hashFunction = hashFunctionLvl2;
    storage = new Node *[size];
    for (int i = 0; i < size; i++)
    {
        storage[i] = new Node();
    }
}

int InternalHashTable::insert(int key, std::string value)
{
    int hashValue = (*hashFunction)(key);

    if (storage[hashValue]->key == NodeStates::NOT_SETTED)
    {
        storage[hashValue]->key = key;
        storage[hashValue]->value = value;
        return hashValue;
    }

    return NodeStates::NOT_INSERTED;
}

Node InternalHashTable::search(int key)
{
    int hashValue = (*hashFunction)(key);
    return *storage[hashValue];
}

// Линейный перебор, очень очень плохо!
int InternalHashTable::del(std::string value)
{
    for (int i = 0; i < size; i++)
    {
        if (storage[i]->value == value)
        {
            storage[i]->key = NodeStates::DELETED;
            storage[i]->value = "";
            return i;
        }
    }

    return NodeStates::NOT_FOUNDED;
}

InternalHashTable::~InternalHashTable()
{
    for (int i = 0; i < size; i++)
    {
        delete storage[i];
    }
    delete[] storage;
}

PerfectHashTable::PerfectHashTable(int size)
    : size(size)
    , hashFunctionLvl1(p, size, (rand() % (p - 1) + 1), rand() % p)
{
    // надо придумать ленивую инициализацию
    // знаем сколько ключе будем вставлять -> нужно создать таблицу такого размера
    // далее считаем кол-во коллизий, и если оно больше чем квадрат от кол-ва то пересобираем таблицу
    storage = new InternalHashTable *[size];
}

int PerfectHashTable::insert(int key, std::string value)
{
    int lvl1Hash = hashFunctionLvl1(key);
    if (storage[lvl1Hash] != nullptr)
    {
        return storage[lvl1Hash]->insert(key, value);
    }

    return NodeStates::NOT_INSERTED;
}

Node PerfectHashTable::search(int key)
{
    int lvl1Hash = hashFunctionLvl1(key);

    if (storage[lvl1Hash] != nullptr)
    {
        return storage[lvl1Hash]->search(key);
    }
    return Node(NodeStates::NOT_FOUNDED);
}

// надо придумать нормальный способ дл delete, потому что O(n) так себе
int del(std::string value)
{
    // int lvl1Hash = hashFunctionLvl1()
    return NodeStates::NOT_FOUNDED;
}

void PerfectHashTable::preprocessing(int size, Node **nodes)
{
    int *countInSubTables = new int[size];
    int squadSum = 0;
    // TODO: дописать чтобы работало в цикле
    while (true)
    {
        squadSum = 0;
        for (int i = 0; i < size; i++)
        {
            countInSubTables[i] = 0;
        }

        for (int i = 0; i < size; i++)
        {
            int hashValue = hashFunctionLvl1(nodes[i]->key);
            countInSubTables[hashValue]++;
        }

        // высчитаем общее число коллизий
        for (int i = 0; i < size; i++)
        {
            // std::cout << countInSubTables[i] << std::endl;
            squadSum += (countInSubTables[i] * countInSubTables[i]);
        }

        if (squadSum < 4 * size)
        {
            break;
        }

        hashFunctionLvl1 = UniversalHash(p, size, (rand() % (p - 1) + 1), rand() % p);
    }

    std::cout << "The size is " <<  " " << squadSum << " " <<4 * size<< std::endl;
    // подобралась функция, 
    // при которой будет достигаться размер 4*n кол-во элементов
    // выделим память для всех элементов
    
    for (int i = 0; i < size; i++)
    {
        int subtableSize = countInSubTables[i];
        storage[i] = new InternalHashTable(subtableSize);
    }
    // на данном уровне у нас есть очень большая вероятность того что коллизий не будет,
    //  но так писать очень плохо потому что по сути тут время будет 2 * O(n)
    for (int i = 0; i < size; i++)
    {
        int lvl1hashValue = hashFunctionLvl1(nodes[i]->key);
        storage[lvl1hashValue]->insert(nodes[i]->key, nodes[i]->value);
    }
}