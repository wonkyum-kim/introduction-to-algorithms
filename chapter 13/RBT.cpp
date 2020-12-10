#include <iostream>
#include <memory>
#include <utility>
#include <algorithm>
#include <random>
#include <vector>
#include <numeric>

std::mt19937 gen(std::random_device{}());

template<typename T>
class RBT {
private:
	enum class Color {
		Red, Black
	};

	struct Node {
		T key;
		Color color;
		Node* parent;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
		Node(const T& k) :
			key{ k }, color{ Color::Red }, parent{ nullptr }, left{ nullptr }, right{ nullptr } {}
	};

	std::unique_ptr<Node> root = nullptr;

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

	/*
	* Why do we use unique_ptr release() ?
	*
	* To get a pointer of a node that is going to be deleted or moved.
	* By doing so, we can access to the former node in spite of the replacement.
	* However, release() does not delete the object. we have to delete that one by one.
	* An easy way to delete the object is std::unique_ptr<Node>(pointer returned by release()).
	*/
	void left_rotate(std::unique_ptr<Node>&& x) {
		auto y = std::move(x->right);
		x->right = std::move(y->left);
		if (x->right) {
			x->right->parent = x.get();
		}
		y->parent = x->parent;
		auto xp = x->parent;
		Node* px = nullptr;	// pointer x
		if (!xp) {
			px = x.release();
			root = std::move(y);
			root->left = std::unique_ptr<Node>(px);
			root->left->parent = root.get();
		}
		else if (x == xp->left) {
			px = x.release();
			xp->left = std::move(y);
			xp->left->left = std::unique_ptr<Node>(px);
			xp->left->left->parent = xp->left.get();
		}
		else {
			px = x.release();
			xp->right = std::move(y);
			xp->right->left = std::unique_ptr<Node>(px);
			xp->right->left->parent = xp->right.get();
		}
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
		if (!xp) {
			px = x.release();
			root = std::move(y);
			root->right = std::unique_ptr<Node>(px);
			root->right->parent = root.get();
		}
		else if (x == xp->left) {
			px = x.release();
			xp->left = std::move(y);
			xp->left->right = std::unique_ptr<Node>(px);
			xp->left->right->parent = xp->left.get();
		}
		else {
			px = x.release();
			xp->right = std::move(y);
			xp->right->right = std::unique_ptr<Node>(px);
			xp->right->right->parent = xp->right.get();
		}
	}

	void rb_insert(std::unique_ptr<Node>&& z) {
		Node* y = nullptr;
		Node* x = root.get();
		while (x) {
			y = x;
			if (z->key < x->key) {
				x = x->left.get();
			}
			else {
				x = x->right.get();
			}
		}
		z->parent = y;
		if (!y) {
			root = std::move(z);
			rb_insert_fixup(root.get());
		}
		else if (z->key < y->key) {
			y->left = std::move(z);
			rb_insert_fixup(y->left.get());
		}
		else {
			y->right = std::move(z);
			rb_insert_fixup(y->right.get());
		}
	}

	void rb_insert_fixup(Node* z) {
		while (z->parent && z->parent->parent && z->parent->color == Color::Red) {
			if (z->parent == z->parent->parent->left.get()) {
				Node* y = z->parent->parent->right.get();
				if (y && y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->right.get()) {
						z = z->parent;
						left_rotate(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					right_rotate(z->parent->parent);
				}
			}
			else {
				Node* y = z->parent->parent->left.get();
				if (y && y->color == Color::Red) {
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left.get()) {
						z = z->parent;
						right_rotate(z);
					}
					z->parent->color = Color::Black;
					z->parent->parent->color = Color::Red;
					left_rotate(z->parent->parent);
				}
			}
		}
		root->color = Color::Black;
	}

	void inorder_tree_walk(Node* x) {
		if (x) {
			inorder_tree_walk(x->left.get());
			std::cout << x->key;
			if (x->color == Color::Black) {
				std::cout << "B ";
			}
			else {
				std::cout << "R ";
			}
			inorder_tree_walk(x->right.get());
		}
	}

	Node* tree_minimum(Node* x) {
		if (!x) {
			return x;
		}
		while (x->left) {
			x = x->left.get();
		}
		return x;
	}

	Node* rb_transplant(Node* u, std::unique_ptr<Node>&& v) {
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

	void rb_delete(Node* z) {
		if (!z) {
			return;
		}
		Color y_original_color = z->color;
		Node* x = nullptr;
		Node* xp = nullptr;
		if (!z->left) {
			x = z->right.get();
			xp = z->parent;
			auto pz = rb_transplant(z, std::move(z->right));
			auto upz = std::unique_ptr<Node>(pz);
		}
		else if (!z->right) {
			x = z->left.get();
			xp = z->parent;
			auto pz = rb_transplant(z, std::move(z->left));
			auto upz = std::unique_ptr<Node>(pz);
		}
		else {
			auto y = tree_minimum(z->right.get());
			y_original_color = y->color;
			x = y->right.get();
			if (y->parent == z) {
				if (x) {
					x->parent = y;
				}
				xp = y;
				auto pz = rb_transplant(z, std::move(z->right));
				y->left = std::move(pz->left);
				y->left->parent = y;
				y->color = pz->color;
				auto upz = std::unique_ptr<Node>(pz);
			}
			else {
				xp = y->parent;
				auto py = rb_transplant(y, std::move(y->right));
				py->right = std::move(z->right);
				py->right->parent = py;
				auto upy = std::unique_ptr<Node>(py);
				auto pz = rb_transplant(z, std::move(upy));
				py->left = std::move(pz->left);
				py->left->parent = py;
				py->color = pz->color;
				auto upz = std::unique_ptr<Node>(pz);
			}
		}
		if (y_original_color == Color::Black) {
			rb_delete_fixup(x, xp);
		}

	}

	void rb_delete_fixup(Node* x, Node* xp) {
		while (x != root.get() && (!x || x->color == Color::Black)) {
			if (x == xp->left.get()) {
				Node* w = xp->right.get();
				if (w && w->color == Color::Red) {
					w->color = Color::Black;
					xp->color = Color::Red;
					left_rotate(xp);
					w = xp->right.get();
				}
				if (w && (!w->left || w->left->color == Color::Black)
					&& (!w->right || w->right->color == Color::Black)) {
					w->color = Color::Red;
					x = xp;
					xp = xp->parent;
				}
				else if (w) {
					if (!w->right || w->right->color == Color::Black) {
						w->left->color = Color::Black;
						w->color = Color::Red;
						right_rotate(w);
						w = xp->right.get();
					}
					w->color = xp->color;
					xp->color = Color::Black;
					w->right->color = Color::Black;
					left_rotate(xp);
					x = root.get();
				}
				else {
					x = root.get();
				}
			}
			else {
				Node* w = xp->left.get();
				if (w && w->color == Color::Red) {
					w->color = Color::Black;
					xp->color = Color::Red;
					right_rotate(xp);
					w = xp->left.get();
				}
				if (w && (!w->left || w->left->color == Color::Black)
					&& (!w->right || w->right->color == Color::Black)) {
					w->color = Color::Red;
					x = xp;
					xp = xp->parent;
				}
				else if (w) {
					if (!w->left || w->left->color == Color::Black) {
						w->right->color = Color::Black;
						w->color = Color::Red;
						left_rotate(w);
						w = xp->left.get();
					}
					w->color = xp->color;
					xp->color = Color::Black;
					w->left->color = Color::Black;
					right_rotate(xp);
					x = root.get();
				}
				else {
					x = root.get();
				}
			}
		}
		if (x) {
			x->color = Color::Black;
		}
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

public:

	void rb_insert(const T& k) {
		auto z = std::make_unique<Node>(k);
		rb_insert(std::move(z));
	}

	void inorder_tree_walk() {
		if (root) {
			inorder_tree_walk(root.get());
		}
		else {
			std::cout << "\ntree empty\n";
		}
	}

	void rb_delete(const T& k) {
		auto z = search(root.get(), k);
		rb_delete(z);
	}
};

int main()
{
	RBT<int> rbt;
	std::vector<int> v(100);
	std::iota(v.begin(), v.end(), 1);

	std::shuffle(v.begin(), v.end(), gen);
	for (auto x : v) {
		rbt.rb_insert(x);
	}
	rbt.inorder_tree_walk();

	std::cout << '\n' << "delete complete.";

	std::shuffle(v.begin(), v.end(), gen);
	for (auto x : v) {
		rbt.rb_delete(x);
	}
	rbt.inorder_tree_walk();
	std::cout << '\n';

	std::shuffle(v.begin(), v.end(), gen);
	for (auto x : v) {
		rbt.rb_insert(x);
	}

	rbt.inorder_tree_walk();

	std::cout << '\n' << "delete complete.";

	std::shuffle(v.begin(), v.end(), gen);
	for (auto x : v) {
		rbt.rb_delete(x);
	}
	rbt.inorder_tree_walk();
	std::cout << '\n';
}
