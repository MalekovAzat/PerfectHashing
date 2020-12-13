#ifndef PERFECTHASHTABLE_H
#define PERFECTHASHTABLE_H

#include <iostream>
#include <limits>
#include <random>
#include <list>
#include "SquareSizeTable.h"

class PerfectHashTable /* : public AbstractHashTable */
{
public:
    /*
     * Constructor for hash table
     * size of level1 (external) table
     */
    PerfectHashTable(int size, int maxKeyValue = MAX_KEY_VALUE);

    /*
     * The function inserts key and his value to the table.
     */
    int insert(int key, std::string value);

    Node search(int key);

    int del(std::string value);

    int preprocessing(int size, Node** nodes, int compression = 4);
    int preprocessing(std::vector<unsigned int> keys, int compression);

    ~PerfectHashTable(){};

private:
    int maxKeyValue;
    int size;
    UniversalHash hashFunctionLvl1;
    SquareSizeTable** lvl2HashTables;
};



#endif // !PERFECTHASHTABLE 