#include <iostream>
#include <complex>

using namespace std::complex_literals;

int main()
{
	// (a + bi) * (c + di) = (ac - bd) + (ad + bc)i
	std::complex<int> c1 = 1.0 + 1i;
	std::complex<int> c2 = 1.0 - 1i;
	auto a = c1.real();
	auto b = c1.imag();
	auto c = c2.real();
	auto d = c2.imag();
	auto temp1 = a * c;
	auto temp2 = b * d;
	auto temp3 = (a + b) * (c + d);
	std::complex<int> c3 = (temp1 - temp2) * 1.0 + (temp3 - temp1 - temp2) * 1.0  * 1i;
	std::cout << c3.real() << '+' << c3.imag() << 'i';
}
