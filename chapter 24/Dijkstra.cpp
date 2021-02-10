#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <cmath>
#include <tuple>
#include <numeric>
#include <stack>

constexpr int INF = std::numeric_limits<int>::max();

int V = 0;
int E = 0;
std::vector<std::vector<std::pair<int, int>>> adj;
std::vector<int> distance;
std::vector<int> parent;
std::vector<bool> processed;

void initialize_sigle_source(int s)
{
	distance.resize(V, INF);
	processed.resize(V, false);
	parent.resize(V, -1);
	distance[s] = 0;
}

void Dijkstra(int s)
{
	initialize_sigle_source(s);
	std::priority_queue<std::pair<int, int>> pq;
	pq.push({ 0,s });
	while (!pq.empty()) {
		int a = pq.top().second;
		pq.pop();
		if (!processed[a]) {
			processed[a] = true;
			// Relax
			for (auto& [b, w] : adj[a]) {
				if (distance[a] != INF && distance[b] > distance[a] + w) {
					distance[b] = distance[a] + w;
					parent[b] = a;
					pq.push({ -distance[b],b });
				}
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
	Dijkstra(0);
}
