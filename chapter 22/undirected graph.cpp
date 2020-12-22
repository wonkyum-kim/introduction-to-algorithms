#include <iostream>
#include <vector>

class Undirected_Graph {
private:
	int n;								// number of nodes
	std::vector<std::vector<int>> adj;	// adjacency list
public:
	Undirected_Graph(int n) : n{ n } {
		adj.resize(n);
	}

	void add_edge(int u, int v) {
		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	void print_edge(int s) {
		for (auto u : adj[s]) {
			std::cout << s << ' ' << u << '\n';
		}
	}
};

int main()
{
	Undirected_Graph ug(4);
	ug.add_edge(0, 1);
	ug.add_edge(0, 3);
	ug.add_edge(1, 2);
	ug.add_edge(1, 3);
	ug.add_edge(2, 3);
	ug.print_edge(2);
}
