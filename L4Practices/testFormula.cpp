#define _USE_MATH_DEFINES

#include <iostream>
#include <stdio.h>
#include<string>
#include <cmath>


using namespace std;

void testFormula(double x) {
	double eps;
	eps = abs(2 * pow(cos(x), 2) - 1 - cos(2 * x));
	printf("The Formula 2(cos(x)^2 - 1 = cos(2x) is %s, with eps = %4.2f \n", ((eps < 0.01)? "valid" : "invalid"), eps);

	eps = pow(sin(x), 4) + 2 * pow(cos(x), 2) - 2 * pow(sin(x), 2) - cos(2 * x) - pow(cos(x), 4);
	printf("The Formula (cos(x))^4 + 2(cos(x))^2 - 2(sin(x))^2 - cos(2x) = (cos(x))^4 is %s, with eps = %4.2f \n", ((eps < 0.01) ? "valid" : "invalid"), eps);

	eps = abs(4 * pow(cos(x), 3) + 3 * cos(x) - cos(3 * x));
	printf("The Formula 4(cos(x))^3 + 3cos(x) = cos(3x) is %s, with eps = %4.2f \n", ((eps < 0.01) ? "valid" : "invalid"), eps);

	double RHS = 0;
	for (int k = 0; k <= 100; ++k) {
		RHS += (2 * pow(-1, k) * pow(3, -k + 1 / 2)) / (2 * k + 1);
	}
	eps = abs(M_PI - RHS);
	printf("The Formula PI = SUM_0_to_inf_{(2(-1)^k * 3^(-k+1/2))/(2k+1)} is %s, with eps = %4.2f \n", ((eps < 0.1) ? "valid" : "invalid"), eps);

}