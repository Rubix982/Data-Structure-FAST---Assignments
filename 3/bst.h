#ifndef BSTREE_H
#define BSTREE_H

#include <stack>
#include <queue>
#include <vector>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <string>

typedef unsigned long long ull;

template <typename T>
struct Node
{
    T data;
    Node<T> *left, *right;

    Node(const T &data = T(), Node<T> *left = nullptr, Node<T> *right = nullptr)
        : data(data), left(left), right(right) {}
};

template <typename T>
class bst
{

private:
    // Pointer to the root
    Node<T> *root;

    // Helper private functions, in an attempt to encapsulate the pointer to the 'root'

    void insert(const T &key, Node<T> *&node);
    Node<T> *search(T key, Node<T> *node);

    std::vector<T> findmin(Node<T> *node, std::vector<T> &vect);
    std::vector<T> findmax(Node<T> *node, std::vector<T> &vect);
    void bfs(Node<T> *node);
    void dfs(Node<T> *node);

    void preorderTraversal(Node<T> *node);
    void inorderTraversal(Node<T> *node);
    void postorderTraversal(Node<T> *node);

    void preorderTraversal_Iter(Node<T> *node);
    void inorderTraversal_Iter(Node<T> *node);
    void postorderTraversal_Iter(Node<T> *node);

    ull height(Node<T> *node);
    void isBST(Node<T> *node, std::vector<T> &vect);
    ull traverseLeft(Node<T> *node);
    ull traverseRight(Node<T> *node);
    void traverseTree(Node<T> *node, std::vector<T> & vect);

    void deleteTree(Node<T> *node);
    void deleteNode(const T &x, Node<T> *node);

public:
    // Functions for public access, the API

    bst();

    Node<T> *search(T key);
    void insert(T key);
    std::vector<T> findmin(std::vector<T> &vect);
    std::vector<T> findmax(std::vector<T> &vect);
    Node<T> *copying(Node<T> *root);
    void bfs();
    void dfs();

    void preorderTraversal();
    void inorderTraversal();
    void postorderTraversal();

    void preorderTraversal_Iter();
    void inorderTraversal_Iter();
    void postorderTraversal_Iter();

    ull height();
    bool isBST();
    bool isEmpty();
    ull traverseLeft();
    ull traverseRight();
    void traverseTree();

    void deleteTree();
    void deleteNode(const T &x);

    ~bst();
};

// * The PRIVATE functions, STARTING from BELOW

template <typename T>
void bst<T>::insert(const T &key, Node<T> *&node)
{
    if (node == nullptr)
    {
        node = new Node<T>(key, nullptr, nullptr);
        return;
    }

    // Note to self, looks like almost Pythonic code?
    if (key <= node->data)
        if (node->left == nullptr)
            node->left = new Node<T>(key, nullptr, nullptr);
        else
            insert(key, node->left);
    else if (key > node->data)
        if (node->right == nullptr)
            node->right = new Node<T>(key, nullptr, nullptr);
        else
            insert(key, node->right);
}

template <typename T>
Node<T> *bst<T>::search(T key, Node<T> *node)
{
    if (node != NULL)
        if (key == node->value)
            return node;
        else if (key < node->value)
            return search(key, node->left);
        else
            return search(key, node->right);
    else
        return NULL;
}

template <typename T>
std::vector<T> bst<T>::findmin(Node<T> *node, std::vector<T> &vect)
{
    if (node->left != nullptr)
    {
        this->findmin(node->left, vect);
    }
    vect.push_back(node->data);
    return vect;
}

template <typename T>
std::vector<T> bst<T>::findmax(Node<T> *node, std::vector<T> &vect)
{
    if (node->right != nullptr)
        this->findmax(node->right, vect);
    vect.push_back(node->data);
    return vect;
}

template <typename T>
void bst<T>::bfs(Node<T> *node)
{
    std::queue<Node<T> *> q;

    if (node)
    {
        q.push(node);
        std::cout << node->data << " ";
    }

    while (!q.empty())
    {
        const Node<T> *const temp = q.front();
        q.pop();

        if (temp->left)
        {
            q.push(temp->left);
            std::cout << temp->left->data << " ";
        }

        if (temp->right)
        {
            q.push(temp->right);
            std::cout << temp->right->data << " ";
        }
    }
}

template <typename T>
void bst<T>::dfs(Node<T> *node)
{
    this->inorderTraversal(this->root);
}

template <typename T>
void bst<T>::preorderTraversal(Node<T> *node)
{
    if (node != nullptr)
    {
        std::cout << node->data << " ";
        preorderTraversal(node->left);
        preorderTraversal(node->right);
    }
}

template <typename T>
void bst<T>::inorderTraversal(Node<T> *node)
{
    if (node != nullptr)
    {
        inorderTraversal(node->left);
        std::cout << node->data << " ";
        inorderTraversal(node->right);
    }
}

template <typename T>
void bst<T>::postorderTraversal(Node<T> *node)
{
    if (node != nullptr)
    {
        postorderTraversal(node->left);
        postorderTraversal(node->right);
        std::cout << node->data << " ";
    }
}

template <typename T>
void bst<T>::preorderTraversal_Iter(Node<T> *node)
{
    if (node == nullptr)
        return;

    std::stack<Node<T> *> s;
    s.push(node);

    while (!s.empty())
    {
        const Node<T> *const temp = s.top();
        s.pop();

        std::cout << temp->data << " ";

        if (temp->right)
            s.push(temp->right);

        if (temp->left)
            s.push(temp->left);
    }
}

template <typename T>
void bst<T>::inorderTraversal_Iter(Node<T> *node)
{
    if (node == nullptr)
        return;

    std::stack<Node<T> *> stack;

    Node<T> *curr = node;

    while (!stack.empty() || curr != nullptr)
    {
        if (curr != nullptr)
        {
            stack.push(curr);
            curr = curr->left;
        }
        else
        {
            curr = stack.top();
            stack.pop();
            std::cout << curr->data << " ";

            curr = curr->right;
        }
    }
}

template <typename T>
void bst<T>::postorderTraversal_Iter(Node<T> *node)
{
    if (node == nullptr)
        return;

    std::stack<Node<T> *> s;
    std::stack<T> out;
    s.push(node);

    while (!s.empty())
    {
        const Node<T> *const temp = s.top();
        s.pop();

        out.push(temp->data);

        if (temp->left)
            s.push(temp->left);

        if (temp->right)
            s.push(temp->right);
    }

    while (!out.empty())
    {
        std::cout << out.top() << " ";
        out.pop();
    }
}

template <typename T>
ull bst<T>::height(Node<T> *node)
{
    if (node == nullptr)
        return 0;

    ull left = height(node->left);
    ull right = height(node->right);

    return std::max(left, right) + 1;
}

template <typename T>
void bst<T>::isBST(Node<T> *node, std::vector<T> &vect)
{
    if (node != nullptr)
    {
        isBST(node->left, vect);
        vect.push_back(node->data);
        isBST(node->right, vect);
    }
}

template <typename T>
ull bst<T>::traverseLeft(Node<T> *node)
{

    if (node == nullptr || node->left == nullptr)
        return 0;

    ull count = 1;

    while (node = node->left, node != nullptr)
        count++;

    return count;
}

template <typename T>
ull bst<T>::traverseRight(Node<T> *node)
{

    if (node == nullptr || node->right == nullptr)
        return 0;

    ull count = 1;

    while (node = node->right, node != nullptr)
        count++;

    return count;
}

template <typename T>
void bst<T>::traverseTree(Node<T> *node, std::vector<T> & vect)
{

    if (node != nullptr)
    {
        ull left = this->traverseLeft(node);
        ull right = this->traverseRight(node);
        traverseTree(node->left);
        traverseTree(node->right);

        ull maxx = std::max(left, right);
        std::cout << "Max: " << maxx << " left: " << left << " right: " << right << " node_data: " << node->data << "\n";
    }
}

template <typename T>
void bst<T>::deleteTree(Node<T> *node)
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
void bst<T>::deleteNode(const T &x, Node<T> *node)
{
    if (node == nullptr)
        return;
    else if (x < node->data)
        deleteNode(x, node->left);
    else if (x > node->data)
        deleteNode(x, node->right);

    if (node->left == nullptr and node->right == nullptr)
    {
        delete node;
        node = nullptr;
        return;
    }
    else if (root->left && root->right != nullptr)
    {
        node->data = this->findmax(node->left);
    }
}

// * The PRIVATE functions, ENDING from ABOVE

// * The PUBLIC functions, STARTING from BELOW

template <typename T>
bst<T>::bst() : root(nullptr) {}

template <typename T>
Node<T> *bst<T>::search(T key)
{
    this->search(key, this->root);
}

template <typename T>
void bst<T>::insert(T key)
{
    this->insert(key, this->root);
    // root = this->insert(key, this->root);
}

template <typename T>
std::vector<T> bst<T>::findmin(std::vector<T> &vect)
{
    return this->findmin(this->root, vect);
}

template <typename T>
std::vector<T> bst<T>::findmax(std::vector<T> &vect)
{
    return this->findmax(this->root, vect);
}

template <typename T>
Node<T> *bst<T>::copying(Node<T> *root)
{
    if (root == nullptr)
        return nullptr;
    else
        new Node<T>(root->data, copying(root->left), copying(root->right));
}

template <typename T>
void bst<T>::bfs()
{
    this->bfs(this->root);
    std::cout << "\n";
}

template <typename T>
void bst<T>::dfs()
{
    this->dfs(this->root);
}

template <typename T>
void bst<T>::preorderTraversal()
{
    this->preorderTraversal(this->root);
    std::cout << "\n";
}

template <typename T>
void bst<T>::inorderTraversal()
{
    this->inorderTraversal(this->root);
    std::cout << "\n";
}

template <typename T>
void bst<T>::postorderTraversal()
{
    this->postorderTraversal(this->root);
    std::cout << "\n";
}

template <typename T>
void bst<T>::preorderTraversal_Iter()
{
    this->preorderTraversal_Iter(this->root);
    std::cout << "\n";
}

template <typename T>
void bst<T>::inorderTraversal_Iter()
{
    this->inorderTraversal_Iter(this->root);
    std::cout << "\n";
}

template <typename T>
void bst<T>::postorderTraversal_Iter()
{
    this->postorderTraversal_Iter(this->root);
    std::cout << "\n";
}

template <typename T>
ull bst<T>::height()
{
    return this->height(this->root);
}

template <typename T>
bool bst<T>::isBST()
{
    std::vector<int> vect;
    isBST(this->root, vect);

    for (int i = 0; i < vect.size() - 1; ++i)
        if (vect[i] > vect[i + 1])
            return false;

    return true;
}

template <typename T>
bool bst<T>::isEmpty()
{
    return this->root == nullptr;
}

template <typename T>
void bst<T>::deleteTree()
{
    this->deleteTree(this->root);
}

template <typename T>
ull bst<T>::traverseLeft()
{
    return this->traverseLeft(this->root);
}

template <typename T>
ull bst<T>::traverseRight()
{
    return this->traverseRight(this->root);
}

template <typename T>
void bst<T>::traverseTree()
{
    std::vector<T> vect;
    this->traverseTree(this->root, vect);

    std::cout << vect.size() << "\n";

    for( const auto & value : vect ) std::cout << valiue << " ";
}

template <typename T>
bst<T>::~bst()
{
    this->deleteTree(this->root);
}

// * The PUBLIC functions, ENDING from ABOVE

#endif