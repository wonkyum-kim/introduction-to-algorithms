#include <iostream>
#include <memory>
#include <utility>

template <typename T>
struct Binary_search_tree_node {
    T key;
    std::unique_ptr<Binary_search_tree_node<T>> left;
    std::unique_ptr<Binary_search_tree_node<T>> right;
    Binary_search_tree_node<T>* parent;

    Binary_search_tree_node(const T& key) : key{ key }, parent{ nullptr } {}
};

// recursive version
template<typename T>
Binary_search_tree_node<T>* tree_search(Binary_search_tree_node<T>* x, const T& k)
{
    if (!x || x->key == k) {
        return x;
    }
    if (k < x->key) {
        return tree_search(x->left.get(), k);
    }
    else {
        return tree_search(x->right.get(), k);
    }
}


/*
// iterative version
template<typename T>
Binary_search_tree_node<T>* tree_search(const Binary_search_tree_node<T>* x, const T& k)
{
    while (x && k != x->key) {
        if (k < x->key) {
            x = x->left.get();
        }
        else {
            x = x->right.get();
        }
    }
    return x;
}
*/

//-------------------------------------------------------------


template<typename T>
Binary_search_tree_node<T>* tree_minimum(Binary_search_tree_node<T>* x)
{
    while (x->left.get()) {
        x = x->left.get();
    }
    return x;
}

template<typename T>
Binary_search_tree_node<T>* tree_maximum(Binary_search_tree_node<T>* x)
{
    while (x->right.get()) {
        x = x->right.get();
    }
    return x;
}

//-------------------------------------------------------------

template<typename T>
Binary_search_tree_node<T>* tree_successor(Binary_search_tree_node<T>* x)
{
    if (x->right.get()) {
        return tree_minimum(x->right.get());
    }
    auto y = x->parent;
    while (y && x == y->right.get()) {
        x = y;
        y = y->parent;
    }
    return y;
}

template<typename T>
Binary_search_tree_node<T>* tree_predecessor(Binary_search_tree_node<T>* x)
{
    if (x->left) {
        return tree_maximum(x->left.get());
    }
    auto y = x->parent;
    while (y && x == y->left.get()) {
        x = y;
        y = y->parent;
    }
    return y;
}

//-------------------------------------------------------------

template<typename T>
void tree_insert(std::unique_ptr<Binary_search_tree_node<T>>& root, std::unique_ptr<Binary_search_tree_node<T>>& z)
{
    Binary_search_tree_node<T>* y = nullptr;
    auto x = root.get();
    while (x) {
        y = x;
        if (z.get()->key < x->key) {
            x = x->left.get();
        }
        else {
            x = x->right.get();
        }
    }
    z.get()->parent = y;
    if (!y) {
        root = std::move(z);
    }
    else if (z.get()->key < y->key) {
        y->left = std::move(z);
    }
    else {
        y->right = std::move(z);
    }
}

//-------------------------------------------------------------

template<typename T>
void transplant(std::unique_ptr<Binary_search_tree_node<T>>& root, Binary_search_tree_node<T>* u, std::unique_ptr<Binary_search_tree_node<T>>&& v)
{
    if (!u->parent) {
        root = std::move(v);
    }
    else if (u == u->parent->left.get()) {
        u->parent->left = std::move(v);
    }
    else {
        u->parent->right = std::move(v);
    }
    if (v) {
        v.get()->parent = u->parent;
    }
}

// not to use now...
template<typename T>
void tree_delete(std::unique_ptr<Binary_search_tree_node<T>>& root, Binary_search_tree_node<T>* z)
{
    if (!z->left.get()) {
        transplant(root, z, std::move(z->right));
    }
    else if (!z->right.get()) {
        transplant(root, z, std::move(z->left));
    }
    else {
        auto y = tree_minimum(z->right.get());
        if (y->parent != z) {
            transplant(root, y, std::move(y->right));
            y->right = std::move(z->right);
            y->right->parent = y;
        }
        transplant(root, z, y);
        y->left = std::move(z->left);
        y->left.get()->parent = y;
    }
}

//-------------------------------------------------------------

template<typename T>
std::unique_ptr<Binary_search_tree_node<T>> make_binary_search_tree_node(T key)
{
    auto node = std::make_unique<Binary_search_tree_node<int>>(key);
    return node;
}


template<typename T>
void inorder_traverse(Binary_search_tree_node<T>* node)
{
    if (node) {
        inorder_traverse(node->left.get());
        std::cout << node->key << ' ';
        inorder_traverse(node->right.get());
    }
}

template<typename T>
void inorder_traverse(std::unique_ptr<Binary_search_tree_node<T>>& node)
{
    inorder_traverse(node.get());
}


int main()
{
    auto node1 = make_binary_search_tree_node(15);
    auto node2 = make_binary_search_tree_node(6);
    auto node3 = make_binary_search_tree_node(18);
    auto node4 = make_binary_search_tree_node(3);
    auto node5 = make_binary_search_tree_node(7);

    tree_insert(node1, node2);
    tree_insert(node1, node3);
    tree_insert(node1, node4);
    tree_insert(node1, node5);

    std::cout << "inorder traverse " << '\n';
    inorder_traverse(node1);

    std::cout << '\n';

    auto find1 = tree_search(node1.get(), 7);
    if (find1) {
        std::cout << "success to find a key : " << find1->key << '\n';
    }
    else {
        std::cout << "fail to find a key" << '\n';
    }    
}
