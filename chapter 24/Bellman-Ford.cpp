#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <cmath>
#include <tuple>
#include <numeric>

constexpr auto INF = std::numeric_limits<long long>::max();

int V = 0;
int E = 0;
std::vector<std::vector<std::pair<int, int>>> adj;
std::vector<long long> distance;
std::vector<int> parent;

void initialize_sigle_source(int s) 
{
	distance.resize(V, INF);
	parent.resize(V, -1);
	distance[s] = 0;
}

bool Bellman_Ford(int s)
{
	initialize_sigle_source(s);
	for (auto i = 1; i <= V - 1; ++i) {
		for (auto a = 0; a < V; ++a) {
			for (auto& [b, w] : adj[a]) {
				// Relax
				if (distance[a] != INF && distance[b] > distance[a] + w) {
					distance[b] = distance[a] + w;
					parent[b] = a;
				}
			}
		}
	}

	for (auto a = 0; a < V; ++a) {
		for (auto& [b, w] : adj[a]) {
			if (distance[a] != INF && distance[b] > distance[a] + w) {
				return false;
			}
		}
	}
	return true;
}

int main()
{
	std::cin >> V >> E;
	adj.resize(V);
	for (auto i = 0; i < E; ++i) {
		int a = 0;
		int b = 0;
		int w = 0;
		std::cin >> a >> b >> w;
		adj[a].push_back({ b,w });
	}

	bool flag = Bellman_Ford(0);
	if (flag) {
		auto d = distance[V - 1];
		if (d == INF) {
			std::cout << "Path does not exist\n";
		}
		else {
			std::cout << d << '\n';
		}
	}
	else {
		std::cout << "A negative cycle has detected\n";
	}
}
