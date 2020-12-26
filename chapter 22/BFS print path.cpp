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

	using vertex_info = std::tuple<Color, size_t, size_t>;	// u.color, u.d, u.phi

	std::vector<vertex_info> BFS(size_t s) {
		std::vector<vertex_info> info(n, { Color::White,std::numeric_limits<size_t>::max(), -1 });
		info[s] = { Color::Gray, 0, -1 };
		std::queue<size_t> q;
		q.push(s);
		while (!q.empty()) {
			size_t u = q.front();
			q.pop();
			for (auto v : adj[u]) {
				if (std::get<0>(info[v]) == Color::White) {
					info[v] = { Color::Gray, std::get<1>(info[u]) + 1, u };
					q.push(v);
				}
			}
			// std::get<0>(info[u]) = Color::Black;
		}
		return info;
	}

	void print_path(size_t s, size_t v, const std::vector<vertex_info>& info) {
		if (v == s) {
			std::cout << s << ' ';
		}
		else if (std::get<2>(info[v]) == -1) {
			std::cout << "no path from " << s << " to " << v << " exists";
			return;
		}
		else {
			print_path(s, std::get<2>(info[v]), info);
			std::cout << v << ' ';
		}
	}
};
