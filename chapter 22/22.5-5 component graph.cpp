#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <numeric>
#include <stack>
#include <utility>
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

	vertex n;
	Graph_Type type;
	std::vector<std::vector<size_t>> adj;
	std::list<size_t> sorted;
	std::vector<std::vector<size_t>> SCC;
	std::vector<size_t> SCC_info;

public:
	Graph(size_t n, Graph_Type dir) : n{ n }, type{ dir }, adj(n), SCC_info(n) {}

	void add_edge(size_t u, size_t v) {
		adj[u].push_back(v);
		if (type == Graph_Type::Undirected) {
			adj[v].push_back(u);
		}
	}

	using vertex_info = std::tuple<Color, size_t, size_t, size_t>;	// u.color, u.d, u.f, u.phi

	void DFS() {
		std::vector<vertex_info> info(n, { Color::White, 0, 0, -1 });
		size_t time = 0;
		for (auto i = 0; i < n; ++i) {
			if (std::get<0>(info[i]) == Color::White) {
				DFS_visit(i, time, info);
			}
		}
	}

	std::list<size_t> topological_sort() {
		assert(type == Graph_Type::Directed);
		DFS();
		return sorted;
	}

	void strongly_connected_components() {
		Graph transposed(n, Graph_Type::Directed);
		for (auto i = 0; i < n; ++i) {
			for (auto neighbor : adj[i]) {
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
			size_t temp1 = SCC_info[i];
			for (auto neighbor : adj[i]) {
				size_t temp2 = SCC_info[neighbor];
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

private:
	void DFS_visit(size_t u, size_t& time, std::vector<vertex_info>& info) {
		++time;
		std::get<1>(info[u]) = time;
		std::get<0>(info[u]) = Color::Gray;
		for (auto v : adj[u]) {
			if (std::get<0>(info[v]) == Color::White) {
				std::get<3>(info[v]) = u;
				DFS_visit(v, time, info);
			}
		}
		std::get<0>(info[u]) = Color::Black;
		++time;
		std::get<2>(info[u]) = time;
		sorted.push_front(u);
	}

	void DFS_SCC(Graph& transposed) {
		std::list<size_t> sorted = topological_sort();
		std::vector<vertex_info> info(n, { Color::White, 0, 0, -1 });
		size_t time = 0;
		size_t component = 0;
		while (!sorted.empty()) {
			size_t i = sorted.front();
			sorted.pop_front();
			std::vector<size_t> scc;
			if (std::get<0>(info[i]) == Color::White) {
				DFS_SCC_visit(transposed, i, time, info, scc, component);
				SCC.push_back(scc);
				component++;
			}
		}
	}

	void DFS_SCC_visit(Graph& transposed, size_t u, size_t& time, std::vector<vertex_info>& info, std::vector<size_t>& scc, size_t& component) {
		++time;
		std::get<1>(info[u]) = time;
		std::get<0>(info[u]) = Color::Gray;
		scc.push_back(u);
		SCC_info[u] = component;
		for (auto v : transposed.adj[u]) {
			if (std::get<0>(info[v]) == Color::White) {
				std::get<3>(info[v]) = u;
				DFS_SCC_visit(transposed, v, time, info, scc, component);
			}
		}
		std::get<0>(info[u]) = Color::Black;
		++time;
		std::get<2>(info[u]) = time;
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
}
