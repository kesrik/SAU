#ifndef QUEUENODE_HPP
#define QUEUENODE_HPP

#include <iostream>

class QueueNode
{ 
public:

    int data;
    QueueNode *next;

    QueueNode(const int &data = int(), QueueNode *next = NULL);
};
#endif