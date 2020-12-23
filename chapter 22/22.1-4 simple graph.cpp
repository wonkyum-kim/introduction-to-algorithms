#include <iostream>
#include <vector>

class Directed_Graph {
private:
	int n;					
	std::vector<std::vector<int>> adj;	
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

	Directed_Graph make_simple() {
		Directed_Graph simple(n);
		for (auto u = 0; u < n; ++u) {
			std::vector<bool> memo(n, false);
			memo[u] = true;
			for (auto v : adj[u]) {
				if (!memo[v]) {
					memo[v] = true;
					simple.add_edge(u, v);
				}
			}
		}
		return simple;
	}
};

int main()
{
	Directed_Graph dg(4);
	dg.add_edge(0, 1);
	dg.add_edge(0, 1);
	dg.add_edge(1, 2);
	dg.add_edge(1, 2);
	dg.add_edge(1, 1);
	auto simple = dg.make_simple();
	simple.graph_view();
}
