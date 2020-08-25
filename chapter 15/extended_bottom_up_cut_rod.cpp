#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>
#include <utility>

// bottom up

template<typename T>
std::pair<std::vector<T>, std::vector<T>> extended_bottom_up_cut_rod(const std::vector<T>& p, int n)
{
	// r is a max_value array
	// s is a devided length array
	std::vector<T> r(n + 1);
	std::vector<T> s(n + 1);
	for (auto j = 1; j <= n; ++j) {
		int q = std::numeric_limits<int>::min();
		for (auto i = 1; i <= j; ++i) {
			if (q < p[i] + r[j - i]) {
				q = p[i] + r[j - i];
				s[j] = i;
			}
		}
		r[j] = q;
	}
	return { r, s };
}

void print_cut_rod_solution(const std::vector<int>& p, int n)
{
	auto [a, b] = extended_bottom_up_cut_rod(p, n);
	while (n > 0) {
		std::cout << b[n] << ' ';
		n -= b[n];
	}
}

int main()
{
	constexpr int dummy = 0;
	int n = 0;
	std::cin >> n;
	std::vector<int> p{ dummy,1,5,8,9,10,17,17,20,24,30 };
	
	auto [a, b] = extended_bottom_up_cut_rod(p, n);
	std::cout << a[n] << '\n';
	print_cut_rod_solution(p, n);
}
