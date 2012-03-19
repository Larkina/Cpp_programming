#include <iostream>
#include <math.h>
#include "complex_coord.h"
#include "polar.h"
#include "super_complex.h"

using namespace std;

#define EPS 0.000000001
#define M_PI_2 1.57079632679489661923
#define test(a, b, c) m_test(a, b, c, __LINE__)
#define test2(a, b) m_test(a, b, __LINE__)
#define Complex complex_polar

int tests_count = 0, correct;

void print_msg_and_inc_tests_count(bool res, int line){
	tests_count++;
	correct += res;
	cout << "Test: " << tests_count << (res ? " OK   " : " FAIL ") 
		 << " at line: " << line << endl;
}

void print_result(){
	cout << correct << " - PASSED " << endl;
	cout << tests_count - correct << " - FAILED " << endl;
	int t;
	cin >> t;
}

void m_test(const Complex &a, double ans_re, double ans_im, int line){
	print_msg_and_inc_tests_count(abs(a.re - ans_re) <= EPS && abs(a.im - ans_im) <= EPS, line);
}

void m_test(double res, double ans, int line){
	print_msg_and_inc_tests_count(abs(res - ans) < EPS, line);
}

int main(){
	//parent_complex *a = new complex_coord(8, 1);
	Complex a(8, 1), b(2, -3), c(5, 5);
	//plus
	test(a + 22, 30, 1);
	test(22 + a, 30, 1);
	test(a + b, 10, -2);
	//minus
	test(-a, -8, -1);
	test(b - 3, -1, -3);
	test(3 - b, 1, 3);
	test(a - b, 6, 4);
	test(b - a, -6, -4);
	//multiply
	test(a * b, 19, -22);
	test(b * a, 19, -22);
	test(3 * a, 24, 3);
	test(-2 * b, -4, 6);
	// division
	test(a / b, 1, 2);
	test(b / a, 1./5, -26./65);
	test(a / 4, 2, 1./4);
	test(5 / b, 10./13, 15./13);
	test(a / 0, 0, 0);
	// ?=
	test(c += b, 7, 2);
	test(c -= a, -1, 1);
	test(c += 1, 0, 1);
	test(c -= -2, 2, 1);
	test(c /= 2, 1, 0.5);
	test(c *= 4, 4, 2);
	test(c *= a, 30, 20);
	test(c /= b, 0, 10);
	// arg, mod
	test2(c.mod(), 10);
	test2(c.arg(), M_PI_2);
	test2(a.mod(), sqrt(65.));
	test2(b.mod(), sqrt(13.));
	// eq
	test2(a == b, 0);
	test2(Complex(0, 10) == c, 1);
	test2(a == c, 0);
	test2(c != b, 1);

	Complex d;
	test2(d.arg(), 0);
	test2(d.mod(), 0);
	d += c * c + a * a + b * b + 42;
	test(d, 0, 4);

	test(7 / b * 6 / a + Complex(0, 4) * c, -33002./845, 924./845);
	test((a + b + c)/(a * b * c), 186./4225, -7./4225);

	cout << a << b << c;

	print_result();

	return 0;
}
