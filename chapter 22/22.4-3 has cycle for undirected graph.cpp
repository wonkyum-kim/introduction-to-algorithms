#include <iostream>
#include <vector>
#include <algorithm>
#include <ranges>

enum class Graph_Type {
	Directed, Undirected
};

class Graph {
private:
	using vertex = size_t;

	enum class Color {
		White, Gray, Black
	};

	struct vertex_info {
		Color color = Color::White;
		int parent = -1;
	};

	vertex n;
	Graph_Type g_type;
	std::vector<std::vector<vertex>> adj;
	std::vector<vertex_info> info;

public:
	Graph(vertex n, Graph_Type g_type) : n{ n }, g_type{ g_type }, adj(n), info(n){}

	void add_edge(vertex u, vertex v) {
		adj[u].push_back(v);
		if (g_type == Graph_Type::Undirected) {
			adj[v].push_back(u);
		}
	}

	bool has_cycle() {
		for (auto i = 0; i < n; ++i) {
			if (info[i].color == Color::White) {
				if (DFS_visit(i)) {
					return true;
				}
			}
		}
		return false;
	}

private:
	bool DFS_visit(vertex u) {
		info[u].color = Color::Gray;
		for (auto v : adj[u]) {
			if (info[v].color == Color::White) {
				info[v].parent = u;
				if (DFS_visit(v)) {
					return true;
				}
			}
			// If an adjacent is not visited and not parent of current vertex,
			// then there is a graph.
			else if (v != info[u].parent) {
				return true;
			}
		}
		info[u].color = Color::Black;
		return false;
	}
};

int main()
{
	Graph g(3, Graph_Type::Undirected);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(2, 0);
	if (g.has_cycle()) {
		std::cout << "Cycle detected\n";
	}
}
