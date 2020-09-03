#include <iostream>
#include <memory>

template<typename T>
struct LCRS_binary_tree_node {
	T key;
	std::unique_ptr<LCRS_binary_tree_node<T>> left_child;
	std::unique_ptr<LCRS_binary_tree_node<T>> right_sibling;

	LCRS_binary_tree_node(const T key) : key{key} {}
};

template<typename T>
struct LCRS_binary_tree {
	std::unique_ptr< LCRS_binary_tree_node<T>> root;
};

template<typename T>
std::ostream& operator<< (std::ostream& os, const LCRS_binary_tree_node<T>* node) 
{
	// TBD...
	if (node) {
		os << node->key << ' ';
		os << node->right_sibling.get();
		os << node->left_child.get();
	}
	return os;
}

template<typename T>
std::ostream& operator<< (std::ostream& os, const LCRS_binary_tree<T>& tree)
{
	os << tree.root.get();
	return os;
}

int main()
{
	LCRS_binary_tree<int> tree;
	auto node1 = std::make_unique<LCRS_binary_tree_node<int>>(1);
	auto node2 = std::make_unique<LCRS_binary_tree_node<int>>(2);
	auto node3 = std::make_unique<LCRS_binary_tree_node<int>>(3);
	auto node4 = std::make_unique<LCRS_binary_tree_node<int>>(4);
	auto node5 = std::make_unique<LCRS_binary_tree_node<int>>(5);
	auto node6 = std::make_unique<LCRS_binary_tree_node<int>>(6);
	auto node7 = std::make_unique<LCRS_binary_tree_node<int>>(7);
	auto node8 = std::make_unique<LCRS_binary_tree_node<int>>(8);
	auto node9 = std::make_unique<LCRS_binary_tree_node<int>>(9);

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

	tree.root = std::move(node1);
	tree.root->left_child = std::move(node2);
	tree.root->left_child->right_sibling = std::move(node3);
	tree.root->left_child->right_sibling->right_sibling = std::move(node4);
	tree.root->left_child->left_child = std::move(node5);
	tree.root->left_child->left_child->right_sibling = std::move(node6);
	tree.root->left_child->right_sibling->right_sibling->left_child = std::move(node7);
	tree.root->left_child->right_sibling->right_sibling->left_child->left_child = std::move(node8);
	tree.root->left_child->right_sibling->right_sibling->left_child->left_child->right_sibling = std::move(node9);

	std::cout << tree;

}
