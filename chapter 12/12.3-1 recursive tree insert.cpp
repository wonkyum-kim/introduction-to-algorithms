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

	/* iterative version */
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

	/* recursive version */
	void recursive_tree_insert(const T& k) {
		recursive_tree_insert(nullptr, root.get(), k);
	}

	//------------------------------------------------------

	void preorder_tree_walk() {
		preorder_tree_walk(root.get());
	}

	void inorder_tree_walk() {
		inorder_tree_walk(root.get());
	}

	void postorder_tree_walk() {
		postorder_tree_walk(root.get());
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

	void recursive_tree_insert(Node* p, Node* x, const T& k) {
		if (!x) {
			std::unique_ptr<Node> z = std::make_unique<Node>(k);
			z->parent = p;
			if (p && z->key < p->key) {
				p->left = std::move(z);
			}
			else if (p && z->key > p->key) {
				p->right = std::move(z);
			}
			else {	// !p
				root = std::move(z);
			}
		}
		else if (k < x->key) {
			recursive_tree_insert(x, x->left.get(), k);
		}
		else {
			recursive_tree_insert(x, x->right.get(), k);
		}
	}

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

	/* recursive version */

	Node* recursive_tree_minimum(Node* x) {
		if (x->left) {
			return recursive_tree_minimum(x->left.get());
		}
		else {
			return x;
		}
	}

	Node* recursive_tree_maximum(Node* x) {
		if (x->right) {
			return recursive_tree_maximum(x->right.get());
		}
		else {
			return x;
		}
	}

	//------------------------------------------------------

	void preorder_tree_walk(Node* x) {
		if (x) {
			std::cout << x->key << ' ';
			preorder_tree_walk(x->left.get());
			preorder_tree_walk(x->right.get());
		}
	}

	void inorder_tree_walk(Node* x) {
		if (x) {
			inorder_tree_walk(x->left.get());
			std::cout << x->key << ' ';
			inorder_tree_walk(x->right.get());
		}
	}

	void postorder_tree_walk(Node* x) {
		if (x) {
			postorder_tree_walk(x->left.get());
			postorder_tree_walk(x->right.get());
			std::cout << x->key << ' ';
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

	Node* tree_predecessor(Node* x) {
		if (x->left) {
			return tree_maximum(x->left.get());
		}
		Node* y = x->parent;
		while (y && x == y->left.get()) {
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
	std::vector<int> v(101);
	std::iota(v.begin() + 1, v.end(), 1);

	std::shuffle(v.begin() + 1, v.end(), gen);
	for (auto i = 1; i < v.size(); ++i) {
		bst.recursive_tree_insert(v[i]);
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
