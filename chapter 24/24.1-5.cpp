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
long long min_d = INF;

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
		bool flag = false;
		for (auto a = 0; a < V; ++a) {
			for (auto& [b, w] : adj[a]) {
				// Relax
				if (distance[a] != INF && distance[b] > distance[a] + w) {
					distance[b] = distance[a] + w;
					parent[b] = a;
					min_d = std::min(min_d, distance[b]);
					flag = true;
				}
			}
		}
		if (flag) {
			break;
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
		std::cout << min_d;
	}
	else {
		std::cout << "A negative cycle has detected\n";
	}
}

	/*
	5 6
	0 1 5
	0 3 9
	0 4 1
	1 2 2 
	2 3 6
	3 4 2
	*/
