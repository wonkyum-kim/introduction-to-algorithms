#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

class Undirected_Graph {
private:	
	int n;
	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
public:
	Undirected_Graph(int n) : n{ n }, adj(n), visited(n) {}

	void add_edge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
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

	void dfs() {
		std::fill(visited.begin(), visited.end(), false);
		dfs(0);
	}

	int component() {
		int count = 0;
		std::fill(visited.begin(), visited.end(), false);
		for (auto i = 0; i < n; ++i) {
			if (!visited[i]) {
				// std::cout << "-- new component --" << '\n';
				dfs(i);
				count++;
			}
		}
		return count;
	}

private:
	void dfs(int s) {
		if (visited[s]) {
			return;
		}
		visited[s] = true;
		// std::cout << "node " << s << " vistied" << '\n';
		for (auto u : adj[s]) {
			dfs(u);
		}
	}
};

int main()
{
	Undirected_Graph udg(10);
	udg.add_edge(0, 1);
	udg.add_edge(2, 3);
	udg.add_edge(1, 3);
	udg.add_edge(4, 6);
	udg.add_edge(5, 7);
	udg.add_edge(5, 8);
	udg.add_edge(7, 8);
	udg.sort_adj();
	auto components = udg.component();
	std::cout << components;
}
