#ifndef OPENHASHTABLE_H
#define OPENHASHTABLE_H

#include <iostream>
#include "AbstractHashTable.h"
#include "../tools/UniversalHash.h"

class OpenHashTable: public AbstractHashTable
{
public:
    /* 
     * Default counstructor
     */
    OpenHashTable(int size, int c1 = 1, int c2 = 0);

    inline ~OpenHashTable(){
        delete [] storage;
    };

    /* 
     * The method inserts the key to table
     */
    virtual int insert(unsigned int key, std::string value);

    /* 
     * The method searchs sert the key to table
     */
    virtual Node search(unsigned int key);

    /* 
     * The method searchs sert the key to table
     */
    virtual int del(std::string value);
    
    /* 
     * The method returns the Node by index
     */
    Node get(int index);

    int getHashValue(int key, int offset) const;
    
private:

    int calc_hash(int key, int offset) const;

    int internal_hash(int key);

private:
    int size;
    unsigned int c1;
    unsigned int c2;
    Node** storage;
    UniversalHash hashFunction;
};

#endif // !OPENHASHTABLE_H
