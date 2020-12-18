#ifndef SQUARESIZETABLE_H
#define SQUARESIZETABLE_H

#include "AbstractHashTable.h"
#include "../tools/UniversalHash.h"

class SquareSizeTable: public AbstractHashTable
{
public:
    SquareSizeTable(int size, int maxKeyValue = MAX_KEY_VALUE);

    SquareSizeTable(int size, UniversalHash* hashFunctionLvl2);

    virtual int insert(unsigned int key, std::string value) override;

    virtual Node search(unsigned int key) override;

    virtual int del(std::string value) override;

    ~SquareSizeTable();

private:
    Node** saveNodes();
    void updateHashFunction();
    void clearStorage();
    int fixCollision(int key, std::string value);

private:
    int size;
    int maxKeyValue;
    Node** storage;
    UniversalHash* hashFunction;
};

#endif // !SQUARESIZETABLE_H