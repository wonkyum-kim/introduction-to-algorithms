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
		size_t scc;
	};

	vertex n;
	Graph_Type g_type;
	std::vector<std::vector<vertex>> adj;
	std::vector<vertex_info> info;
	std::list<size_t> sorted;
	std::vector<std::vector<vertex>> SCC;

public:
	Graph(vertex n, Graph_Type g_type) : n{n}, g_type{g_type}, adj(n), info(n){}

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

	void strongly_connected_components() {
		DFS();
		Graph transposed(n, Graph_Type::Directed);
		for (auto i = 0; i < n; ++i) {
			for (const auto& neighbor : adj[i]) {
				transposed.add_edge(neighbor, i);
			}
		}
		DFS_SCC(transposed);
	}

	Graph component_graph() {
		strongly_connected_components();
		size_t SCC_SIZE = SCC.size();
		std::vector<std::vector<bool>> is_connected(SCC_SIZE, std::vector<bool>(SCC_SIZE, false));
		Graph cg(SCC_SIZE, Graph_Type::Directed);
		for (auto i = 0; i < n; ++i) {
			size_t temp1 = info[i].scc;
			for (const auto& neighbor : adj[i]) {
				size_t temp2 = info[neighbor].scc;
				if ((temp1 != temp2) && !is_connected[temp1][temp2]) {
					cg.add_edge(temp1, temp2);
					is_connected[temp1][temp2] = true;
				}
			}
		}
		for (auto i = 0; i < SCC_SIZE; ++i) {
			std::sort(cg.adj[i].begin(), cg.adj[i].end());
		}
		return cg;
	}

	void graph_view() {
		size_t temp = adj.size();
		for (auto i = 0; i < temp; ++i) {
			std::cout << i << " : ";
			for (auto j = 0; j < adj[i].size(); ++j) {
				std::cout << adj[i][j] << ' ';
			}
			std::cout << '\n';
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
				DFS_visit(v, time);
			}
		}
		info[u].color = Color::Black;
		++time;
		info[u].f = time;
		sorted.push_front(u);
	}

	void DFS_SCC(Graph& transposed) {
		size_t component = 0;
		while (!sorted.empty()) {
			vertex i = sorted.front();
			sorted.pop_front();
			std::vector<vertex> scc;
			if (transposed.info[i].color == Color::White) {
				DFS_SCC_visit(transposed, i, scc, component);
				SCC.push_back(scc);
				component++;
			}
		}
	}

	void DFS_SCC_visit(Graph& transposed, vertex u, std::vector<vertex>& scc, size_t& component) {
		transposed.info[u].color = Color::Gray;
		scc.push_back(u);
		info[u].scc = component;
		for (const auto& v : transposed.adj[u]) {
			if (transposed.info[v].color == Color::White) {
				DFS_SCC_visit(transposed, v, scc, component);
			}
		}
		transposed.info[u].color = Color::Black;
	}
};

int main() 
{
	Graph g(8, Graph_Type::Directed);
	g.add_edge(0, 1);
	g.add_edge(1, 2);
	g.add_edge(2, 0);
	g.add_edge(2, 3);
	g.add_edge(1, 3);
	g.add_edge(1, 4);
	g.add_edge(4, 5);
	g.add_edge(3, 5);
	g.add_edge(5, 3);
	g.add_edge(4, 6);
	g.add_edge(6, 4);
	g.add_edge(6, 7);
	g.add_edge(5, 7);
	g.add_edge(7, 7);
	auto cg = g.component_graph();
	cg.graph_view();
}
