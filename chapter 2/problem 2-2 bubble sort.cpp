#include <iostream>
#include <vector>
#include <algorithm>

template<typename T>
void bubble_sort(std::vector<T>& A)
{
	for (size_t i = 0; i < A.size() - 1; ++i)
	{
		for (size_t j = A.size() - 1; j > i ; --j)
		{
			if (A[j] < A[j - 1])
				std::swap(A[j], A[j - 1]);
		}
	}
}

int main()
{
	std::vector<int> A{ 5,2,4,1,3 };
	bubble_sort(A);
	for (auto& x : A)
		std::cout << x << ' ';
	return 0;
}