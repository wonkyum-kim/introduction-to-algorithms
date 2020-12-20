#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>

double fractional_knapsack(std::vector<std::pair<double, double>>& stuff, int n, double W)
{
	std::sort(stuff.begin(), stuff.end(), [](auto& a, auto& b) {return a.second / a.first > b.second / b.first; });
	double cur_weight = 0;
	double final_value = 0;
	for (auto i = 1; i <= n; ++i) {
		if (cur_weight + stuff[i].first <= W) {
			cur_weight += stuff[i].first;
			final_value += stuff[i].second;
		}
		else {
			double fraction = W - cur_weight;
			final_value += fraction * stuff[i].second / stuff[i].first;
		}
	}
	return final_value;
}

int main()
{
	int n = 0;
	double W = 0;
	std::cin >> n >> W;
	std::vector<std::pair<double, double>> stuff = { {0,0} };
	for (auto i = 0; i < n; ++i) {
		double weight = 0;
		double value = 0;
		std::cin >> weight >> value;
		stuff.push_back({ weight, value });
	}
	std::cout << knapsack(stuff, n, W);
}
