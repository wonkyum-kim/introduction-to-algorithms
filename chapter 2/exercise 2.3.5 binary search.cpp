#include <iostream>
#include <vector>

template<typename T>
int binary_search(std::vector<T>& A, size_t left, size_t right, const T& target)
{
	if (left > right)	return -1;

	size_t mid = (left + right) / 2;
	if (A[mid] > target)
		binary_search(A, left, mid - 1, target);
	else if (A[mid] < target)
		binary_search(A, mid + 1, right, target);
	else
		return mid;
}

int main()
{
	std::vector<int> A{ 1,2,3,4,5 };
	std::cout << binary_search<int>(A, 0, A.size() - 1, 3);
	return 0;
}
