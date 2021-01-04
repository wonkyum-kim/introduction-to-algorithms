#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>

enum class Graph_Type {
	Directed, Undirected
};

class Graph {
private:
	using vertex = size_t;
	using edge_weight = double;

	struct vertex_info {
		size_t in = 0;
		size_t out = 0;
	};

	vertex n;
	Graph_Type g_type;
	std::vector<std::vector<vertex>> adj;
	std::vector<vertex_info> info;

public:
	Graph(vertex n, Graph_Type g_type) : n{ n }, g_type{ g_type }, adj(n), info(n) {}

	void add_edge(vertex u, vertex v) {
		adj[u].push_back(v);
		info[u].out++;
		info[v].in++;
		if (g_type == Graph_Type::Undirected) {
			adj[v].push_back(u);
		}
	}

	void get_outdegree() {
		assert(g_type == Graph_Type::Directed);
		for (auto i = 0; i < n; ++i) {
			std::cout << info[i].out << ' ';
		}
		std::cout << '\n';
	}

	void get_indegree() {
		assert(g_type == Graph_Type::Directed);
		for (auto i = 0; i < n; ++i) {
			std::cout << info[i].in << ' ';
		}
		std::cout << '\n';
	}

	void get_degree() {
		for (auto i = 0; i < n; ++i) {
			std::cout << info[i].in + info[i].out << ' ';
		}
		std::cout << '\n';
	}
};

int main()
{
	Graph g(4, Graph_Type::Directed);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(3, 1);
	g.get_indegree();
	g.get_outdegree();
	g.get_degree();
}
