#ifndef ABSTRACTHASHTABLE_H
#define ABSTRACTHASHTABLE_H

#include <string>
#include "../tools/Node.h"

class AbstractHashTable
{
public:
    AbstractHashTable(){};
    // AbstractHashTable(AbstractHashTable &&) = default;
    // AbstractHashTable(const AbstractHashTable &) = default;
    // AbstractHashTable &operator=(AbstractHashTable &&) = default;
    // AbstractHashTable &operator=(const AbstractHashTable &) = default;
    ~AbstractHashTable(){};

    virtual int insert(int key, std::string value) = 0;
    virtual Node search(int key) = 0;
    virtual void del(std::string value) = 0;
};

#endif // ABSTRACTHASHTABLE_H