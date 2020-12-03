#include<iostream>
#include<memory>
#include<utility>
#include<stack>

template<typename T>
class BT {
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

	std::unique_ptr<Node> root = nullptr;

public:
	Node* make_root(const T& k) {
		root = std::make_unique<Node>(k);
		return root.get();
	}

	Node* make_left(Node* x, const T& k) {
		auto child = std::make_unique<Node>(k);
		x->left = std::move(child);
		x->left->parent = x;
		return x->left.get();
	}

	Node* make_right(Node* x, const T& k) {
		auto child = std::make_unique<Node>(k);
		x->right = std::move(child);
		x->right->parent = x;
		return x->right.get();
	}

	Node* search(const T& k) {
		if (!root) {
			return nullptr;
		}
		else {
			return search(root.get(), k);
		}
	}

	void inorder_tree_walk() {
		inorder_tree_walk(root.get());
	}

private:
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

	Node* search(Node* x, const T& k) {
		std::stack<Node*> s;
		s.push(x);
		while (!s.empty()) {
			auto x = s.top();
			while (x) {
				s.push(x->left.get());
				x = s.top();
			}
			s.pop();
			if (!s.empty()) {
				x = s.top();
				s.pop();
				if (x->key == k) {
					return x;
				}
				s.push(x->right.get());
			}
		}
		return nullptr;
	}
};

int main()
{
	int n = 0;
	std::cin >> n;
	BT<int> bt;

	for (auto i = 0; i < n; ++i) {
		int first;
		int second;
		int third;
		std::cin >> first >> second >> third;

		auto node = bt.search(first);
		if (!bt.search(first)) {
			node = bt.make_root(first);
		}
		if (second != -1) {
			auto temp = bt.make_left(node, second);
		}
		if (third != -1) {
			auto temp = bt.make_right(node, third);
		}
	}

	bt.inorder_tree_walk();
}
