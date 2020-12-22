#include <iostream>
#include <vector>

class Directed_Graph {
private:
	int n;								              // number of nodes
	std::vector<std::vector<int>> adj;	// adjacency list
public:
	Directed_Graph(int n) : n{ n } {
		adj.resize(n);
	}

	void add_edge(int u, int v) {
		adj[u].push_back(v);
	}

	void print_edge(int u) {
		for (auto v : adj[u]) {
			std::cout << u << ' ' << v << '\n';
		}
	}
};

int main()
{
	Directed_Graph dg(4);
	dg.add_edge(0, 1);
	dg.add_edge(1, 2);
	dg.add_edge(1, 3);
	dg.add_edge(2, 3);
	dg.add_edge(3, 0);
	dg.print_edge(0);
	dg.print_edge(1);
	dg.print_edge(2);
	dg.print_edge(3);
}
