#include <iostream>
#include <vector>


/* the result of this code is false */
/* not to use right now*/

template<typename T>
int merge(std::vector<T>& A, size_t left, size_t mid, size_t right)
{
	size_t i = left;
	size_t j = mid + 1;
	int count = 0;

	std::vector<T> sorted;

	while (i <= mid && j <= right)
	{
		if (A[i] <= A[j])
			sorted.push_back(A[i++]);
		else
		{
			sorted.push_back(A[j++]);
			count++;
		}
			
	}

	if (i > mid)
	{
		while (j <= right)
			sorted.push_back(A[j++]);
	}
	else if (j > right)
	{
		while (i <= mid)
			sorted.push_back(A[i++]);
	}

	size_t k = 0;
	for (size_t i = left; i <= right; i++)
		std::swap(A[i], sorted[k++]);

	return count;
}

template<typename T>
int inversion_count(std::vector<T>& A, size_t left, size_t right)
{
	if (left < right)
	{
		size_t mid = (left + right) / 2;
		int count = 0;

		count += inversion_count(A, left, mid);
		count += inversion_count(A, mid + 1, right);
		count += merge(A, left, mid, right);
		return count;
	}
	else
		return 0;
}

template<typename T>
int inversion(std::vector<T>& A)
{
	return inversion_count(A, 0, A.size() - 1);
}


int main()
{
	std::vector<int> A{ 5,2,4,1,3 };
	std::cout << inversion(A);

	return 0;
}

/*
#include <iostream>
#include <vector>

template<typename T>
int merge(std::vector<T>& A, const size_t p, const size_t q, const size_t r)
{
	size_t n1 = q - p + 1;
	size_t n2 = r - q;
	int count = 0;
	std::vector<T> L, R;

	// sentinel value
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

	for (auto k = p; k <= r; ++k) {
		if (L[i] < R[i] || j == n2 + 1) {
			A[k] = L[i++];
		}
		else {
			A[k] = R[j++];
			count++;
		}
	}
	return count;
}

template<typename T>
int merge_sort(std::vector<T>& A, const size_t p, const size_t r)
{
	if (p < r) {
		size_t q = (p + r) / 2;
		int count = 0;
		count += merge_sort(A, p, q);
		count += merge_sort(A, q + 1, r);
		count += merge(A, p, q, r);
		return count;
	}
	return 0;
}

int main()
{
	std::vector<int> A{ 0,5,2,4,1,3 };
	std::cout << merge_sort(A,1,5);
	return 0;

}
*/

