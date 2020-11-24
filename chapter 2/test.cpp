#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

size_t modified_merge(std::vector<int>& A, size_t p, size_t q, size_t r)
{
	size_t inv = 0;
	size_t n1 = q - p + 1;
	size_t n2 = r - q;
	std::vector<int> L;
	std::vector<int> R;
	L.push_back(0);
	R.push_back(0);
	for (auto i = 1; i <= n1; ++i) {
		L.push_back(A[p + i - 1]);
	}
	for (auto j = 1; j <= n2; ++j) {
		R.push_back(A[q + j]);
	}
	size_t i = 1;
	size_t j = 1;
	size_t k = p;
	while (i != (n1 + 1) && j != (n2 + 1)) {
		if (L[i] < R[i]) {
			A[k] = L[i];
			i++;
		}
		else {
			A[k] = R[j];
			// this keeps track of the number of inversions
			// between the left and right arrays
			inv += j;
			j++;
		}
		k++;
	}
	if (i == n1 + 1) {
		for (auto m = j; m <= n2; ++m) {
			A[k] = R[m];
			k++;
		}
	}
	if (j == n2 + 1) {
		for (auto m = i; m <= n1; ++m) {
			A[k] = L[m];
			// tracks inversions once we have exhausted the raight array.
			// at this point, every element of the right array contributes an inversion.
			inv += n2;
			k++;
		}
	}
	return inv;
}


size_t modified_merge_sort(std::vector<int>& A, size_t p, size_t r)
{
	if (p < r) {
		size_t q = (p + r) / 2;
		size_t left = modified_merge_sort(A, p, q);
		size_t right = modified_merge_sort(A, q + 1, r);
		size_t inv = modified_merge(A, p, q, r) + left + right;
		return inv;
	}
	return 0;
}

int main()
{
	std::vector<int> v{ 0,2,3,8,6,1 };
	std::cout << modified_merge_sort(v, 1, v.size() - 1);
}
