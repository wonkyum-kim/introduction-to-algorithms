#include <iostream>
#include <utility>
#include <memory>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>
#include <crtdbg.h>

std::mt19937 gen(std::random_device{}());

template<typename T>
class BST {
private:
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
		z->parent = y;
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
		if (x) {
			inorder_tree_walk(x->left.get());
			std::cout << x->key << ' ';
			inorder_tree_walk(x->right.get());
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
		if (!z->left) {
			Node* pz = transplant(z, std::move(z->right));
			// delete heap memory
			auto upz = std::unique_ptr<Node>(pz);
		}
		else if (!z->right) {
			Node* pz = transplant(z, std::move(z->left));
			// delete heap memory
			auto upz = std::unique_ptr<Node>(pz);
		}
		else {
			Node* y = tree_minimum(z->right.get());
			if (y->parent == z) {
				Node* pz = transplant(z, std::move(z->right));
				y->left = std::move(pz->left);
				y->left->parent = y;
				// delete heap memory
				auto upz = std::unique_ptr<Node>(pz);
			}
			else {
				Node* py = transplant(y, std::move(y->right));
				py->right = std::move(z->right);
				py->right->parent = py;
				// delete heap memory
				auto upy = std::unique_ptr<Node>(py);
				Node* pz = transplant(z, std::move(upy));
				py->left = std::move(pz->left);
				py->left->parent = py;
				// delete heap memory
				auto upz = std::unique_ptr<Node>(pz);
			}
		}
	}

	//------------------------------------------------------

};

int main()
{
	BST<int> bst;
	std::vector<int> v(101);
	std::iota(v.begin() + 1, v.end(), 1);

	std::shuffle(v.begin() + 1, v.end(), gen);
	for (auto i = 1; i < v.size(); ++i) {
		bst.tree_insert(v[i]);
	}

	bst.inorder_tree_walk();
	std::cout << '\n';
	std::cout << '\n';

	std::shuffle(v.begin() + 1, v.end(), gen);
	for (auto i = 1; i < v.size(); i++) {
		bst.tree_delete(v[i]);
	}

	std::cout << "delete complete \n";
	bst.inorder_tree_walk();
	std::cout << '\n';

	std::shuffle(v.begin() + 1, v.end(), gen);
	for (auto i = 1; i < v.size(); ++i) {
		bst.tree_insert(v[i]);
	}

	bst.inorder_tree_walk();
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}
