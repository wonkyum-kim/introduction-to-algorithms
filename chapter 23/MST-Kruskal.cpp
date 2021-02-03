#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <queue>
#include <string>
#include <tuple>

std::vector<int> link;
std::vector<int> size;

int find(int a)
{
	if (a == link[a]) {
		return a;
	}
	return link[a] = find(link[a]);
}

bool unite(int a, int b)
{
	a = find(a);
	b = find(b);
	if (a == b) {
		return false;
	}
	if (size[a] < size[b]) {
		std::swap(a, b);
	}
	size[a] += size[b];
	link[b] = a;
	return true;
}

int MST_Kruskal(std::vector<std::tuple<int, int, int>>&edges)
{
	std::sort(edges.begin(), edges.end(),
		[](auto a, auto b) {return std::get<2>(a) < std::get<2>(b); });

	int ans = 0;

	for (auto& x : edges) {
		if (unite(std::get<0>(x), std::get<1>(x))) {
			ans += std::get<2>(x);
		}
	}
	return ans;
}

int main()
{
	std::ios_base::sync_with_stdio(0);
	std::cin.tie(0);
	int v = 0;
	int e = 0;
	std::cin >> v >> e;

	link.resize(v);
	std::iota(link.begin(), link.end(), 0);
	size.resize(v, 1);

	std::vector<std::tuple<int, int, int>> edges;
	for (auto i = 0; i < e; ++i) {
		// Add edges
	}

	std::cout << MST_Kruskal(edges);
}
