#ifndef DIRECTHASHTABLE_H
#define DIRECTHASHTABLE_H

#include <iostream>
#include "AbstractHashTable.h"
#include "../tools/UniversalHash.h"

class DirectHashTable: public AbstractHashTable
{
public:
    /* 
     * Default counstructor
     */
    DirectHashTable(int size);
    // TODO: create at least 3 constructors for different input methods

    inline ~DirectHashTable(){
        delete [] storage;
    };

    /* 
     * The method inserts the key to table
     */
    virtual int insert(int key, std::string value);

    /* 
     * The method searchs sert the key to table
     */
    virtual Node search(int key);

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
    int c1;
    int c2;
    Node** storage;
    UniversalHash hashFunction;
};

#endif // !DIRECTHASHTABLE_H