#include <iostream>
#include <utility>
#include <memory>

template<typename T>
class BST {
private:
	struct Node {
		T key;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		Node(const T& k) :
			key{k}, left{nullptr}, right{nullptr} {}
	};
public:
	std::unique_ptr<Node> root = nullptr;

	bool tree_search(const T& k) {
		return tree_search(root.get(), k);
	}

	bool iterative_tree_search(const T& k) {
		return iterative_tree_search(root.get(), k);
	}

	void tree_insert(const T& k) {
		auto z = std::make_unique<Node>(k);
		Node* y = nullptr;
		Node* x = root.get();
		while (x) {
			y = x;
			if (k < x->key) {
				x = x->left.get();
			}
			else {
				x = x->right.get();
			}
		}
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

	void inorer_tree_walk() {
		inorder_tree_walk(root.get());
	}

private:
	bool tree_search(Node* x, const T& k) {
		if (!x) {
			return false;
		}
		if (k == x->key) {
			return true;
		}
		else if (k < x->key) {
			return tree_search(x->left.get(), k);
		}
		else {
			return tree_search(x->right.get(), k);
		}
	}

	bool iterative_tree_search(Node* x, const T& k) {
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

	Node* tree_minimum(Node* x) {
		while (x->left) {
			x = x->left.get();
		}
		return x;
	}

	Node* tree_maximum(Node* x) {
		while (x->right) {
			x = x->right.get();
		}
		return x;
	}

	void inorder_tree_walk(Node* x) {
		if (x) {
			inorder_tree_walk(x->left.get());
			std::cout << x->key << ' ';
			inorder_tree_walk(x->right.get());
		}
	}
};

int main()
{
	BST<int> tree;
	tree.tree_insert(10);
	tree.tree_insert(20);
	tree.tree_insert(30);
	if (tree.tree_search(20)) {
		std::cout << "tree_search is okay" << '\n';
	}
	if (tree.iterative_tree_search(30)) {
		std::cout << "iterative_tree_search is okay" << '\n';
	}
	tree.inorer_tree_walk();
}
