#include <iostream>
#include <vector>
#include <stdexcept>

template<typename T>
int binary_search(std::vector<T>& A, const size_t left, const size_t right, const T target)
{
	if (left > right)	
	    throw std::invalid_argument{"left must not bigger than right"};
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
}
