#include "SquareSizeTable.h"

SquareSizeTable::SquareSizeTable(int size, int maxKeyValue)
    : AbstractHashTable(), size(size), maxKeyValue(maxKeyValue), hashFunction(new UniversalHash(size))
{
    storage = new Node *[size];
    for (int i = 0; i < size; i++)
    {
        storage[i] = new Node();
    }
}

SquareSizeTable::SquareSizeTable(int size, UniversalHash *newHashFunction)
    : size(size)
{
    hashFunction = newHashFunction;
    storage = new Node *[size];
    for (int i = 0; i < size; i++)
    {
        storage[i] = new Node();
    }
}

int SquareSizeTable::insert(uint key, std::string value)
{
    uint hashValue = hashFunction->operator()(key);
    if (storage[hashValue]->key == NodeStates::NOT_SETTED)
    {
        storage[hashValue]->key = key;
        storage[hashValue]->value = value;
        return hashValue;
    }
    else if (storage[hashValue]->key == key)
    {
        return NodeStates::ALREADY_INSERTED;
    }
    else
    {
        return fixCollision(key, value);
    }

    return NodeStates::NOT_INSERTED;
}

Node** SquareSizeTable::saveNodes()
{
    Node **savedNodes = new Node*[size + 1];
    int savedCount = 0;
    for (int i = 0; i < size; i++)
    {   
        if (storage[i]->key != NodeStates::NOT_SETTED)
        {
            savedNodes[i] = new Node(storage[i]->key, storage[i]->value);
        }
        else
        {
            savedNodes[i] = nullptr;
        }
    }
    return savedNodes;
}

void SquareSizeTable::updateHashFunction()
{
    hashFunction->updateParameters();
}

void SquareSizeTable::clearStorage()
{
    for (int i = 0; i < size; i++)
    {
        storage[i]->key = NodeStates::NOT_SETTED;
        storage[i]->value = "";
    }
}

int SquareSizeTable::fixCollision(int key, std::string value)
{
    Node **savedNodes = saveNodes();
    savedNodes[size] = new Node(key, value);
    
    bool hasCollision = true;
    uint hashValue;
    while (hasCollision)
    {
        hasCollision = false;
        clearStorage();
        updateHashFunction();
        for (int i = 0; i < size + 1; i++)
        {
            if (savedNodes[i] == nullptr)
            {
                continue;
            }
        
            hashValue = hashFunction->operator()(savedNodes[i]->key);

            if (storage[hashValue]->key != NOT_SETTED)
            {
                hasCollision = true;
                break;
            }
            else
            {
                storage[hashValue]->key = savedNodes[i]->key;
                storage[hashValue]->value = savedNodes[i]->value;
            }
        }
    }

    for (int i = 0; i < size + 1; i++)
    {
        delete savedNodes[i];
    }
    delete[] savedNodes;

    return hashValue;
}

Node SquareSizeTable::search(unsigned int key)
{
    int hashValue = hashFunction->operator()(key);
    return *storage[hashValue];
}

// Линейный перебор, очень очень плохо!
int SquareSizeTable::del(std::string value)
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

SquareSizeTable::~SquareSizeTable()
{
    for (int i = 0; i < size; i++)
    {
        delete storage[i];
    }

    delete[] storage;
}