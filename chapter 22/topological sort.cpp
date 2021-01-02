#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <cassert>

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

	struct vertex_info {
		Color color = Color::White;
		size_t d = 0;
		size_t f = 0;
		int phi = -1;
	};

	vertex n;
	Graph_Type g_type;
	std::vector<std::vector<vertex>> adj;
	std::vector<vertex_info> info;
	std::list<size_t> sorted;

public:
	Graph(vertex n, Graph_Type g_type) : n{n},g_type{g_type},adj(n), info(n){}

	void add_edge(vertex u, vertex v) {
		adj[u].push_back(v);
		if (g_type == Graph_Type::Undirected) {
			adj[v].push_back(u);
		}
	}

	void sort_adj() {
		for (auto i = 0; i < n; ++i) {
			std::sort(adj[i].begin(), adj[i].end());
		}
	}

	void DFS() {
		size_t time = 0;
		for (auto i = 0; i < n; ++i) {
			if (info[i].color == Color::White) {
				DFS_visit(i, time);
			}
		}
	}

	std::list<vertex> topological_sort() {
		assert(g_type == Graph_Type::Directed);
		DFS();
		return sorted;
	}

private:
	void DFS_visit(vertex u, size_t& time) {
		++time;
		info[u].d = time;
		info[u].color = Color::Gray;
		for (auto v : adj[u]) {
			if (info[v].color == Color::White) {
				info[v].phi = u;
				DFS_visit(v, time);
			}
		}
		info[u].color = Color::Black;
		++time;
		info[u].f = time;
		sorted.push_front(u);
	}
};

int main() 
{
	Graph g(6, Graph_Type::Directed);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(2, 5);
	g.add_edge(3, 0);
	g.add_edge(3, 4);
	g.add_edge(4, 1);
	g.add_edge(4, 2);
	g.sort_adj();
	auto topological_sort = g.topological_sort();
	while (!topological_sort.empty()) {
		size_t node = topological_sort.front();
		topological_sort.pop_front();
		std::cout << node << ' ';
	}
}
