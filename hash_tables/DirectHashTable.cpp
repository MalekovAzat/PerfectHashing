#include "DirectHashTable.h"
#include <cstdlib>

DirectHashTable::DirectHashTable(int size)
    : AbstractHashTable()
    , size(size)
    , c1(rand())
    , c2(rand())
    , hashFunction(p, size, rand() % (p - 1) + 1 , rand() % p)
{
    storage = new Node*[size];
    for(int i = 0; i < size;i++)
    {
        //initial value as NIL
        storage[i] = new Node();
    }

}

int DirectHashTable::insert(int key, std::string value)
{
    for (int i = 0; i < size; i++)
    {
        int hashValue = calc_hash(key, i);
        //  empty or deleted
        if (storage[hashValue]->key == -1 
            || storage[hashValue]->key == -2)
        {
            storage[hashValue]->key = key;
            storage[hashValue]->value = value;

            return hashValue;
        }
    }
        return -1;
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
            storage[i]->key = -2;
        }
    }
}

int DirectHashTable::calc_hash(int key, int offset)
{
    return (hashFunction(key) + c1 * offset + c2 * offset * offset) % size;
}