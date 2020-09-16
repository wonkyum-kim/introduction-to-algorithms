#include <iostream>
#include <memory>

template <typename T>
struct LCRS_binary_tree_node {
    T key;
    std::unique_ptr<LCRS_binary_tree_node<T>> left_child;
    std::unique_ptr<LCRS_binary_tree_node<T>> right_sibling;

    LCRS_binary_tree_node(const T& key) : key{ key } {}
};

template<typename T>
std::unique_ptr<LCRS_binary_tree_node<T>> make_LCRS_binary_tree_node(T key)
{
    auto node = std::make_unique<LCRS_binary_tree_node<int>>(key);
    return node;
}

template<typename T>
void make_left_child(std::unique_ptr<LCRS_binary_tree_node<T>>& main, std::unique_ptr<LCRS_binary_tree_node<T>>& sub)
{
    main.get()->left_child = std::move(sub);
}

template<typename T>
void make_right_sibling(std::unique_ptr<LCRS_binary_tree_node<T>>& main, std::unique_ptr<LCRS_binary_tree_node<T>>& sub)
{
    main.get()->right_sibling = std::move(sub);
}

template<typename T>
void inorder_traverse(LCRS_binary_tree_node<T>* node)
{
    if (node) {
        std::cout << node->key << ' ';
        auto x = node->left_child.get();
        while (x) {
            inorder_traverse(x);
            x = x->right_sibling.get();
        }
    }
}

template<typename T>
void inorder_traverse(std::unique_ptr<LCRS_binary_tree_node<T>>& node)
{
    inorder_traverse(node.get());
}


int main()
{
    auto node1 = make_LCRS_binary_tree_node(1);
    auto node2 = make_LCRS_binary_tree_node(2);
    auto node3 = make_LCRS_binary_tree_node(3);
    auto node4 = make_LCRS_binary_tree_node(4);
    auto node5 = make_LCRS_binary_tree_node(5);
    auto node6 = make_LCRS_binary_tree_node(6);
    auto node7 = make_LCRS_binary_tree_node(7);
    auto node8 = make_LCRS_binary_tree_node(8);
    auto node9 = make_LCRS_binary_tree_node(9);

    /*
                  1
                 /
                /
               /
              2---3---4
             /       /
            5---6   7
                   /
                  8---9
    */

    // level 1
    make_left_child(node1, node2);
    make_right_sibling(node1.get()->left_child, node3);
    make_right_sibling(node1.get()->left_child->right_sibling, node4);
    // level 2
    make_left_child(node1.get()->left_child, node5);
    make_right_sibling(node1.get()->left_child->left_child, node6);
    make_left_child(node1.get()->left_child->right_sibling->right_sibling, node7);
    // level 3
    make_left_child(node1.get()->left_child->right_sibling->right_sibling->left_child, node8);
    make_right_sibling(node1.get()->left_child->right_sibling->right_sibling->left_child->left_child, node9);
    // 1 2 5 6 3 4 7 8 9
    inorder_traverse(node1);
}
