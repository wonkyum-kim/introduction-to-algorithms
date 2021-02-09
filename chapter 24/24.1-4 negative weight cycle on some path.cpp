#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <cmath>
#include <tuple>
#include <numeric>

constexpr auto INF = std::numeric_limits<long long>::max();
constexpr auto N_INF = std::numeric_limits<long long>::min();

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

void Bellman_Ford(int s)
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
				distance[b] = N_INF;
				distance[a] = N_INF;
			}
		}
	}

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

	Bellman_Ford(0);

	for (auto x : distance) {
		if (x == INF) {
			std::cout << "INF\n";
		}
		else if (x == N_INF) {
			std::cout << "N_INF\n";
		}
		else {
			std::cout << x << '\n';
		}
	}
}

	/*
	4 4
	0 1 2
	1 2 -2
	2 1 -2
	2 3 1
	*/
