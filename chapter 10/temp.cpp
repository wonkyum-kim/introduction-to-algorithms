#include <iostream>
#include <memory>

template <typename T>
struct Binary_tree_node {
    T key;
    std::unique_ptr<Binary_tree_node<T>> left;
    std::unique_ptr<Binary_tree_node<T>> right;

    Binary_tree_node(const T& key) : key{ key } {}
};

template<typename T>
std::unique_ptr<Binary_tree_node<T>> make_binary_tree_node(T key)
{
    auto node = std::make_unique<Binary_tree_node<int>>(key);
    return node;
}

template<typename T>
void make_left_child(std::unique_ptr<Binary_tree_node<T>>& main, std::unique_ptr<Binary_tree_node<T>>& sub)
{
    main.get()->left = std::move(sub);
}

template<typename T>
void make_right_child(std::unique_ptr<Binary_tree_node<T>>& main, std::unique_ptr<Binary_tree_node<T>>& sub)
{
    main.get()->right = std::move(sub);
}

template<typename T>
void inorder_traverse(Binary_tree_node<T>* node)
{
    if (node) {
        inorder_traverse(node->left.get());
        std::cout << node->key << ' ';
        inorder_traverse(node->right.get());
    }
}

template<typename T>
void inorder_traverse(std::unique_ptr<Binary_tree_node<T>>& node)
{
    inorder_traverse(node.get());
}


int main()
{
    auto node1 = make_binary_tree_node(1);
    auto node2 = make_binary_tree_node(2);
    auto node3 = make_binary_tree_node(3);
    auto node4 = make_binary_tree_node(4);
    auto node5 = make_binary_tree_node(5);

    make_left_child(node1, node2);
    make_right_child(node1, node3);
    /* 
    make_left_child(node2, node4);
    make_right_child(node2, node5);
    */
    inorder_traverse(node1);
}
