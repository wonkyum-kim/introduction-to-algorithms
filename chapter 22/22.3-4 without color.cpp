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

	using vertex_info = std::tuple<bool, size_t, size_t, int>;	// u.visit, u.d, u.f, u.phi

	void DFS() {
		std::vector<vertex_info> info(n, { false, 0, 0, -1 });
		size_t time = 0;
		for (auto i = 0; i < n; ++i) {
			if (!std::get<0>(info[i])) {
				DFS_visit(i, time, info);
			}
		}
	}

private:
	void DFS_visit(size_t u, size_t& time, std::vector<vertex_info>& info) {
		++time;
		std::get<1>(info[u]) = time;
		std::get<0>(info[u]) = true;
		for (auto v : adj[u]) {
			if (!std::get<0>(info[v])) {
				std::get<3>(info[v]) = u;
				DFS_visit(v, time, info);
			}
		}
		++time;
		std::get<2>(info[u]) = time;
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
	g.DFS();	
}
