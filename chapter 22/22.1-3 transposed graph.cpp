#include <iostream>
#include <vector>

class Directed_Graph {
private:
	int n;								              // number of nodes
	std::vector<std::vector<int>> adj;	// adjacency list
public:
	Directed_Graph(int n) : n{ n } , adj(n) {}

	void add_edge(int u, int v) {
		adj[u].push_back(v);
	}

	Directed_Graph transpose() {
		Directed_Graph transposed(n);
		for (auto u = 0; u < n; ++u) {
			for (auto v : adj[u]) {
				transposed.add_edge(v, u);
			}
		}
		return transposed;
	}

	void graph_view() {
		for (auto u = 0; u < n; ++u) {
			for (auto v : adj[u]) {
				if (adj[u].size()) {
					std::cout << u << ' ' << v << '\n';
				}
			}
		}
	}
};

int main()
{
	Directed_Graph dg(4);
	dg.add_edge(0, 1);
	dg.add_edge(2, 3);
	dg.add_edge(3, 0);
	auto transposed = dg.transpose();
	transposed.graph_view();
}
