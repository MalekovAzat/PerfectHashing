#include "Node.h"

Node::Node(const Node &node)
    : key(node.key), value(node.value)
{
}

Node::Node(unsigned int key, std::string value) : key(key), value(value){};

bool operator==(const Node &left, const Node &right)
{
    return (left.key == right.key && left.value == right.value);
}

bool operator!=(const Node &left, const Node &right)
{
    return !(left == right);
}