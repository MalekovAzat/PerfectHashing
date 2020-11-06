#include "PerfectHashTable.h"
#define p 100000

InternalHashTable::InternalHashTable(int size)
    : size(size)
    , hashFunction(p, size, (rand() % (p-1) + 1), rand() % p)
{
    storage = new Node*[size];
    for (int i = 0; i < size; i++)
    {
        storage[i] = new Node();
    }
}

InternalHashTable::insert(int key, std::string)
{
    
}

PerfectHashTable::PerfectHashTable(int size)
{
    
}

int PerfectHashTable::insert(int key, std::string value)
{
    return NodeStates::NOT_INSERTED;
}

Node PerfectHashTable::search(int key)
{
    return Node(NodeStates::NOT_FOUNDED);
}

int del(std::string value)
{
    return NodeStates::NOT_FOUNDED;
}

