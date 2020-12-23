#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Directed_Graph {
private:	
	int n;
	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
public:
	Directed_Graph(int n) : n{ n }, adj(n), visited(n) {}

	void add_edge(int u, int v) {
		adj[u].push_back(v);
	}

	void sort_adj() {
		for (auto i = 0; i < n; ++i) {
			std::sort(adj[i].begin(), adj[i].end());
		}
	}

	void graph_view() {
		for (auto u = 0; u < n; ++u) {
			for (auto v : adj[u]) {
				if (adj[u].size()) {
					std::cout << u << "->" << v << '\n';
				}
			}
		}
	}

	void dfs(int s) {
		std::fill(visited.begin(), visited.end(), false);
		dfs_(s);
	}

	int component() {
		int count = 0;
		std::fill(visited.begin(), visited.end(), false);
		for (auto i = 0; i < n; ++i) {
			if (!visited[i]) {
				// std::cout << "-- new component --" << '\n';
				dfs_(i);
				count++;
			}
		}
		return count;
	}

private:
	void dfs_(int s) {
		if (visited[s]) {
			return;
		}
		visited[s] = true;
		// std::cout << "node " << s << " vistied" << '\n';
		for (auto u : adj[s]) {
			dfs_(u);
		}
	}
};

int main()
{
	Directed_Graph dg(10);
	dg.add_edge(0, 1);
	dg.add_edge(2, 3);
	dg.add_edge(1, 3);
	dg.add_edge(4, 6);
	dg.add_edge(5, 7);
	dg.add_edge(5, 8);
	dg.add_edge(7, 8);
	dg.sort_adj();
	auto components = dg.component();
	std::cout << components;
}
