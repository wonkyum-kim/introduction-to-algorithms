#include <vector>
#include <utility>
#include <numeric>

using Point = std::pair<double, double>;

double distance(const Point& p1, const Point& p2)
{
	return std::hypot(p1.first - p2.first, p1.second - p2.second);
}

double bitonic_tour(std::vector<Point>& p) 
{
	std::sort(p.begin(), p.end());
	const size_t n = p.size();
	std::vector<std::vector<double>> dp(n, std::vector<double>(n, -1));
	dp[0][0] = 0;
	for (auto i = 1; i < n; ++i) {
		dp[0][i] = dp[0][i - 1] + distance(p[i - 1], p[i]);
	}
	for (auto i = 1; i < n; ++i) {
		for (auto j = i; j < n; ++j) {
			auto minimum = std::numeric_limits<double>::max();
			if (i == j || i == j - 1) {
				for (auto k = 0; k < i; ++k) {
					auto opt = dp[k][i] + distance(p[k], p[j]);
					minimum = std::min(minimum, opt);
				}
				dp[i][j] = minimum;
			}
			else {
				dp[i][j] = dp[i][j - 1] + distance(p[j - 1], p[j]);
			}
		}
	}
	return dp[n - 1][n - 1];
}



int main()
{
	std::vector<Point> p;
	p.push_back({ 0.0, 0.0 });
	p.push_back({ 1.0, 6.0 });
	p.push_back({ 2.0, 3.0 });
	p.push_back({ 5.0, 2.0 });
	p.push_back({ 6.0, 5.0 });
	p.push_back({ 7.0, 1.0 });
	p.push_back({ 8.0, 4.0 });
	std::cout << bitonic_tour(p);
}
