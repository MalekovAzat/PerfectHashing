#ifndef NODE_H
#define NODE_H

#include <string>

enum NodeStates
{
    NOT_FOUNDED = -4,
    DELETED = -3,
    NOT_SETTED = -2,
    NOT_INSERTED = -1,
};

class Node
{
public:
    // Node();
    Node(int key = NOT_SETTED, std::string value = "");
    
    //copyconstructor
    Node(const Node&);
    
    friend bool operator==(const Node& left, const Node& right);
    friend bool operator!=(const Node& left, const Node& right);
    int key;
    std::string value;  
};

#endif // !NODE_H