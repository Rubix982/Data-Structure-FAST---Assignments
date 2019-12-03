#ifndef BTREE_H
#define BTREE_H

#include <queue>
#include <vector>
#include <iostream>

typedef unsigned long long ull;

template <typename T>
struct Data
{
    T data;
};

template <typename T>
struct Node
{
    Data<T> data;
    Data<T> *left, *right;

    Node(const Data<T> &data = Data<T>(), Data<T> *left = nullptr, Data<T> *right = nullptr)
        : data(data), left(left), right(right) {}
};

template <typename T>
class bt
{

private:
    // Pointer to the root
    Node<T> *root;

    // Helper private functions, in an attempt to encapsulate the pointer to the 'root'

    void insert(const T &key, Node<T> *node);
    Node<T> *search(T key, Node<T> *node);

    T findmin(Node<T> *node);
    T findmax(Node<T> *node);
    void bfs(Node<T> *node);
    void dfs(Node<T> *node);

    void preorderTraversal(Node<T> *node);
    void inorderTraversal(Node<T> *node);
    void postorderTraversal(Node<T> *node);

    ull height(Node<T> *node);
    void isBST(Node<T> *node, std::vector<T> &vect);

    void deleteTree(Node<T> *node);
    void deleteNode(const T &x, Node<T> *node);

public:
    // Functions for public access, the API

    bt();

    Node<T> *search(T key);
    void insert(T key);
    T findmin();
    T findmax();
    Node<T> *copying(Node<T> *root);
    void bfs();
    void dfs();

    void preorderTraversal();
    void inorderTraversal();
    void postorderTraversal();

    ull height();
    bool isBST();
    bool isEmpty();

    void deleteTree();
    void deleteNode(const T &x);

    ~bt();
};

// * The PRIVATE functions, STARTING from BELOW

template <typename T>
void bt<T>::insert(const T &key, Node<T> *node)
{
    if (node == nullptr)
    {
        node = new Node<T>(T, nullptr, nullptr);
        return;
    }

    if (node->left == nullptr)
        node->left = new Node<T>(key, nullptr, nullptr);
    else if (node->right == nullptr)
        node->right = new Node<T>(key, nullptr, nullptr);
    else
    {
        insert(key, node->left);
        insert(key, node->right);
    }
}

template <typename T>
Node<T> *bt<T>::search(T key, Node<T> *node)
{
    if (node != NULL)
    {
        if (key == node->value)
            return node;
        else
        {
            return search(key, node->left);
            return search(key, node->right);
        }
    }
    else
        return NULL;
}

template <typename T>
T bt<T>::findmin(Node<T> *node)
{
}

template <typename T>
T bt<T>::findmax(Node<T> *node)
{
}

template <typename T>
void bfs(Node<T> *node)
{
    queue<T> q;

    if (node != nullptr)
    {
        q.push(root->data);

        while (!q.empty())
        {
            T = q.front();
            b
                q.pop();

            if (node->left)
                q.push(node->left->data);
            else if (node->right)
                q.push(node->right->data);
        }
    }
}

template <typename T>
void bt<T>::dfs(Node<T> *node)
{
    this->inorderTraversal(this->root);
}

template <typename T>
void bt<T>::preorderTraversal(Node<T> *node)
{
    if (node != nullptr)
    {
        std::cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

template <typename T>
void bt<T>::inorderTraversal(Node<T> *node)
{
    if (node != nullptr)
    {
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }
}

template <typename T>
void bt<T>::postorderTraversal(Node<T> *node)
{
    if (node != nullptr)
    {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->data << " ";
    }
}

template <typename T>
ull bt<T>::height(Node<T> *node)
{
    if (node == nullptr)
        return 0;

    ull left = height(node->left);
    ull right = height(node->right);

    return max(left, right) + 1;
}

template <typename T>
void bt<T>::isBST(Node<T> *node, std::vector<T> &vect)
{
    if (node != nullptr)
    {
        isBST(node->left, vect);
        vect.push_back(node->data);
        isBST(node->right, vect);
    }
}

template <typename T>
void bt<T>::deleteTree(Node<T> *node)
{
    if (node != nullptr)
    {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
        node = nullptr;
    }
}

template <typename T>
void bt<T>::deleteNode(const T &x, Node<T> *node)
{
    if (node == nullptr)
        return;
    else if (x < node->data)
        deleteNode(T, node->left);
    else if (x > node->data)
        deleteNode(T, node->right);

    if (node->left == nullptr and node->right == nullptr)
    {
        delete node;
        node = nullptr;
        return;
    }
    else if (root->left != nullptr && root->right != nullptr)
    {
        node->data = this->findmax(node->left)->
    }
}

// * The PRIVATE functions, ENDING from ABOVE

// * The PUBLIC functions, STARTING from BELOW

template <typename T>
bt<T>::bt() : root(nullptr) {}

template <typename T>
Node<T> *bt<T>::search(T key)
{
    this->search(T, this->root);
}

template <typename T>
void bt<T>::insert(T key)
{
    this->insert(key, this->root);
}

template <typename T>
T bt<T>::findmin()
{
    return this->findmin(this->root);
}

template <typename T>
T bt<T>::findmax()
{
    return this->findmax(this->root);
}

template <typename T>
Node<T> *bt<T>::copying(Node<T> *root)
{
    if (root == nullptr)
        return;
    else
        new Node<T>(root->data, copying(root->left), copying(root->right));
}

template <typename T>
void bt<T>::bfs()
{
    this->bfs(this->root);
}

template <typename T>
void bt<T>::dfs()
{
    this->dfs(this->root);
}

template <typename T>
void bt<T>::preorderTraversal()
{
    this->preorderTraversal(this->root);
}

template <typename T>
void bt<T>::inorderTraversal()
{
    this->inorderTraversal(this->root);
}

template <typename T>
void bt<T>::postorderTraversal()
{
    this->postorderTraversal(this->root);
}

template <typename T>
ull bt<T>::height()
{
    return this->height(this->root);
}

template <typename T>
bool bt<T>::isBST()
{
    std::vector<int> vect;
    isBST(this->root, vect);

    for (int i = 0; i < vect.size() - 1; ++i)
        if (vect[i] > vect[i + 1])
            return false;

    return true;
}

template <typename T>
bool bt<T>::isEmpty()
{
    return this->root == nullptr;
}

template <typename T>
void bt<T>::deleteTree()
{
    this->deleteTree(this->root);
}

template <typename T>
bt<T>::~bt()
{
    this->deleteTree(this->root);
}

// * The PUBLIC functions, ENDING from ABOVE

#endif