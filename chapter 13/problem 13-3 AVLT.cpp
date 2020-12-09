#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <random>
#include <vector>
#include <numeric>

/*
* balance factor = left subtree's height - right subtree's height
* the balance factor must be -1, 0 or 1.
* If the balance factor of a node is greater than 1(left heavy) or less than -1 (right heavy), the node needs to be rebalanced.
*/

std::mt19937 gen(std::random_device{}());

template<typename T>
class AVLT {
private:
	struct Node {
		T key;
		Node* parent;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		int height;
		Node(const T& k) :
			key{ k }, parent{ nullptr }, left{ nullptr }, right{ nullptr }, height{ 0 } {}
	};

	std::unique_ptr<Node> root = nullptr;

	int height(Node* x) {
		if (!x) {
			return 0;
		}
		else {
			return x->height;
		}
	}

	int balance(Node* x) {
		if (!x) {
			return 0;
		}
		else {
			return height(x->left.get()) - height(x->right.get());
		}
	}

	// helper function.
	void left_rotate(Node* x) {
		Node* xp = x->parent;
		if (!xp) {
			left_rotate(std::move(root));
		}
		else if (x == xp->left.get()) {
			left_rotate(std::move(xp->left));
		}
		else {
			left_rotate(std::move(xp->right));
		}
	}

	// helper function.
	void right_rotate(Node* x) {
		Node* xp = x->parent;
		if (!xp) {
			right_rotate(std::move(root));
		}
		else if (x == xp->left.get()) {
			right_rotate(std::move(xp->left));
		}
		else {
			right_rotate(std::move(xp->right));
		}
	}

	void left_rotate(std::unique_ptr<Node>&& x) {
		auto y = std::move(x->right);
		x->right = std::move(y->left);
		if (x->right) {
			x->right->parent = x.get();
		}
		y->parent = x->parent;
		Node* xp = x->parent;
		Node* px = nullptr;	// pointer x
		Node* py = nullptr;	// pointer y
		if (!xp) {
			px = x.release();
			root = std::move(y);
			root->left = std::unique_ptr<Node>(px);
			root->left->parent = root.get();
			py = root.get();
		}
		else if (x == xp->left) {
			px = x.release();
			xp->left = std::move(y);
			xp->left->left = std::unique_ptr<Node>(px);
			xp->left->left->parent = xp->left.get();
			py = xp->left.get();
		}
		else {
			px = x.release();
			xp->right = std::move(y);
			xp->right->left = std::unique_ptr<Node>(px);
			xp->right->left->parent = xp->right.get();
			py = xp->right.get();
		}

		// update heights
		px->height = std::max(height(px->left.get()), height(px->right.get()));
		py->height = std::max(height(py->left.get()), height(py->right.get()));

	}

	void right_rotate(std::unique_ptr<Node>&& x) {
		auto y = std::move(x->left);
		x->left = std::move(y->right);
		if (x->left) {
			x->left->parent = x.get();
		}
		y->parent = x->parent;
		Node* xp = x->parent;
		Node* px = nullptr;	// pointer x
		Node* py = nullptr;	// pointer y
		if (!xp) {
			px = x.release();
			py = root.get();
			root = std::move(y);
			root->right = std::unique_ptr<Node>(px);
			root->right->parent = root.get();
		}
		else if (x == xp->left) {
			px = x.release();
			xp->left = std::move(y);
			xp->left->right = std::unique_ptr<Node>(px);
			xp->left->right->parent = xp->left.get();
			py = xp->left.get();
		}
		else {
			px = x.release();
			xp->right = std::move(y);
			xp->right->right = std::unique_ptr<Node>(px);
			xp->right->right->parent = xp->right.get();
			py = xp->right.get();
		}

		// update heights
		px->height = std::max(height(px->left.get()), height(px->right.get()));
		py->height = std::max(height(py->left.get()), height(py->right.get()));
	}

	Node* search(Node* x, const T& k) {
		if (!x || x->key == k) {
			return x;
		}
		else if (x->key > k) {
			return search(x->left.get(), k);
		}
		else {
			return search(x->right.get(), k);
		}
	}

	void inorder_tree_walk(Node* x) {
		if (x) {
			inorder_tree_walk(x->left.get());
			std::cout << x->key << ' ';
			inorder_tree_walk(x->right.get());
		}
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
		Node* zp = z->parent;
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
			if (y->parent == z) {
				Node* pz = transplant(z, std::move(z->right));
				y->left = std::move(pz->left);
				y->left->parent = y;
				auto upz = std::unique_ptr<Node>(pz);
			}
			else {
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
		rebalance(zp);
	}

	void rebalance(Node * zp) { 
		if (!zp) {
			return;
		}
		else {
			zp->height = std::max(height(zp->left.get()), height(zp->right.get()));
			int bf = balance(zp);
			if (bf > 1 && balance(zp->left.get()) >= 0) {
				right_rotate(zp);
			}
			else if (bf > 1 && balance(zp->left.get()) < 0) {
				left_rotate(zp->left.get());
				right_rotate(zp);
			}
			else if (bf < -1 && balance(zp->right.get()) <= 0) {
				left_rotate(zp);
			}
			else if (bf < -1 && balance(zp->right.get()) > 0) {
				right_rotate(zp->right.get());
				left_rotate(zp);
			}
		}

	}

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

	void tree_insert(Node* p, Node* x, const T& k) {
		if (!x) {
			std::unique_ptr<Node> z = std::make_unique<Node>(k);
			z->parent = p;
			if (p && z->key < p->key) {
				p->left = std::move(z);

			}
			else if (p && z->key > p->key) {
				p->right = std::move(z);
			}
			else {	
				root = std::move(z);
				return;
			}
			p->height = std::max(height(p->left.get()), height(p->right.get()));
			int bf = balance(p);
			if (bf > 1 && k < p->left->key) {
				right_rotate(p);
			}
			else if (bf< -1 && k > p->right->key) {
				left_rotate(p);
			}
			else if (bf > 1 && k > p->left->key){
				left_rotate(p->left.get());
				right_rotate(p);
			}
			else if (bf < -1 && k < p->right->key) {
				right_rotate(p->right.get());
				left_rotate(p);
			}
		}
		else if (k < x->key) {
			tree_insert(x, x->left.get(), k);
		}
		else {
			tree_insert(x, x->right.get(), k);
		}
	}

public:

	Node* tree_search(const T& k) {
		return tree_search(root.get(), k);
	}

	void inorder_tree_walk() {
			if (root) {
				inorder_tree_walk(root.get());
			}
			else {
				std::cout << "\ntree empty\n";
			}
		}

	void tree_insert(const T& k) {
		tree_insert(nullptr, root.get(), k);
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
};

int main()
{
	AVLT<int> avl;
	std::vector<int> v(1001);
	std::iota(v.begin() + 1, v.end(), 1);

	std::shuffle(v.begin() + 1, v.end(), gen);
	for (auto i = 1; i < v.size(); ++i) {
		avl.tree_insert(v[i]);
	}

	avl.inorder_tree_walk();
	std::cout << '\n';
	std::cout << '\n';

	std::shuffle(v.begin() + 1, v.end(), gen);
	for (auto i = 1; i < v.size(); i++) {
		avl.tree_delete(v[i]);
	}

	std::cout << "delete complete \n";
	avl.inorder_tree_walk();
	std::cout << '\n';

	std::shuffle(v.begin() + 1, v.end(), gen);
	for (auto i = 1; i < v.size(); ++i) {
		avl.tree_insert(v[i]);
	}

	avl.inorder_tree_walk();
}
