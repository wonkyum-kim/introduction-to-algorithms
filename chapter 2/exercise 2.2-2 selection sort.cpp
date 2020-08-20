#include <iostream>
#include <vector>
#include <utility>

template<typename T>
void selection_sort(std::vector<T>& A)
{
	for (size_t i = 0; i < A.size() - 1; ++i) {
		size_t min_index = i;
		for (size_t j = i + 1; j < A.size(); ++j) {
			if (A[min_index] > A[j])
				min_index = j;
		}
		std::swap(A[min_index], A[i]);
	}
}

int main()
{
	std::vector<int>A{ 5,2,4,3,1 };
	selection_sort(A);
	for (auto& x : A)
		std::cout << x << " ";
}
