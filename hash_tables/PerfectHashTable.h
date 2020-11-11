#ifndef PERFECTHASHTABLE_H
#define PERFECTHASHTABLE_H

#include <iostream>
#include "AbstractHashTable.h"
#include "../tools/UniversalHash.h"

class InternalHashTable: public AbstractHashTable
{
public:
    /*
     * Constructor for hash table
     * size of level2 (internal)  table
     */
    InternalHashTable(int size);

    InternalHashTable(int size, UniversalHash* hashFunctionLvl2);

    virtual int insert(int key, std::string value);

    virtual Node search(int key);

    virtual int del(std::string value);

    ~InternalHashTable();
private:
    int size;
    Node** storage;
    UniversalHash* hashFunction;
};


class PerfectHashTable /* : public AbstractHashTable */
{
public:
    /*
     * Constructor for hash table
     * size of level1 (external) table
     */
    PerfectHashTable(int size);

    /*
     * The function inserts key and his value to the table.
     */
    int insert(int key, std::string value);

    Node search(int key);

    int del(std::string value);

    void preprocessing(int size, Node** nodes);

    ~PerfectHashTable(){};

private:
    int size;
    
    UniversalHash hashFunctionLvl1;
    InternalHashTable** storage;
};



#endif // !PERFECTHASHTABLE 