#include "AVL.hpp"

Node *AVL::ArrayAdd(Node *subNode, const int &item, int *array, const int &arrayLength) // private
{
    if (subNode == NULL)
        subNode = new Node(item, array, arrayLength);
    else if (item < subNode->data)
    {
        subNode->left = ArrayAdd(subNode->left, item, array, arrayLength);

        if (Height(subNode->left) == Height(subNode->right) + 2)
        {
            if (item < subNode->left->data)
                subNode = SwapWithLeftChild(subNode);
            else
            {
                subNode->left = SwapWithRightChild(subNode->left);
                subNode = SwapWithLeftChild(subNode);
            }
        }
    }
    else if (item > subNode->data)
    {
        subNode->right = ArrayAdd(subNode->right, item, array, arrayLength);

        if (Height(subNode->right) == Height(subNode->left) + 2)
        {
            if (item > subNode->right->data)
                subNode = SwapWithRightChild(subNode);
            else
            {
                subNode->right = SwapWithLeftChild(subNode->right);
                subNode = SwapWithRightChild(subNode);
            }
        }
    }
    else
        ;
    subNode->Sort();
    subNode->height = Height(subNode);
    return subNode;
}

Node *AVL::SwapWithLeftChild(Node *subNode) // private
{
    Node *tmp = subNode->left;
    subNode->left = tmp->right;
    tmp->right = subNode;

    subNode->height = Height(subNode);
    tmp->height = 1 + max(Height(tmp->left), subNode->height);

    return tmp;
}

Node *AVL::SwapWithRightChild(Node *subNode) // private
{
    Node *tmp = subNode->right;
    subNode->right = tmp->left;
    tmp->left = subNode;

    subNode->height = Height(subNode);
    tmp->height = 1 + max(Height(tmp->right), subNode->height);

    return tmp;
}

bool AVL::DeleteNode(Node *&subNode) // private
{
    Node *delNode = subNode;

    if (subNode->right == NULL)
        subNode = subNode->left;
    else if (subNode->left == NULL)
        subNode = subNode->right;
    else
    {
        delNode = subNode->left;
        Node *parentNode = subNode;
        while (delNode->right != NULL)
        {
            parentNode = delNode;
            delNode = delNode->right;
        }
        subNode->data = delNode->data;
        if (parentNode == subNode)
            subNode->left = delNode->left;
        else
            parentNode->right = delNode->left;
    }
    delete delNode;
    return true;
}

void AVL::preorder(Node *subNode) // private
{
    if (subNode != NULL)
    {
        subNode->print();
        preorder(subNode->left);
        preorder(subNode->right);
    }
}

int AVL::Height(Node *subNode)
{
    if (subNode == NULL)
        return -1;
    return 1 + max(Height(subNode->left), Height(subNode->right));
}

AVL::AVL()
{
    root = NULL;
}

bool AVL::isEmpty() const
{
    return root == NULL;
}

void AVL::ArrAdd(const int &item, int *array, const int &arrayLength)
{
    root = ArrayAdd(root, item, array, arrayLength);
}

void AVL::preorder()
{
    preorder(root);
}

int AVL::Height()
{
    return Height(root);
}

void AVL::Clear()
{
    while (!isEmpty())
        DeleteNode(root);
}

AVL::~AVL()
{
    Clear();
}