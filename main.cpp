#include <iostream>
#include <cmath>
#include <iomanip>

int main(int argc, char** argv)
{
	double a = 3., b = 1.e9, c = 5.;
	double d = b * b - 4 * a * c;
	double r1 = (- b - sqrt(d)) / 2. * a;
	double r2 = (- b + sqrt(d)) / 2. * a;
	std::cout << std::setprecision(10) << r1 << "\n";
	std::cout << r2 << "\n";
	return 0;
}
