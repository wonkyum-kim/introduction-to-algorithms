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

	void BFS(size_t start) {
		std::queue<size_t> q;
		std::vector<bool> visited(n, false);
		std::vector<size_t> distance(n);
		visited[start] = true;
		q.push(start);
		while (!q.empty()) {
			size_t s = q.front();
			std::cout << s << ' ';
			q.pop();
			for (auto u : adj[s]) {
				if (visited[u]) {
					continue;
				}
				visited[u] = true;
				distance[u] = distance[s] + 1;
				q.push(u);
			}
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
