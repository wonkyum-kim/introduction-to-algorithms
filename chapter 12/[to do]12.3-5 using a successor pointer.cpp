#include <iostream>
#include <utility>
#include <memory>

template<typename T>
class BST {
private: 

	struct Node {
		T key;
		Node* succ;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		Node(const T& k) :
			key{ k }, succ{ nullptr }, left{ nullptr }, right{ nullptr } {}
	};

	std::unique_ptr<Node> root = nullptr;

public:

	void inorder_tree_walk() {
		inorder_tree_walk(root.get());
	}

	Node* tree_search(const T& k) {
		return tree_search(root.get(), k);
	}

	void tree_insert(const T& k) {
		tree_insert(root.get(), k);
	}

	void tree_delete(const T& k) {
		Node* z = tree_search(k);
		tree_delete(z);
	}

private:

	void inorder_tree_walk(Node* x) {
		if (x) {
			inorder_tree_walk(x->left.get());
			std::cout << x->key << ' ';
			inorder_tree_walk(x->right.get());
		}
	}

	Node* tree_maximum(Node* x) {
		while (x->right) {
			x = x->right.get();
		}
		return x;
	}

	Node* tree_minimum(Node* x) {
		while (x->left) {
			x = x->left.get();
		}
		return x;
	}

	// tree_search is unchanged.
	Node* tree_search(Node* x, const T& k) {
		if (!x) {
			return x;
		}
		if (k == x->key) {
			return x;
		}
		else if (k < x->key) {
			return tree_search(x->left.get(), k);
		}
		else {
			return tree_search(x->right.get(), k);
		}
	}

	Node* tree_parent(Node* x) {
		if (x == root.get()) {
			return nullptr;
		}
		Node* y = tree_maximum(x)->succ;
		if (!y) {
			y = root.get();
		}
		else {
			if (x == y->left.get()) {
				return y;
			}
			y = y->left.get();
		}
		while (x != y->right.get()) {
			y = y->right.get();
		}
		return y;
	}

	void tree_insert(Node* x, const T& k) {
		auto z = std::make_unique<Node>(k);
		Node* y = nullptr;
		Node* pred = nullptr;
		while (x) {
			y = x;
			if (k < x->key) {
				x = x->left.get();
			}
			else {
				pred = x;
				x = x->right.get();
			}
		}
		if (!y) {
			root = std::move(z);
		}
		else if (k < y->key) {
			z->succ = y;
			if (pred) {
				pred->succ = z.get();
			}
			y->left = std::move(z);
		}
		else {
			z->succ = y->succ;
			y->succ = z.get();
			y->right = std::move(z);
		}
	}

	Node* tree_predecessor(Node* x) {
		if (x->left) {
			return tree_maximum(x->left.get());
		}
		Node* y = root.get();
		Node* pred = nullptr;
		while (y) {
			if (y->key == x->key) {
				break;
			}
			if (y->key < x->key) {
				pred = y;
				y = y->right.get();
			}
			else {
				y = y->left.get();
			}
		}
		return pred;
	}

	void transplant(Node* u, std::unique_ptr<Node>&& v) {
		Node* p = tree_parent(u);
		if (!p) {
			root = std::move(v);
		}
		else if (u == p->left.get()) {
			p->left = std::move(v);
		}
		else {
			p->right = std::move(v);
		}
	}


	// working...
	void tree_delete(Node* z) {
		Node* pred = tree_predecessor(z);
		pred->succ = z->succ;
		if (!z->left) {
			transplant(z, std::move(z->right));
		}
		else if (!z->right) {
			transplant(z, std::move(z->left));
		}
		else {
			Node* y = tree_minimum(z->right.get());
			Node* temp = z->right.get();
			std::unique_ptr<Node> upy;
			if (y == z->right.get()) {
				upy = std::move(z->right);
			}
			else {
				while (temp->left) {
					temp = temp->left.get();
				}
				upy = std::move(tree_parent(temp)->left);
			}
			if (tree_parent(y) != z) {
				transplant(y, std::move(y->right));
				y->right = std::move(z->right);
			}
			y->left = std::move(z->left);
			transplant(z, std::move(upy));
		}
	}
};

int main()
{
	BST<int> bst;
	bst.tree_insert(10);
	bst.tree_insert(8);
	bst.tree_insert(12);
	bst.tree_insert(7);
	bst.tree_insert(9);
	bst.inorder_tree_walk();
	std::cout << '\n';
	bst.tree_delete(7);
	bst.inorder_tree_walk();

}
