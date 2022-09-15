#ifndef QUEUE_HPP
#define QUEUE_HPP

#include "QueueNode.hpp"

using namespace std;

class Queue
{
private:
    QueueNode *front;
    QueueNode *back;
    int length;

public:
    Queue();
    void clear();
    int count() const;
    bool isEmpty() const;
    void enqueue(const int &item);
    const int &peek() const;
    void dequeue();
    ~Queue();
};

#endif