#include <string>
#include <queue>
#include <cmath>
#include <tuple>
#include <numeric>

constexpr auto INF = std::numeric_limits<int>::max();
int n = 0;
int m = 0;
std::vector<std::vector<int>> dist;
std::vector<std::vector<int>> parent;

void Floyd_Warshall()
{
	parent.resize(n, std::vector<int>(n, -1));
	for (auto i = 0; i < n; ++i) {
		for (auto j = 0; j < n; ++j) {
			if (i != j && dist[i][j] != INF) {
				parent[i][j] = i;
			}
		}
	}

	for (auto k = 0; k < n; ++k) {
		for (auto i = 0; i < n; ++i) {
			for (auto j = 0; j < n; ++j) {
				if (dist[i][k] == INF || dist[k][j] == INF) {
					continue;
				}
				if (dist[i][j] > dist[i][k] + dist[k][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					parent[i][j] = parent[k][j];
				}
			}
		}
	}
}

void print_all_pairs_shortest_path(int i, int j)
{
	if (i == j) {
		std::cout << i << ' ';
	}
	else if (parent[i][j] == -1) {
		std::cout << "no path from " << i << " to" << j << " exist";
	}
	else {
		print_all_pairs_shortest_path(i, parent[i][j]);
		std::cout << j + 1 << ' ';
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
}
