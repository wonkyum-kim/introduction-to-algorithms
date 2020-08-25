#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

// top_down_recursion

template<typename T>
int cut_rod(const std::vector<T>& p, int n)
{
	if (n == 0)
		return 0;
	int q = std::numeric_limits<int>::min();
	for (int i = 1; i <= n; ++i)
		q = std::max(q, p[i] + cut_rod(p, n - i));
	return q;
}

int main()
{
	constexpr int dummy = 0;
	int n = 0;
	std::cin >> n;
	std::vector<int> p{ dummy,1,5,8,9,10,17,17,20,24,30 };
	std::cout << cut_rod(p, n);
}
