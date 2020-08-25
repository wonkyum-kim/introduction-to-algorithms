#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// bottom up

template<typename T>
T bottom_up_cut_rod(const std::vector<T>& p, int n)
{
	std::vector<T> r(n + 1);
	for (auto j = 1; j <= n; ++j) {
		int q = std::numeric_limits<int>::min();
		for (auto i = 1; i <= j; ++i)
			q = std::max(q, p[i] + r[j - i]);
		r[j] = q;
	}
	return r[n];
}

int main()
{
	constexpr int dummy = 0;
	int n = 0;
	std::cin >> n;
	std::vector<int> p{ dummy,1,5,8,9,10,17,17,20,24,30 };
	std::cout << bottom_up_cut_rod(p, n);
}
