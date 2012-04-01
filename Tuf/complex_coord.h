#ifndef COMPLEX_COORD 
#define COMPLEX_COORD

#include <iostream>
#include "super_complex.h"

class complex_coord: public parent_complex {
public:
	double re, im;
	complex_coord(double _re, double _im);
	complex_coord(double _re);
	complex_coord();

	virtual double GetRe() const;
	virtual double GetIm() const;

	friend complex_coord operator+(const complex_coord& a, const complex_coord& b);
	friend complex_coord operator-(const complex_coord& a, const complex_coord& b);
	friend complex_coord operator*(const complex_coord& a, const complex_coord& b);
	friend complex_coord operator/(const complex_coord& a, const complex_coord& b);

	friend complex_coord operator+=(complex_coord& a, const complex_coord& b);
	friend complex_coord operator-=(complex_coord& a, const complex_coord& b);
	friend complex_coord operator*=(complex_coord& a, const complex_coord& b);
	friend complex_coord operator/=(complex_coord& a, const complex_coord& b);

	friend complex_coord operator-(complex_coord& a);

	friend bool operator==(const complex_coord& a, const complex_coord& b);
	friend bool operator!=(const complex_coord& a, const complex_coord& b);

	friend std::ostream& operator<<(std::ostream& s, const complex_coord& a);

	virtual double mod() const;
	virtual double arg() const;

};

#endif