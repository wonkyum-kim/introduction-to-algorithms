#include <iostream>
#include <utility>
#include <memory>
#include <algorithm>

enum class Color {
	Red, Black
};

template<typename T>
struct Node {
	T key;
	Color color;
	Node* parent;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
	Node(const T& key) : key{ key }, color{ Color::Red }, parent{ nullptr }, left{ nullptr }, right{ nullptr } {}
};

template<typename T>
class Red_Black_Tree {
public:
	std::unique_ptr<Node<T>> root;
	void insert(const T& key) {
		auto z = std::make_unique<Node<T>>(key);
		insert(z);
	}
private:
	void left_rotate(std::unique_ptr<Node<T>>&& x) {
		auto y = std::move(x->right);	// set y;
		// turn y's left subtree into x's right subtree
		x->right = std::move(y->left);
		if (x->right != nullptr) {
			x->right->parent = x.get();
		}
		y->parent = x->parent;	// link x's parent to y
		if (x->parent == nullptr) {	// x is a root node
			root = std::move(y);
			root->left = std::move(x);
			root->left->parent = root.get();
		}
		else if (x == x->parent->left) {	// x is a left child
			// now x->parent is deprived of the ownership for x.
			Node<T>* x_p = x->parent;
			Node<T>* x_x = x.release();	// x is no loger owned by unique_ptr
			x_p->left = std::move(y);
			x_p->left->parent = x_p;
			x_p->left->left = std::unique_ptr<Node<T>>(x_x);
			x_p->left->left->parent = x_p->left.get();
		}
		else {	// x is a right child
			// now x->parent is deprived of the ownership for x.
			Node<T>* x_p = x->parent;
			Node<T>* x_x = x.release();	// x is no loger owned by unique_ptr
			x_p->right = std::move(y);
			x_p->right->parent = x_p;
			x_p->right->right = std::unique_ptr<Node<T>>(x_x);
			x_p->right->right->parent = x_p->right.get();
		}
	}

	void right_rotate(std::unique_ptr<Node<T>>&& x) {
		auto y = std::move(x->left);	// set y;
		// turn y's left subtree into x's left subtree
		x->left = std::move(y->right);
		if (x->left != nullptr) {
			x->left->parent = x.get();
		}
		y->parent = x->parent;	// link x's parent to y
		if (x->parent == nullptr) {	// x is a root node
			root = std::move(y);
			root->right = std::move(x);
			root->right->parent = root.get();
		}
		else if (x == x->parent->right) {	// x is a right child
			// now x->parent is deprived of the ownership for x.
			Node<T>* x_p = x->parent;
			Node<T>* x_x = x.release();	// x is no loger owned by unique_ptr
			x_p->right = std::move(y);
			x_p->right->parent = x_p;
			x_p->right->right = std::unique_ptr<Node<T>>(x_x);
			x_p->right->right->parent = x_p->right.get();
		}
		else {	// x is a left child
			// now x->parent is deprived of the ownership for x.
			Node<T>* x_p = x->parent;
			Node<T>* x_x = x.release();	// x is no loger owned by unique_ptr
			x_p->left = std::move(y);
			x_p->left->parent = x_p;
			x_p->left->left = std::unique_ptr<Node<T>>(x_x);
			x_p->left->left->parent = x_p->left.get();
		}
	}
	
	// convert a pointer to a unique_ptr
	void left_rotate(Node<T>* x) {
		auto x_p = x->parent;
		if (!x_p) {
			left_rotate(std::move(root));
		}
		else if (x == x_p->left.get()) {
			left_rotate(std::move(x_p->left));
		}
		else {
			left_rotate(std::move(x_p->right));
		}
	}

	// convert a pointer to a unique_ptr
	void right_rotate(Node<T>* x) {
		auto x_p = x->parent;
		if (!x_p) {
			right_rotate(std::move(root));
		}
		else if (x == x_p->left.get()) {
			right_rotate(std::move(x_p->left));
		}
		else {
			right_rotate(std::move(x_p->right));
		}
	}
	
	void insert(std::unique_ptr<Node<T>>& z) {	
		Node<T>* y = nullptr;
		Node<T>* x = root.get();
		while (x != nullptr) {
			y = x;
			if (z->key < x->key) {
				x = x->left.get();
			}
			else {
				x = x->right.get();
			}
		}
		z->parent = y;
		if (y == nullptr) {
			root = std::move(z);
			insert_fixup(root.get());
		}
		else if (z->key < y->key) {
			y->left = std::move(z);
			insert_fixup(y->left.get());
		}
		else {
			y->right = std::move(z);
			insert_fixup(y->right.get());
		}
	}

	void insert_fixup(Node<T>* z) {
		while (z->parent && z->parent->color == Color::Red) {
			if (z->parent == z->parent->parent->left.get()) {
				Node<T>* y = z->parent->parent->right.get();	// y is z's uncle.
				if (y && y->color == Color::Red) {	// case 1
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->right.get()) {	// case 2
						z = z->parent;
						left_rotate(z);
					}
					z->parent->color = Color::Black;	// case 3
					z->parent->parent->color = Color::Red;
					right_rotate(z->parent->parent);
				}
			}
			else {
				Node<T>* y = z->parent->parent->left.get();	// y is z's uncle.
				if (y && y->color == Color::Red) {	// case 1
					z->parent->color = Color::Black;
					y->color = Color::Black;
					z->parent->parent->color = Color::Red;
					z = z->parent->parent;
				}
				else {
					if (z == z->parent->left.get()) {	// case 2
						z = z->parent;
						left_rotate(z);
					}
					z->parent->color = Color::Black;	// case 3
					z->parent->parent->color = Color::Red;
					right_rotate(z->parent->parent);
				}
			}
		}
		root->color = Color::Black;
	}
};

int main()
{
	Red_Black_Tree<int> rbtree;
	rbtree.insert(41);
	rbtree.insert(38);
	rbtree.insert(31);
	rbtree.insert(12);
	rbtree.insert(19);
	rbtree.insert(8);
}
