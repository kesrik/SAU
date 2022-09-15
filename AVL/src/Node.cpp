#include "Node.hpp"

Node::Node(const int &data, int *array, const int &arrayLength, Node *left, Node *right)
{
    this->data = data;
    this->array = array;
    this->arrayLength = arrayLength;
    this->left = left;
    this->right = right;
    this->height = 0;
}

Node::~Node()
{
    if (array != NULL)
    {
        delete[] array;
    }
}

void Node::Sort()
{
    if (array != NULL)
    {
        Radix *radix = new Radix(array, arrayLength);
        int *sorted = radix->Sort();
        delete[] array;
        array = sorted;
    }
}

void Node::print()
{
    cout << endl;
    cout << this->data << ": ";
    for (int i = 0; i < this->arrayLength; i++)
    {
        cout << this->array[i] << " ";
    }
}