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

	bool is_singly_connected() {
		bool flag = true;
		for (auto i = 0; i < n; ++i) {
			DFS_visit(i, flag);
			if (!flag) {
				return false;
			}
			for (auto j = 0; j < n; ++j) {
				info[j].color = Color::White;
			}
		}
		return true;
	}

private:
	void DFS_visit(vertex u, bool& flag) {
		info[u].color = Color::Gray;
		for (auto v : adj[u]) {
			if (info[v].color == Color::White) {
				DFS_visit(v,flag);
			}
			else {
				flag = false;
				return;
			}
		}
		info[u].color = Color::Black;
	}
};

int main()
{
	Graph g(5, Graph_Type::Directed);
	g.add_edge(0, 1);
	g.add_edge(0, 2);
	g.add_edge(0, 3);
	g.add_edge(1, 4);
	g.add_edge(2, 4);
	if (g.is_singly_connected()) {
		std::cout << "this grpah is singly connected graph\n";
	}
	else {
		std::cout << "this graph is not singly connected\n";
	}
}
