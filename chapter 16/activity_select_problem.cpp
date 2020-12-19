#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

using activity = std::vector<std::pair<int, int>>;

activity greedy_activity_selector(activity& v)
{
	// sort by finish time
	std::sort(v.begin(), v.end(), [](auto a, auto b) {return a.second != b.second ? a.second < b.second : a.first < b.first; });

	// selected activity
	std::vector<std::pair<int, int>> A;
	A.push_back(v[0]);

	size_t k = 0;
	size_t n = v.size();

	for (auto m = 1; m < n; ++m) {
		if (v[m].first >= v[k].second) {
			A.push_back(v[m]);
			k = m;
		}
	}
	return A;
}

int main() {
	int test;
	std::cin >> test;
	activity v;
	for (auto i = 0; i < test; ++i) {
		int a = 0, b = 0;
		std::cin >> a >> b;
		v.push_back({ a, b });
	}
	auto A = greedy_activity_selector(v);
	std::cout << A.size();
}
