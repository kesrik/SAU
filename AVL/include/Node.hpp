#ifndef NODE_HPP
#define NODE_HPP

#include "Radix.hpp"

class Node
{
public:
    int data;
    int *array;
    int arrayLength;
    Node *left;
    Node *right;
    int height;
    Node(const int &data,  int *array = NULL, const int &arrayLength = 0, Node *left = NULL, Node *right = NULL);
    void Sort();
    void print();
    ~Node();
};

#endif