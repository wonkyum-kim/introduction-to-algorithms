#include <vector>
#include <iostream>

template<typename T>
int linearSearch(std::vector<T>& A, const T& key)
{
	for (size_t i = 0; i<A.size(); ++i)
	{
		if (key==A[i])
			return i;
	}
	return -1;
}

int main()
{
	std::vector<int> v = { 5,2,3,1,4 };
	std::cout << linearSearch(v, 3) + 1;
	return 0;
}