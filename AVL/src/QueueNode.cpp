#include "QueueNode.hpp"

QueueNode::QueueNode(const int &data, QueueNode *next)
{
    this->data = data;
    this->next = next;
}