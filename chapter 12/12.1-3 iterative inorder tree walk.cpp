#include <iostream>
#include <utility>
#include <memory>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

std::mt19937 gen(std::random_device{}());

template<typename T>
class BST {
private:
	enum class From {
		PARENT,
		LEFT,
		RIGHT
	};

	struct Node {
		T key;
		Node* parent;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		Node(const T& k) :
			key{ k }, parent{ nullptr }, left{ nullptr }, right{ nullptr } {}
	};
public:
	//------------------------------------------------------

	std::unique_ptr<Node> root = nullptr;

	//------------------------------------------------------

	Node* tree_search(const T& k) {
		return tree_search(root.get(), k);
	}

	Node* iterative_tree_search(const T& k) {
		return iterative_tree_search(root.get(), k);
	}

	//------------------------------------------------------

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
			z->parent = y;
			y->left = std::move(z);
		}
		else {
			z->parent = y;
			y->right = std::move(z);
		}
	}

	//------------------------------------------------------

	void inorder_tree_walk() {
		inorder_tree_walk(root.get());
	}

	//------------------------------------------------------

	void tree_delete(const T& k) {
		auto z = tree_search(k);
		if (z) {
			tree_delete(z);
		}
		else {
			return;
		}
	}

	//------------------------------------------------------

private:

	//------------------------------------------------------

	/* recursive version */

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

	/* iterative version */

	Node* iterative_tree_search(Node* x, const T& k) {
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

	//------------------------------------------------------

	/* iterative version */

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

	//------------------------------------------------------

	void inorder_tree_walk(Node* x) {
		From pred = From::PARENT;
		auto curr = x;
		while (curr) {
			if (pred == From::PARENT) {
				if (curr->left) {
					curr = curr->left.get();
					pred = From::PARENT;
				}
				else {
					pred = From::LEFT;
				}
			}
			else if (pred == From::LEFT) {
				std::cout << curr->key << ' ';
				if (curr->right) {
					curr = curr->right.get();
					pred = From::PARENT;
				}
				else {
					pred = From::RIGHT;
				}
			}
			else {
				if (!curr->parent) {
					curr = nullptr;
					break;
				}
				if (curr == curr->parent->left.get()) {
					pred = From::LEFT;
				}
				else {
					pred = From::RIGHT;
				}
				curr = curr->parent;
			}
		}
	}

	//------------------------------------------------------

	Node* tree_successor(Node* x) {
		if (x->right) {
			return tree_minimum(x->right.get());
		}
		Node* y = x->parent;
		while (y && x == y->right.get()) {
			x = y;
			y = y->parent;
		}
		return y;
	}

	//------------------------------------------------------

	Node* transplant(Node* u, std::unique_ptr<Node>&& v) {
		if (v) {
			v->parent = u->parent;
		}
		Node* w = nullptr;
		if (!u->parent) {
			w = root.release();
			root = std::move(v);
		}
		else if (u == u->parent->left.get()) {
			w = u->parent->left.release();
			u->parent->left = std::move(v);
		}
		else {
			w = u->parent->right.release();
			u->parent->right = std::move(v);
		}
		return w;
	}

	void tree_delete(Node* z) {
		Node* x = nullptr;
		Node* xp = nullptr;
		if (!z->left) {
			Node* pz = transplant(z, std::move(z->right));
			auto upz = std::unique_ptr<Node>(pz);
		}
		else if (!z->right) {
			Node* pz = transplant(z, std::move(z->left));
			auto upz = std::unique_ptr<Node>(pz);
		}
		else {
			Node* y = tree_minimum(z->right.get());
			x = y->right.get();
			if (y->parent == z) {
				//
				xp = y;
				Node* pz = transplant(z, std::move(z->right));
				y->left = std::move(pz->left);
				y->left->parent = y;
				auto upz = std::unique_ptr<Node>(pz);
			}
			else {
				xp = y->parent;
				Node* py = transplant(y, std::move(y->right));
				py->right = std::move(z->right);
				py->right->parent = py;
				auto upy = std::unique_ptr<Node>(py);
				Node* pz = transplant(z, std::move(upy));
				py->left = std::move(pz->left);
				py->left->parent = py;
				auto upz = std::unique_ptr<Node>(pz);
			}
		}
	}

	//------------------------------------------------------

};

int main()
{
	BST<int> bst;
	bst.tree_insert(5);
	bst.tree_insert(8);
	bst.tree_insert(2);
	bst.tree_insert(1);
	bst.tree_insert(3);
	bst.inorder_tree_walk();
}
