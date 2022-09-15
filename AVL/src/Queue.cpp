#include "Queue.hpp"

Queue::Queue()
{
    front = back = NULL;
    length = 0;
}

void Queue::clear()
{while (!isEmpty())
    dequeue();
}

int Queue::count() const
{
    return length;
}

bool Queue::isEmpty() const
{
    return length == 0;
}

void Queue::enqueue(const int &item)
{
    QueueNode *last = new QueueNode(item);
    if (isEmpty())
        front = back = last;
    else
    {
        back->next = last;
        back = last;
    }
    length++;
}

const int &Queue::peek() const
{
    if (isEmpty())
        throw "Queue is empty";
    return front->data;
}

void Queue::dequeue()
{
    if (isEmpty())
        throw "Queue is empty";
    QueueNode *del = front;
    front = front->next;
    delete del;
    length--;
}

Queue::~Queue()
{
    clear();
}