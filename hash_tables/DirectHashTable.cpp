#include "DirectHashTable.h"
#include <cstdlib>
#define p 100000

DirectHashTable::DirectHashTable(int size)
    : AbstractHashTable()
    , size(size)
    , c1(rand())
    , c2(rand())
    , hashFunction(p, size, (rand() % (p-1) + 1), rand() % p)
{
    storage = new Node*[size];
    for(int i = 0; i < size; i++)
    {
        storage[i] = new Node();
    }
}

int DirectHashTable::insert(int key, std::string value)
{
    for (int i = 0; i < size; i++)
    {
        int hashValue = calc_hash(key, i);
        if (storage[hashValue]->key == NodeStates::NOT_SETTED 
            || storage[hashValue]->key == NodeStates::DELETED)
        {
            storage[hashValue]->key = key;
            storage[hashValue]->value = value;

            return hashValue;
        }
    }
    return (int)NodeStates::NOT_INSERTED;
}   

Node DirectHashTable::search(int key)
{
    for(int i = 0; i < size; i++)
    {
        int hashValue = calc_hash(key, i);
        
        if (storage[hashValue]->key == -1)
            break;

        if (storage[hashValue]->key == key)
        {
            return *storage[hashValue];
        }
    }
}

void DirectHashTable::del(std::string value)
{
    for (int i = 0; i < size; i++)
    {
        if (storage[i]->value == value)
        {
            storage[i]->value = "";
            // as deleted key
            storage[i]->key = NodeStates::DELETED;
        }
    }
}

int DirectHashTable::calc_hash(int key, int offset) const
{
    return ((unsigned long long int)(hashFunction(key) + c1 * offset + c2 * offset * offset)) % size;
}

Node DirectHashTable::get(int index)
{
    if (index < size)
    {
        return *storage[index];
    }
    // index out of the range
    return Node(NodeStates::NOT_FOUNDED);
}

int DirectHashTable::getHashValue(int key, int offset) const
{
    return calc_hash(key, offset);
}