#include <iostream>
#include <bitset>

template<size_t N>
std::bitset<N+1> add_binary(const std::bitset<N>& A, const std::bitset<N>& B)
{
	int carry = 0;
	std::bitset<N + 1> C;
	for (int i = 0; i < N; ++i) {
		auto temp = A[i] + B[i] + carry;
		C[i] = temp % 2;
		carry = temp / 2;
	}
	C[N] = carry;
	return C;
}

int main()
{
	std::bitset<8> A(8);
	std::bitset<8> B(2);
	auto C = add_binary(A, B);
	std::cout << C;
}
