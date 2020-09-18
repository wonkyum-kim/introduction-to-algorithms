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

template<typename T>
std::unique_ptr<Binary_search_tree_node<T>> make_node(T key)
{
    auto node = std::make_unique<Binary_search_tree_node<int>>(key);
    return node;
}

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
    if (x->left.get()) {
        return tree_maximum(x->left.get());
    }
    auto y = x->parent;
    while (y && x == y->left.get()) {
        x = y;
        y = y->parent;
    }
    return y;
}

template<typename T>
void tree_insert(std::unique_ptr<Binary_search_tree_node<T>>& root, const T& k)
{
    auto z = make_node(k);
    Binary_search_tree_node<T>* y = nullptr;
    auto x = root.get();
    while (x) {
        y = x;
        if (k < x->key) {
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
    else if (k < y->key) {
        y->left = std::move(z);
    }
    else {
        y->right = std::move(z);
    }
}

template<typename T>
void transplant(std::unique_ptr<Binary_search_tree_node<T>>& root, Binary_search_tree_node<T>* u, std::unique_ptr<Binary_search_tree_node<T>>&& v)
{
    if (v) {
        v.get()->parent = u->parent;
    }
    if (!u->parent) {
        root = std::move(v);
    }
    else if (u == u->parent->left.get()) {
        u->parent->left = std::move(v);
    }
    else {
        u->parent->right = std::move(v);
    }
}

template<typename T>
void tree_delete(std::unique_ptr<Binary_search_tree_node<T>>& root, Binary_search_tree_node<T>* z)
{
    /* 
     * First case : z doesn't have a left child.
     * Transplant z->right node to the place of z node.
     */
    if (!z->left.get()) {
        transplant(root, z, std::move(z->right));
    }
    /*
     * Second case : z doesn't have a right child.
     * Transplant z->left node to the place of z node.
     */
    else if (!z->right.get()) {
        transplant(root, z, std::move(z->left));
    }
    else {
        // To find a successor key of z, I can't use the fuction, tree_minimum.
        auto s = z->right.get();
        std::unique_ptr<Binary_search_tree_node<T>> y;
        if (s->left.get()) {
            while (s->left.get()) {
                s = s->left.get();
            }
            y = std::move(s->parent->left);
        }
        else {
            y = std::move(z->right);
        }
        if (y->parent != z) {
            transplant(root, y.get(), std::move(y.get()->right));
            y.get()->right = std::move(z->right);
            y.get()->parent->parent = y.get();
        }
        auto temp = y.get();
        transplant(root, z, std::move(y));
        temp->left = std::move(z->left);
        temp->left.get()->parent = y.get();

    }
}

template<typename T>
void tree_delete(std::unique_ptr<Binary_search_tree_node<T>>& root, const T& k)
{
    auto z = tree_search(root.get(),k);
    tree_delete(root, z);
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
    auto root = make_node(15);
    tree_insert(root, 6);
    tree_insert(root, 3);
    tree_insert(root, 7);
    tree_insert(root, 18);

    inorder_traverse(root);
    std::cout << '\n';

    auto search = tree_search(root.get(), 15);
    if (search) {
        std::cout << search->key << " is founded in the binary search tree\n";
    }

    auto min = tree_minimum(root.get());
    if (min) {
        std::cout << min->key << " is minium value in the binary search tree\n";
    }

    auto max = tree_maximum(root.get());
    if (max) {
        std::cout << max->key << " is maximum value in the binary search tree\n";
    }

    tree_delete(root, 18);
    tree_delete(root, 7);
    inorder_traverse(root);
}
