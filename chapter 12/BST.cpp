#include <iostream>
#include <utility>
#include <memory>

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
		tree_delete(z);
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
		// case 1 : z has one child
		// case 1-1 : z has a right child
		if (!z->left) {
			transplant(z, std::move(z->right));
		}
		// case 1-2 : z has a left child
		else if (!z->right) {
			transplant(z, std::move(z->left));
		}
		// case 2 : z has two children
		else {
			Node* y = tree_minimum(z->right.get());
			std::unique_ptr<Node> upy = nullptr;
			if (y->parent != z) {
				// disconnect a link between z->right's subtree and y's subtree
				upy = std::move(y->parent->left);
				// disconnect a link between y and y->right's subtree
				std::unique_ptr<Node> x = std::move(upy->right);
				// link z->right's subtree with x
				transplant(tree_minimum(z->right.get())->left.get(), std::move(x));
				// link y with z->right's subtree
				transplant(upy->right.get(), std::move(z->right));
			}
			else {
				upy = std::move(z->right);
			}
			std::unique_ptr<Node> upzl = std::move(z->left);
			upy->left = std::move(upzl);
			transplant(z, std::move(upy));
		}
	}

	//------------------------------------------------------

};

int main()
{
	BST<int> bst;
	bst.tree_insert(10);
	bst.tree_insert(8);
	bst.tree_insert(12);
	bst.tree_insert(7);
	bst.tree_insert(9);
	if (bst.tree_search(10)) {
		std::cout << "tree_search is okay" << '\n';
	}
	if (bst.iterative_tree_search(12)) {
		std::cout << "iterative_tree_search is okay" << '\n';
	}
	bst.inorder_tree_walk();
	bst.tree_delete(10);
	std::cout << '\n';
	bst.inorder_tree_walk();
	bst.tree_delete(12);
	std::cout << '\n';
	bst.inorder_tree_walk();
	bst.tree_delete(9);
	std::cout << '\n';
	bst.inorder_tree_walk();
	bst.tree_delete(7);
	std::cout << '\n';
	bst.inorder_tree_walk();

}