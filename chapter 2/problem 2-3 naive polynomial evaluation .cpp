#include <iostream>
#include <vector>

template<typename T>
T naive_polynomial_evaluation(std::vector<T>& A, const T x)
{
	T y = 0;
	T term = 0;

	for (int i = A.size() - 1; i > 0; --i)
	{
		term = A[i];
		for (int j = 1; j<=i; ++j)
			term *= x;
		y += term;
	}
	y += A[0];
	return y;
}
int main()
{
	std::vector<int> coefficient{ 1, 2, 3 };
	std::cout << naive_polynomial_evaluation(coefficient, 2);
	return 0;
}

/*
A= 1,2,3
x = 2

A[0]x2^0 + A[1]x2^1 + A[2]x2^2

1+4+12 = 17

*/