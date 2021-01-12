#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include <utility>
#include <numeric>
#include <iomanip>

using Point = std::pair<long double, long double>;

long double distance(const Point& p1, const Point& p2)
{
	return std::hypot(p1.first - p2.first, p1.second - p2.second);
}

long double bitonic_tour(std::vector<Point>& p)
{
	std::sort(p.begin() + 1, p.end());
	size_t n = p.size() - 1;
	// dp[a][b] (a < b)
	std::vector<std::vector<long double>> dp(n + 1, std::vector<long double>(n + 1));
	dp[1][2] = distance(p[1], p[2]);
	for (auto j = 3; j < n + 1; ++j) {
		// k > 1
		// route 1 : from p[1] to p[i]
		// route 2 : from p[1] to p[i + k]
		// dp[i][i + k] = dp[i][i + k - 1] + distance(p[i + k - 1], p[i + k])
		for (auto i = 1; i < j - 1; ++i) {
			dp[i][j] = dp[i][j - 1] + distance(p[j - 1], p[j]);
		}
		// k = 1
		// route 1 : from p[1] to p[i]
		// route 2 : from p[1] to p[i + 1]
		// dp[i][i + 1] = min(dp[i][i + 1], dp[0 .. i - 1][i] + distnace(p[0 .. i - 1] + p[i + 1])
		dp[j - 1][j] = std::numeric_limits<long double>::max();
		for (auto i = 1; i < j - 1; ++i) {
			dp[j - 1][j] = std::min(dp[j - 1][j], dp[i][j - 1] + distance(p[i], p[j]));
		}
	}

	long double ans = std::numeric_limits<long double>::max();
	for (auto i = 1; i < n; ++i) {
		ans = std::min(ans, dp[i][n] + distance(p[i], p[n]));
	}
	return ans;
}


int main()
{
	std::vector<Point> p;
	p.push_back({ 0.0, 0.0 });	// dummy
	p.push_back({ 0.0, 0.0 });
	p.push_back({ 1.0, 6.0 });
	p.push_back({ 2.0, 3.0 });
	p.push_back({ 5.0, 2.0 });
	p.push_back({ 6.0, 5.0 });
	p.push_back({ 7.0, 1.0 });
	p.push_back({ 8.0, 4.0 });
	std::cout << bitonic_tour(p);
}
