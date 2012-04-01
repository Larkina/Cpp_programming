#ifndef POLAR
#define POLAR

#include <iostream>
#include "super_complex.h"
#include "complex_coord.h"

class complex_polar: public parent_complex {
	void update_re_and_im();
public:
	double r, fi, re, im;
	complex_polar(double _re, double _im);
	complex_polar(double _re);
	complex_polar(const complex_coord& a);
	complex_polar();

	friend complex_polar operator+(const complex_polar& a, const complex_polar& b);
	friend complex_polar operator-(const complex_polar& a, const complex_polar& b);
	friend complex_polar operator*(const complex_polar& a, const complex_polar& b);
	friend complex_polar operator/(const complex_polar& a, const complex_polar& b);

	friend complex_polar operator+=(complex_polar& a, const complex_polar& b);
	friend complex_polar operator-=(complex_polar& a, const complex_polar& b);
	friend complex_polar operator*=(complex_polar& a, const complex_polar& b);
	friend complex_polar operator/=(complex_polar& a, const complex_polar& b);

	friend complex_polar operator-(complex_polar& a);

	friend bool operator==(const complex_polar& a, const complex_polar& b);
	friend bool operator!=(const complex_polar& a, const complex_polar& b);

	friend std::ostream& operator<<(std::ostream& s, const complex_polar& a);

	double mod() const;
	double arg() const;

};

#endif