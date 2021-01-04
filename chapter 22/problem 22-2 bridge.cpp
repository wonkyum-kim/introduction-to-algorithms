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
		size_t low = 0;
	};

	vertex n;
	Graph_Type g_type;
	std::vector<std::vector<vertex>> adj;
	std::vector<vertex_info> info;
	std::vector<std::pair<vertex, vertex>> br;

public:
	Graph(vertex n, Graph_Type g_type) : n{ n }, g_type{ g_type }, adj(n), info(n) {}

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

	void bridges() {
		size_t brsz = br.size();
		std::cout << brsz << '\n';
		std::sort(br.begin(), br.end());
		for (auto i = 0; i < brsz; ++i) {
			std::cout << br[i].first + 1 << ' ' << br[i].second + 1 << '\n';
		}
	}

private:
	void DFS_visit(vertex u, size_t& time) {
		++time;
		info[u].d = time;
		info[u].color = Color::Gray;
		info[u].low = time;
		for (auto v : adj[u]) {
			if (info[v].color == Color::White) {
				info[v].phi = u;
				info[u].children++;
				DFS_visit(v, time);
				info[u].low = std::min(info[u].low, info[v].low);
				if (info[u].d < info[v].low) {
					if (u < v) {
						br.push_back({ u,v });
					}
					else {
						br.push_back({ v,u });
					}
				}
			}
			else if (v != info[u].phi) {
				info[u].low = std::min(info[u].low, info[v].d);
			}
		}
		info[u].color = Color::Black;
		++time;
		info[u].f = time;
	}

};

int main()
{
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);

	int v = 0;
	int e = 0;
	std::cin >> v >> e;
	Graph g(v, Graph_Type::Undirected);
	for (auto i = 0; i < e; ++i) {
		int a = 0;
		int b = 0;
		std::cin >> a >> b;
		g.add_edge(a - 1, b - 1);
	}
	g.DFS();
	g.bridges();
}
