#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <cmath>
#include <tuple>
#include <numeric>

constexpr auto INF = std::numeric_limits<int>::max();
int n = 0;
int m = 0;
std::vector<std::vector<int>> dist;

void Floyd_Warshall()
{
	for (auto k = 0; k < n; ++k) {
		for (auto i = 0; i < n; ++i) {
			for (auto j = 0; j < n; ++j) {
				if (dist[i][k] == INF || dist[k][j] == INF) {
					continue;
				}
				dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	std::cin >> n >> m;

	dist.resize(n, std::vector<int>(n, INF));
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < n; ++j) {
			if (i == j) {
				dist[i][j] = 0;
			}
		}
	}

	for (auto i = 0; i < m; ++i) {
		int a = 0;
		int b = 0;
		int c = 0;
		std::cin >> a >> b >> c;
		dist[a][b] = c;
	}

	Floyd_Warshall();

	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < n; ++j) {
			if (dist[i][j] == INF) {
				std::cout << 0 << ' ';
			}
			else {
				std::cout << dist[i][j] << ' ';
			}
		}
		std::cout << '\n';
	}
}
