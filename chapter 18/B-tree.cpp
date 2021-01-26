#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <memory>
#include <ranges>
#include <cassert>
#include <numeric>
#include <random>

namespace sr = std::ranges;

// B-TREE-IMPLEMENTATION
template<typename T, size_t t>
class BTree {
private:

	// MINIMUM-DEGREE
	static_assert(t >= 2);

	// B-TREE-NODE
	struct Node {
		size_t n = 0;
		bool leaf = true;
		std::vector<T> key;
		std::vector<std::unique_ptr<Node>> c;
		Node() {
			key.resize(2 * t - 1);
			c.resize(2 * t);
		}
	};

	// B-TREE-ROOT
	std::unique_ptr<Node> root = nullptr;

	// B-TREE-SEARCH
	std::pair<Node*, size_t> search(Node* x, const T& k) {
		// First call is search(root.get(), k)
		auto lower = std::lower_bound(x->key.begin(), x->key.begin() + x->n, k);
		auto i = std::distance(x->key.begin(), lower);
		if (i < x->n && k == x->key[i]) {
			return { x,i };
		}
		else if (x->leaf) {
			return { nullptr,0 };
		}
		else {
			return search(x->c[i].get(), k);
		}
	}

	// B-TREE-SPLIT-CHILD
	void split_child(Node* x, size_t i) {

		assert(x && !x->leaf);
		Node* y = x->c[i].get();
		assert(y && y->n == 2 * t - 1);
		auto z = std::make_unique<Node>();
		z->leaf = y->leaf;
		y->n = t;
		z->n = t - 1;

		// Move y's key to z
		sr::move(sr::drop_view{ y->key,t }, z->key.begin());

		// Move y's child to z
		if (!y->leaf) {
			sr::move(sr::drop_view{ y->c,t }, z->c.begin());
		}

		y->n--;
		assert(y->n == t - 1);

		// To insert a new child, shift right by 1 from i + 1;
		std::shift_right(x->c.begin() + i + 1, x->c.end(), 1);

		// Insert z to x
		x->c[i + 1] = std::move(z);

		// To insert a new key, shift right by 1 from i
		std::shift_right(x->key.begin() + i, x->key.end(), 1);

		// Insert y's last key to x
		x->key[i] = y->key[t - 1];

		// Increase x->n
		x->n++;
	}

	// B-TREE-INSERT-NONFULL
	void insert_nonfull(Node* x, const T& k) {
		assert(x->n != 2 * t - 1);
		// Find 0 to n - 1.
		auto upper = std::upper_bound(x->key.begin(), x->key.begin() + x->n, k);
		// This result means x->key[i] > k.
		auto i = std::distance(x->key.begin(), upper);
		if (x->leaf) {
			x->n++;
			std::shift_right(x->key.begin() + i, x->key.end(), 1);
			x->key[i] = k;
		}
		else {
			if (x->c[i]->n == 2 * t - 1) {
				split_child(x, i);
				if (k > x->key[i]) {
					++i;
				}
			}
			insert_nonfull(x->c[i].get(), k);
		}
	}

	// B-TREE-TRAVERSE
	void traverse(Node* x) {
		auto i = 0;
		while (i != x->n) {
			if (!x->leaf) {
				traverse(x->c[i].get());
			}
			std::cout << ' ' << x->key[i];
			++i;
		}
		if (!x->leaf) {
			traverse(x->c[i].get());
		}
	}

	// B-TREE-DELETE
	void remove(Node* x, const T& k) {
		// Find i (x->key[i] >= k) 
		// ==> x has x->n keys, so range to binary search is [0,x->n).
		auto lower = sr::lower_bound(x->key.begin(), x->key.begin() + x->n, k);
		size_t i = std::distance(x->key.begin(), lower);

		// Case 1 : The key k is present in this node.
		if (i < x->n && x->key[i] == k) {
			// Case 1 - 1 : Remove from leaf
			if (x->leaf) {
				std::shift_left(x->key.begin() + i, x->key.end(), 1);
				x->n--;
			}
			// Case 1 - 2 : Remove from non leaf
			else {
				Node* y = x->c[i].get();
				Node* z = x->c[i + 1].get();
				if (y && y->n >= t) {
					T pred_key = get_pred_key(x, i);
					// Change k to pred_key.
					x->key[i] = pred_key;
					remove(y, pred_key);
				}
				else if (z && z->n >= t) {
					assert(y && y->n < t);
					T succ_key = get_succ_key(x, i);
					// Change k to succ_key
					x->key[i] = succ_key;
					remove(z, succ_key);
				}
				else {
					assert(y && z && y->n == t - 1 && z->n == t - 1);
					merge(x, i);
					Node* next = x->c[i].get();
					if (x == root.get() && x->n == 0) {
						root = std::move(x->c[i]);
					}
					remove(next, k);
				}
			}
		}
		// Case 2 : The key k is not present in this node.
		else {
			assert(!x->leaf, "THE KEY DOES NOT EXIST\n");

			bool flag = i == x->n ? true : false;
			// Find next node.
			Node* next = x->c[i].get();
			if (next->n == t - 1) {
				fill(x, i);
			}
			if (flag && i > x->n) {
				remove(x->c[i - 1].get(), k);
			}
			else {
				remove(x->c[i].get(), k);
			}
		}
	}

	// GET-PREDECESSOR-KEY
	T get_pred_key(Node* x, size_t i) {
		Node* curr = x->c[i].get();
		while (!curr->leaf) {
			curr = curr->c[curr->n].get();
		}
		assert(curr);
		return curr->key[curr->n - 1];
	}

	// GET-SUCCESSOR-KEY
	T get_succ_key(Node* x, size_t i) {
		Node* curr = x->c[i + 1].get();
		while (!curr->leaf) {
			curr = curr->c[0].get();
		}
		assert(curr);
		return curr->key[0];
	}

	// MERGE
	void merge(Node* x, size_t i) {
		auto y = x->c[i].get();
		auto z = x->c[i + 1].get();

		// Add k to y.
		assert(y->n == t - 1);
		y->key[t - 1] = x->key[i];
		y->n++;
		x->n--;
		assert(y->n == t);

		// Add z to y
		sr::move(sr::views::all(z->key) | sr::views::take(z->n), y->key.begin() + t);
		if (!y->leaf) {
			sr::move(sr::views::all(z->c) | sr::views::take(z->n + 1), y->c.begin() + t);
		}
		y->n += z->n;
		assert(y->n == 2 * t - 1);

		// Delete x->key[i]
		std::shift_left(x->key.begin() + i, x->key.end(), 1);

		// Delete z
		std::shift_left(x->c.begin() + i + 1, x->c.end(), 1);
	}

	// FILL
	void fill(Node* x, size_t i) {
		if (i != 0 && x->c[i - 1]->n >= t) {
			borrow_from_prev(x, i);
		}
		else if (i != x->n && x->c[i + 1]->n >= t) {
			borrow_from_next(x, i);
		}
		else {
			if (i != x->n) {
				merge(x,i);
			}
			else {
				merge(x,i - 1);
			}
		}
	}

	// BORROW-FROM-PREV
	void borrow_from_prev(Node* x, size_t i) {
		Node* y = x->c[i].get();		// child
		Node* z = x->c[i - 1].get();	// left sibling

		// Shift right all keys in y by 1.
		std::shift_right(y->key.begin(), y->key.end(), 1);

		// Shift right all child pointers in y by 1.
		if (!y->leaf) {
			std::shift_right(y->c.begin(), y->c.end(), 1);
		}

		// x->key[i - 1] is inserted into y->key[0]
		y->key[0] = x->key[i - 1];

		// Moving z's last child as y's first child
		if (!y->leaf) {
			y->c[0] = std::move(z->c[z->n]);
		}

		// Moving z's last key to x->key[i-1]
		x->key[i - 1] = z->key[z->n - 1];

		y->n++;
		z->n--;
	}

	// BORROW-FROM-NEXT
	void borrow_from_next(Node* x, size_t i) {
		Node* y = x->c[i].get();		// child
		Node* z = x->c[i + 1].get();	// right sibling

		y->key[y->n] = x->key[i];

		if (!y->leaf) {
			y->c[y->n + 1] = std::move(z->c[0]);
		}

		x->key[i] = z->key[0];

		std::shift_left(z->key.begin(), z->key.end(), 1);
		if (!z->leaf) {
			std::shift_left(z->c.begin(), z->c.end(),1);
		}

		y->n++;
		z->n--;
	}

public:
	// B-TREE-SEARCH
	std::pair<Node*, size_t> search(const T& k) {
		if (!root) {
			std::cout << "The tree is empty...\n";
			return { nullptr,0 };
		}
		return search(root.get(), k);
	}

	// B-TREE-INSERT
	void insert(const T& k) {
		if (!root) {
			root = std::make_unique<Node>();
			root->n = 1;
			root->key[0] = k;
		}
		else {
			if (root->n == 2 * t - 1) {
				// Make new empty root.
				auto new_root = std::make_unique<Node>();
				new_root->leaf = false;
				// new_root is a parent of old root.
				new_root->c[0] = std::move(root);
				root = std::move(new_root);
				split_child(root.get(), 0);
			}
			insert_nonfull(root.get(), k);
		}
	}

	// B-TREE-TRAVERSE
	void traverse() {
		traverse(root.get());
	}

	// B-TREE-DELETE
	void remove(const T& k) {
		assert(root, "B-TREE-EMPTY\n");
		remove(root.get(), k);
		// If the root node has 0 keys, make its first child as the new root.
		if (root->n == 0) {
			// root has not a child.
			if (root->leaf) {
				root = nullptr;
			}
			else {
				auto temp = std::move(root);
				root = std::move(temp->c[0]);
			}
		}
	}

	// B-TREE-IS-EMPTY
	bool is_empty() {
		return root == nullptr;
	}
};

int main()
{
	std::mt19937 gen(std::random_device{}());
	BTree<int, 3> btree;
	std::vector<int> v(100);
	std::iota(v.begin(), v.end(), 1);
	std::shuffle(v.begin(), v.end(), gen);

	std::cout << "Insert numbers randomly...\n";
	for (auto x : v) {
		btree.insert(x);
		std::cout << x << ' ';
	}

	std::cout << "\n\nPrint keys in B-Tree...\n";
	btree.traverse();

	std::shuffle(v.begin(), v.end(), gen);

	std::cout << "\n\nDelete keys randomly...\n";
	for (auto x : v) {
		btree.remove(x);
		std::cout << x << ' ';
	}

	if (btree.is_empty()) {
		std::cout << "\n\nDelete complete\n";
	}
}
