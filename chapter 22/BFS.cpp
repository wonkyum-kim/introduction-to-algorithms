#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <numeric>
#include <queue>
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

	void BFS(size_t s) {
		// u.color, u.d, u.phi
		using vertex_u = std::tuple<Color, size_t, size_t>;
		std::vector<vertex_u> info(n, { Color::White,std::numeric_limits<size_t>::max(), -1 });
		info[s] = { Color::Gray, 0, -1 };
		std::queue<size_t> q;
		q.push(s);
		while (!q.empty()) {
			size_t u = q.front();
			std::cout << u << ' ';
			q.pop();
			for (auto v : adj[u]) {
				if (std::get<0>(info[v]) == Color::White) {
					info[v] = { Color::Gray, std::get<1>(info[v]) + 1, u };
					q.push(v);
				}
			}
			std::get<0>(info[u]) = Color::Black;
		}
	}

};

int main()
{
	Graph g(6, Graph_Type::Undirected);
	g.add_edge(0, 3);
	g.add_edge(0, 1);
	g.add_edge(1, 4);
	g.add_edge(1, 2);
	g.add_edge(2, 5);
	g.add_edge(4, 5);
	g.BFS(0);
}
