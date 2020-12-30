#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
#include <numeric>
#include <queue>
#include <utility>
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
	std::vector<vertex> indegree;

public:
	Graph(size_t n, Graph_Type dir) : n{ n }, type{ dir }, adj(n), indegree(n) {}

	void add_edge(size_t u, size_t v) {
		adj[u].push_back(v);
		indegree[v]++;
		if (type == Graph_Type::Undirected) {
			adj[v].push_back(u);
		}
	}

	std::vector<vertex> topological_sort() {
		assert(type == Graph_Type::Directed);
		std::queue<vertex> q;
		std::vector<vertex> sorted(n);
		for (auto i = 0; i < n; ++i) {
			if (indegree[i] == 0) {
				q.push(i);
			}
		}
		for (auto i = 0; i < n; ++i) {
			if (q.empty()) {
				break;
			}
			vertex curr = q.front();
			q.pop();
			sorted[i] = curr;
			for (auto next : adj[curr]) {
				indegree[next]--;
				if (indegree[next] == 0) {
					q.push(next);
				}
			}
		}
		return sorted;
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
	auto sorted = g.topological_sort();
	for (auto x : sorted) {
		std::cout << x + 1 << ' ';
	}
}
