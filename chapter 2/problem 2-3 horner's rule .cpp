#include <iostream>
#include <vector>

template<typename T>
T horner(std::vector<T>& A, const T x)
{
	T y = 0;
	int i = A.size() - 1;
	while (i >= 0)
	{
		y = A[i] + x * y;
		i--;
	}
	return y;
}

int main()
{
	std::vector<int> coefficient{ 1, 2, 3 };
	std::cout << horner(coefficient, 2);
	return 0;
}

/*
A= 1,2,3
x = 2

A[0]x2^0 + A[1]x2^1 + A[2]x2^2

1+4+12 = 17

A[0] + 2(A[1] + 2A[2]) 

y = 0
y = A[2] + 0 = 3
y = A[1] + 2A[2] = 8
y = A[0] + 2(A[1] + 2A[2]) = 17

*/