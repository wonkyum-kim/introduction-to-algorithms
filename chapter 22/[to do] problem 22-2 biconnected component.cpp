#include <iostream>
#include <vector>
#include <algorithm>

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
		size_t children = 0;
		int low = -1;
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

	void DFS() {
		size_t time = 0;
		for (auto i = 0; i < n; ++i) {
			if (info[i].color == Color::White) {
				DFS_visit(i, time);
			}
		}
	}

	void articulation_point() {
		DFS();
		update_low();
		std::vector<bool> visited(n, false);
		std::vector<bool> ap(n, false);
		ap_helper(0, visited, ap);
		for (auto i = 0; i < n; ++i) {
			if (ap[i]) {
				std::cout << i << ' ';
			}
		}
	}

	void update_low() {
		for (int i = 0; i < n; ++i) {
			// case 1 : root
			if (info[i].phi == -1) {
				info[i].low = info[i].d;
			}
			// case 2 : from leaf to all vertex without root
			else if (info[i].children == 0) {
				int curr = i;
				while (curr != -1) {
					for (auto neighbor : adj[curr]) {
						if (neighbor != info[curr].phi) {
							info[curr].low = std::min(info[curr].d, info[neighbor].d);
						}
					}
					curr = info[curr].phi;
				}
			}
			else {
				continue;
			}
		}
	}

	void check_low() {
		for (auto i = 0; i < n; ++i) {
			std::cout << info[i].low << ' ';
		}
	}



private:
	void DFS_visit(vertex u, size_t& time) {
		++time;
		info[u].d = time;
		info[u].color = Color::Gray;
		for (auto v : adj[u]) {
			if (info[v].color == Color::White) {
				info[v].phi = u;
				info[u].children++;
				DFS_visit(v, time);
			}
		}
		info[u].color = Color::Black;
		++time;
		info[u].f = time;
	}

	void ap_helper(size_t parent, std::vector<bool>& visited, std::vector<bool>& ap) {
		visited[parent] = true;
		for (auto child : adj[parent]) {
			if (info[child].low >= info[parent].d) {
				ap[parent] = true;
			}
			ap_helper(child, visited, ap);
		}
	}

};

int main()
{
	Graph g(6, Graph_Type::Undirected);
	g.add_edge(0, 1);
	g.add_edge(0, 3);
	g.add_edge(2, 3);
	g.add_edge(1, 2);
	g.add_edge(4, 2);
	g.add_edge(4, 5);
	g.add_edge(5, 2);
	g.articulation_point();
}
