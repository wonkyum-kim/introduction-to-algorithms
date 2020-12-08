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

	void tree_insert(const T& k) {
		auto z = std::make_unique<Node>(k);
		Node* y = nullptr;
		Node* x = root.get();
		Node* pred = nullptr;
		while (x) {
			y = x;
			if (z->key < x->key) {
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
		else if (z->key < y->key) {
			z->succ = y;
			y->left = std::move(z);
			if (pred) {
				pred->succ = y->left.get();
			}
		}
		else {
			y->right = std::move(z);
			y->right->succ = y->succ;
			y->succ = y->right.get();
		}
	}

	Node* tree_search(const T& k) {
		return tree_search(root.get(), k);
	}

	void tree_delete(const T& k) {
		auto z = tree_search(k);
		if (z) {
			tree_delete(z);
		}
		else {
			return;
		}
	}

private:
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

	void inorder_tree_walk(Node* x) {
		if (x) {
			inorder_tree_walk(x->left.get());
			std::cout << x->key << ' ';
			inorder_tree_walk(x->right.get());
		}
	}

	Node* parent(Node* x) {
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

	Node* tree_predecessor(Node* x) {
		if (x->left) {
			return tree_maximum(x->left.get());
		}
		else {	// !x->left
			Node* y = parent(x);
			while (y && x == y->left.get()) {
				x = y;
				y = parent(y);
			}
			return y;
		}
	}

	Node* transplant(Node* u, std::unique_ptr<Node>&& v) {
		Node* up = parent(u);
		Node* w = nullptr;
		if (!up) {
			w = root.release();
			root = std::move(v);
		}
		else if (u == up->left.get()) {
			w = up->left.release();
			up->left = std::move(v);
		}
		else {		
			w = up->right.release();
			up->right = std::move(v);
		}
		return w;
	}

	void tree_delete(Node* z) {
		Node* pred = tree_predecessor(z);
		Node* zsucc = z->succ;
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
			if (parent(y) == z) {
				Node* pz = transplant(z, std::move(z->right));
				y->left = std::move(pz->left);
				auto upz = std::unique_ptr<Node>(pz);
			}
			else {
				Node* py = transplant(y, std::move(y->right));
				py->right = std::move(z->right);
				auto upy = std::unique_ptr<Node>(py);
				Node* pz = transplant(z, std::move(upy));
				py->left = std::move(pz->left);
				auto upz = std::unique_ptr<Node>(pz);
			}
		}
		if (pred) {
			pred->succ = z->succ;
		}
	}

};

int main()
{
	BST<int> bst;
	std::vector<int> v(150);
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
}
