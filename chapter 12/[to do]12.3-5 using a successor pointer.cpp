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
		Node* y = tree_parent(x);
		while (y && x == y->left.get()) {
			x = y;
			y = tree_parent(y);
		}
		return y;
	}

	Node* tree_successor(Node* x) {
		if (x->left) {
			return tree_minimum(x->right.get());
		}
		Node* y = tree_parent(x);
		while (y && x == y->right.get()) {
			x = y;
			y = tree_parent(y);
		}
		return y;
	}

	void transplant(Node* u, std::unique_ptr<Node>&& v) {
		Node* up = tree_parent(u);
		if (!up) {
			root = std::move(v);
		}
		else if (u == up->left.get()) {
			up->left = std::move(v);
		}
		else {
			up->right = std::move(v);
		}
	}

	// working...
	void tree_delete(Node* z) {
		Node* pred = tree_predecessor(z);
		pred->succ = tree_successor(z);
		if (!z->left) {
			transplant(z, std::move(z->right));
		}
		else if (!z->right) {
			transplant(z, std::move(z->left));
		}
		else {
			Node* y = tree_minimum(z->right.get());
			Node* yp = tree_parent(y);
			std::unique_ptr<Node> upy = nullptr;
			if (yp != z) {
				upy = std::move(yp->left);
				std::unique_ptr<Node> x = std::move(upy->right);
				transplant(tree_minimum(z->right.get())->left.get(), std::move(x));
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
