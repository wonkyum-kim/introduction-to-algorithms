#include <iostream>
#include <utility>
#include <memory>
#include <random>
#include <algorithm>
#include <numeric>

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
		// z->parent = y;
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
		if (root) {
			inorder_tree_walk(root.get());
		}
		else {
			std::cout << "empty";
		}
	}

	//------------------------------------------------------

	void tree_delete(const T& k) {
		if (tree_search(k)) {
			auto z = tree_search(k);
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
		if (!x || k == x->key) {
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

	void transplant(Node* u, std::unique_ptr<Node>&& v) {
		if (v) {
			v->parent = u->parent;
		}
		if (!u->parent) {
			root = std::move(v);
		}
		else if (u == u->parent->left.get()) {
			u->parent->left = std::move(v);
		}
		else {
			u->parent->right = std::move(v);
		}
	}

	void tree_delete(Node* z) {
		if (!z->left && !z->right) {
			if (z->parent && z == z->parent->left.get()) {
				z->parent->left.reset(nullptr);
			}
			else if (z->parent && z == z->parent->right.get()) {
				z->parent->right.reset(nullptr);
			}
			else {
				root.reset(nullptr);
			}
		}
		else if (!z->left && z->right) {
			transplant(z, std::move(z->right));
		}
		else if (!z->right) {
			transplant(z, std::move(z->left));
		}
		else {
			/* set y */
			Node* zr_min = z->right.get();
			while (zr_min->left) {
				zr_min = zr_min->left.get();
			}
			std::unique_ptr<Node> y = nullptr;
			/* case 1 */
			if (zr_min->parent == z) {
				y = std::move(z->right);
				y->left = std::move(z->left);
				y->left->parent = y.get();
				transplant(z, std::move(y));
			}
			/* case 2 */
			else {
				y = std::move(zr_min->parent->left);
				std::unique_ptr<Node> x = nullptr;
				if (y->right) {
					x = std::move(y->right);
				}
				y->right = std::move(z->right);
				y->right->parent = y->right.get();
				if (x) {
					y->right->left = std::move(x);
					y->right->left->parent = y->right->left.get();
				}
				transplant(z, std::move(y));
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
	for (auto i = 1; i < v.size() / 10; i++) {
		bst.tree_delete(v[i]);
	}
	bst.inorder_tree_walk();
	std::cout << '\n';
	std::cout << "success";
}
