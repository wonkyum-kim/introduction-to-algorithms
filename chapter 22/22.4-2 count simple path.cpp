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

	size_t count_simple_paths(size_t s, size_t t) {
		std::vector<size_t> path(n);
		return count_simple_paths(s, t, path);
	}

private:

	size_t count_simple_paths(size_t s, size_t t, std::vector<size_t>& path) {
		if (s == t) {
			return 1;
		}
		else if (path[s] != 0) {
			return path[s];
		}
		else {
			for (auto w : adj[s]) {
				path[s] += count_simple_paths(w, t, path);
			}
			return path[s];
		}
	}
};

int main()
{
	Graph g(6, Graph_Type::Directed);
	g.add_edge(0, 3);
	g.add_edge(0, 1);
	g.add_edge(1, 4);
	g.add_edge(1, 2);
	g.add_edge(2, 5);
	g.add_edge(4, 5);
	std::cout << g.count_simple_paths(0, 5);
}
