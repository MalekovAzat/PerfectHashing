#include "OpenHashTable.h"
#include <cstdlib>
#define p 100000

OpenHashTable::OpenHashTable(int size, int c1, int c2)
    : AbstractHashTable()
    , size(size)
    , c1(c1)
    , c2(c2)
    , hashFunction(size)
{
    storage = new Node*[size];
    for(int i = 0; i < size; i++)
    {
        storage[i] = new Node();
    }
}

int OpenHashTable::insert(unsigned int key, std::string value)
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

    return NodeStates::NOT_INSERTED;    
}   

Node OpenHashTable::search(unsigned int key)
{
    for(int i = 0; i < size; i++)
    {
        int hashValue = calc_hash(key, i);
        
        if (storage[hashValue]->key == NodeStates::NOT_SETTED)
            return Node(NodeStates::NOT_FOUNDED);

        if (storage[hashValue]->key == key)
        {
            return *storage[hashValue];
        }
    }
}

int OpenHashTable::del(std::string value)
{
    for (int i = 0; i < size; i++)
    {
        if (storage[i]->value == value)
        {
            storage[i]->value = "";
            // as deleted key
            storage[i]->key = NodeStates::DELETED;
            //return deletedIndex
            return i;
        }
    }
    return NodeStates::NOT_FOUNDED;
}

int OpenHashTable::calc_hash(int key, int offset) const
{
    return ((hashFunction(key) + c1 * offset + c2 * offset * offset)) % size;
}

Node OpenHashTable::get(int index)
{
    if (index < size)
    {
        return *storage[index];
    }
    // index out of the range
    return Node(NodeStates::NOT_FOUNDED);
}

int OpenHashTable::getHashValue(int key, int offset) const
{
    return calc_hash(key, offset);
}