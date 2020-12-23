#ifndef NODE_H
#define NODE_H

#include <string>

enum NodeStates
{
    NOT_FOUNDED = -5,
    DELETED = -4,
    NOT_SETTED = -3,
    NOT_INSERTED = -2,
    ALREADY_INSERTED = -1,
};

class Node
{
public:
    Node(unsigned int key = NOT_SETTED, std::string value = "");

    //copy constructor
    Node(const Node &);

    friend bool operator==(const Node &left, const Node &right);
    friend bool operator!=(const Node &left, const Node &right);

    unsigned int key;
    std::string value;
};

#endif // !NODE_H