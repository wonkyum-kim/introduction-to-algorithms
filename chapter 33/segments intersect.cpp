#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>

using point = std::complex<long long>;

long long direction(point& pi, point& pj, point& pk)
{
	point x = pk - pi;
	point y = pj - pi;
	return (std::conj(x) * y).imag();
}

bool on_segment(point pi, point pj, point pk)
{
	long long min_x = std::min(pi.real(), pj.real());
	long long max_x = std::max(pi.real(), pj.real());
	long long min_y = std::min(pi.imag(), pj.imag());
	long long max_y = std::max(pi.imag(), pj.imag());
	if (min_x <= pk.real() && pk.real() <= max_x && min_y <= pk.imag() && pk.imag() <= max_y) {
		return true;
	}
	else {
		return false;
	}
}


bool segements_intersect(point& p1, point& p2, point& p3, point& p4)
{
	long long d1 = direction(p3, p4, p1);
	long long d2 = direction(p3, p4, p2);
	long long d3 = direction(p1, p2, p3);
	long long d4 = direction(p1, p2, p4);

	if (((d1 > 0 && d2 < 0) || (d1 < 0 && d2 > 0)) && ((d3 > 0 && d4 < 0) || (d3 < 0 && d4 > 0))) {
		return true;
	}
	else if (d1 == 0 && on_segment(p3, p4, p1)) {
		return true;
	}
	else if (d2 == 0 && on_segment(p3, p4, p2)) {
		return true;
	}
	else if (d3 == 0 && on_segment(p1, p2, p3)) {
		return true;
	}
	else if (d4 == 0 && on_segment(p1, p2, p4)) {
		return true;
	}
	else {
		return false;
	}
}

int main()
{
	point p1 = { 0,0 };
	point p2 = { 10,10 };
	point p3 = { 0,0 };
	point p4 = { 10,0 };
	if (segements_intersect(p1, p2, p3, p4)) {
		std::cout << "hi\n";
	}
}
