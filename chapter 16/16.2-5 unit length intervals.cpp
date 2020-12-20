#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>
#include <numeric>

std::vector<std::pair<double, double>> unit_length_intervals(std::vector<double>& x)
{
	std::sort(x.begin(), x.end());
	std::vector<std::pair<double, double>> S;
	double start = x[0];
	S.push_back({ start, start + 1 });
	for (auto i = 1; i < x.size(); ++i) {
		if (x[i] <= start + 1) {
			continue;
		}
		else {
			start = x[i];
			S.push_back({ start, start + 1 });
		}
	}
	return S;
}


int main()
{
}
