#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

enum class Dir {
	Directed, Undirected
};

class Graph {
private:
	int n;
	Dir dir;
	std::queue<int> q;
	std::vector<std::vector<int>> adj;
	std::vector<bool> visited;
public:
	Graph(int n, Dir dir) : n{ n }, dir{ dir }, adj(n), visited(n, false) {}

	void add_edge(int u, int v) {
		if (dir == Dir::Undirected) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		else {
			adj[u].push_back(v);
		}
	}

	void search_reset() {
		std::fill(visited.begin(), visited.end(), false);
	}

	void sort_adj() {
		for (auto i = 0; i < n; ++i) {
			std::sort(adj[i].begin(), adj[i].end());
		}
	}

	void dfs(int u) {
		if (visited[u]) {
			return;
		}
		visited[u] = true;
		std::cout << u + 1 << ' ';
		for (auto v : adj[u]) {
			dfs(v);
		}
	}

	void bfs(int x) {
		visited[x] = true;
		std::vector<int> distance(n);
		q.push(x);
		while (!q.empty()) {
			int s = q.front();
			q.pop();
			std::cout << s + 1 << ' ';
			for (auto u : adj[s]) {
				if (visited[u]) {
					continue;
				}
				visited[u] = true;
				distance[u] = distance[s] + 1;
				q.push(u);
			}
		}
	}
};

int main()
{
}
