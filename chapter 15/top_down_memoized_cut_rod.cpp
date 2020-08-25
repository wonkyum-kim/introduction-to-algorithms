#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// top_down_memoization

template<typename T>
int memoized_cut_rod_aux(const std::vector<T>& p, int n, std::vector<T>& r)
{
	if (r[n] >= 0)
		return r[n];
	int q;
	if (n == 0)
		q = 0;
	else {
		q = std::numeric_limits<int>::min();
		for (auto i = 1; i <= n; ++i)
			q = std::max(q, p[i] + memoized_cut_rod_aux(p, n - i, r));
	}
	r[n] = q;
	return q;
}

template<typename T>
int memoized_cut_rod(const std::vector<T>& p, int n)
{
	std::vector<T> r(n + 1, std::numeric_limits<int>::min());
	return memoized_cut_rod_aux(p, n, r);
}

int main()
{
	constexpr int dummy = 0;
	int n = 0;
	std::cin >> n;
	std::vector<int> p{ dummy,1,5,8,9,10,17,17,20,24,30 };
	std::cout << memoized_cut_rod(p, n);
}
