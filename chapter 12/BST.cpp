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

	void inorder_tree_walk() {
		inorder_tree_walk(root.get());
	}

	bool tree_delete(const T& k) {
		if (iterative_tree_search(k)) {
			return tree_delete(root, k);
		}
		else {
			return false;
		}
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

	std::unique_ptr<Node>& tree_minimum(std::unique_ptr<Node>& x) {
		if (!x->left) {
			return x;
		}
		else {
			return tree_minimum(x->left);
		}
	}

	std::unique_ptr<Node>& tree_maximum(std::unique_ptr<Node>& x) {
		if (!x->right) {
			return x;
		}
		else {
			return tree_maximum(x->right);
		}
	}

	void inorder_tree_walk(Node* x) {
		if (x) {
			inorder_tree_walk(x->left.get());
			std::cout << x->key << ' ';
			inorder_tree_walk(x->right.get());
		}
	}

	bool tree_delete(std::unique_ptr<Node>& z, const T& k) {
		if (!z) {
			return false;
		}
		else if (z.get()->key == k) {
			// case 1: z is a leaf
			if (!z->left && !z->right) {
				z.reset();
				return true;
			}
			// case 2: z has one child 
			else if (!z->left || !z->right) {
				// case 2-1 : z has left child
				if (!z->right) {
					z = std::move(z->left);
				}
				// case 2-2: z has right child
				else {
					z = std::move(z->right);
				}
				return true;
			}
			// case 3: z has two children
			else {
				std::unique_ptr<Node>& swap = tree_maximum(z->left);
				z->key = swap->key;
				swap = std::move(swap->left);
				return true;
			}
		}
		else {
			if (k > z->key) {
				return tree_delete(z->right, k);
			}
			else {
				return tree_delete(z->left, k);
			}
		}
	}
	
};

int main()
{
	BST<int> bst;
	bst.tree_insert(10);
	bst.tree_insert(20);
	bst.tree_insert(30);
	bst.tree_insert(40);
	if (bst.tree_search(20)) {
		std::cout << "tree_search is okay" << '\n';
	}
	if (bst.iterative_tree_search(30)) {
		std::cout << "iterative_tree_search is okay" << '\n';
	}
	bst.inorder_tree_walk();
	bst.tree_delete(10);
	std::cout << '\n';
	bst.inorder_tree_walk();
	bst.tree_delete(40);
	std::cout << '\n';
	bst.inorder_tree_walk();
	bst.tree_delete(20);
	std::cout << '\n';
	bst.inorder_tree_walk();
	bst.tree_delete(30);
	std::cout << '\n';
	bst.inorder_tree_walk();

}
