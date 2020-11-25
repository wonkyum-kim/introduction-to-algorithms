#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <utility>

size_t merge(std::vector<int>& A, size_t p, size_t q, size_t r)
{
	size_t n1 = q - p + 1;
	size_t n2 = r - q;
	std::vector<int> L(n1 + 1);
	std::vector<int> R(n2 + 1);
	for (auto i = 1; i <= n1; ++i) {
		L[i] = A[p + i - 1];
	}
	for (auto j = 1; j <= n2; ++j) {
		R[j] = A[q + j];
	}
	L.push_back(std::numeric_limits<int>::max());
	R.push_back(std::numeric_limits<int>::max());
	size_t i = 1;
	size_t j = 1;
	size_t inversions = 0;
	for (auto k = p; k <= r; ++k) {
		if (L[i] <= R[j]) {
			A[k] = L[i++];
		}
		else {
			inversions += n1 - i + 1;
			A[k] = R[j++];
		}
	}
	return inversions;
}

size_t count_inversions(std::vector<int>& A, size_t p, size_t r)
{
	if (p < r) {
		size_t q = (p + r) / 2;
		size_t left = count_inversions(A, p, q);
		size_t right = count_inversions(A, q + 1, r);
		size_t inversions = left + right + merge(A, p, q, r);
		return inversions;
	}
	return 0;
}

int main()
{
	std::vector<int> v{ 0,2,3,8,6,1 };
	std::cout << count_inversions(v, 1, 5);
}
