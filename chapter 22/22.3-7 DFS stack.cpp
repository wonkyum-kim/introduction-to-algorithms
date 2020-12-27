#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <numeric>
#include <stack>
#include <utility>

enum class Graph_Type {
	Directed, Undirected
};

class Graph {
private:
	using vertex = size_t;
	using edge_weight = double;
	using edge = std::tuple<vertex, vertex, edge_weight>;

	enum class Color {
		White, Gray, Black
	};

	vertex n;
	Graph_Type type;
	std::vector<std::vector<size_t>> adj;

public:
	Graph(size_t n, Graph_Type dir) : n{ n }, type{ dir }, adj(n) {}

	void add_edge(size_t u, size_t v) {
		adj[u].push_back(v);
		if (type == Graph_Type::Undirected) {
			adj[v].push_back(u);
		}
	}

	void sort_adj() {
		for (auto i = 0; i < n; ++i) {
			std::sort(adj[i].begin(), adj[i].end());
		}
	}

	using vertex_info = std::tuple<Color, size_t, size_t, size_t>;	// u.color, u.d, u.f, u.phi

	void DFS() {
		std::vector<vertex_info> info(n, { Color::White,0,0,-1 });
		size_t time = 0;
		std::stack<size_t> s;
		for (auto u = 0; u < n; ++u) {
			if (std::get<0>(info[u]) == Color::White) {
				s.push(u);
				while (!s.empty()) {
					size_t v = s.top();
					s.pop();
					if (std::get<0>(info[v]) != Color::Black) {
						std::cout << v + 1 << ' ';
					}
					time++;
					std::get<1>(info[v]) = time;
					std::get<0>(info[v]) = Color::Black;
					std::stack<size_t> temp;
					for (auto w : adj[v]) {
						if (std::get<0>(info[w]) == Color::White || std::get<0>(info[w]) == Color::Gray ) {
							std::get<0>(info[w]) = Color::Gray;
							std::get<3>(info[w]) = v;
							temp.push(w);
						}
					}
					while (!temp.empty()) {
						auto neighbor = temp.top();
						temp.pop();
						s.push(neighbor);
					}
					time++;
					std::get<2>(info[v]) = time;
				}
			}
		}
	}
};

int main()
{
	Graph g(6, Graph_Type::Undirected);
	g.add_edge(0, 1);
	g.add_edge(0, 3);
	g.add_edge(1, 2);
	g.add_edge(1, 4);
	g.add_edge(2, 5);
	g.add_edge(4, 5);
	g.DFS();	
}
