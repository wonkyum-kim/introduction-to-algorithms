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
std::vector<int> indegree;
std::vector<int> sorted;

void topological_sort()
{
	std::queue<int> q;
	sorted.resize(V);
	for (auto i = 0; i < V; ++i) {
		if (indegree[i] == 0) {
			q.push(i);
		}
	}
	for (auto i = 0; i < V; ++i) {
		if (q.empty()) {
			break;
		}
		int curr = q.front();
		q.pop();
		sorted[i] = curr;
		for (auto& [next, weight] : adj[curr]) {
			indegree[next]--;
			if (indegree[next] == 0) {
				q.push(next);
			}
		}
	}
}


void initialize_sigle_source(int s)
{
	distance.resize(V, INF);
	parent.resize(V, -1);
	distance[s] = 0;
}

void Bellman_Ford(int s)
{
	topological_sort();
	initialize_sigle_source(s);
	for (auto a : sorted) {
		for (auto& [b, w] : adj[a]) {
			if (distance[a] != INF && distance[b] > distance[a] + w) {
				distance[b] = distance[a] + w;
			}
		}
	}
}

int main()
{
	std::cin >> V >> E;
	adj.resize(V);
	indegree.resize(V);
	for (auto i = 0; i < E; ++i) {
		int a = 0;
		int b = 0;
		int w = 0;
		std::cin >> a >> b >> w;
		adj[a].push_back({ b,w });
		indegree[b]++;
	}

	Bellman_Ford(0);
	std::cout << distance[5];
}

/*
6 10
0 1 2 
0 3 6
1 3 7
1 4 4
1 5 2
2 0 5 
2 1 3
3 4 -1
3 5 1
4 5 -2
*/
