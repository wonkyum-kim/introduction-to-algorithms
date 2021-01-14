#include <iostream> 
#include <queue> 
#include <vector>
#include <utility>
#include <memory>

class Huffman {
private:
	struct Node {
		char data;
		int freq;
		std::shared_ptr<Node> left;
		std::shared_ptr<Node> right;
		Node(const char& data, const int& freq) : data{data},freq{freq},left{nullptr},right{nullptr}{}
	};
public:

	std::shared_ptr<Node> root = nullptr;

	std::shared_ptr<Node> encoding(std::vector<std::pair<char, int>>& x) {
		int n = x.size();
		auto comp = [](auto& a, auto& b)->bool {
			return a.freq > b.freq;
		};
		std::priority_queue<Node, std::vector<Node>, decltype(comp)> pq(comp);
		for (auto i = 0; i < n; ++i) {
			Node temp(x[i].first, x[i].second);
			pq.push(temp);
		}
		for (auto i = 0; i < n - 1; ++i) {
			auto x = pq.top();
			pq.pop();
			auto y = pq.top();
			pq.pop();
			Node z('#', x.freq + y.freq);
			z.left = std::make_shared<Node>(x);
			z.right = std::make_shared<Node>(y);
			pq.push(z);
		}
		auto r = pq.top();
		root = std::make_shared<Node>(r);
		return root;
	}

	void print_codes(std::shared_ptr<Node>& root) {
		std::vector<int> v(100);
		int top = 0;
		print_codes(root.get(), v, top);
	}

private:

	void print_codes(Node* root, std::vector<int>& v, int top) {
		if (root->left) {
			v[top] = 0;
			print_codes(root->left.get(), v, top + 1);
		}

		if (root->right) {
			v[top] = 1;
			print_codes(root->right.get(), v, top + 1);
		}

		if (!root->left && !root->right) {
			std::cout << root->data << ' ';
			for (auto i = 0; i < top; ++i) {
				std::cout << v[i];
			}
			std::cout << '\n';
		}
	}
};

int main()
{
	std::vector<std::pair<char, int>> nodes;
	nodes.push_back({ 'a',45 });
	nodes.push_back({ 'b',13 });
	nodes.push_back({ 'c',12});
	nodes.push_back({ 'd',16 });
	nodes.push_back({ 'e',9 });
	nodes.push_back({ 'f',5 });
	Huffman h;
	auto root = h.encoding(nodes);
	h.print_codes(root);
}
