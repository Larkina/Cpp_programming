#include "complex_coord.h"
#include <iostream>
#include <math.h>

using namespace std;

complex_coord::complex_coord(double _re, double _im): re(_re), im(_im) {}

complex_coord::complex_coord(double _re): re(_re), im(0) {}

complex_coord::complex_coord(): re(0), im(0) {}

complex_coord operator+(const complex_coord& a, const complex_coord& b){
	return complex_coord(a.re + b.re, a.im + b.im);
}

complex_coord operator+(double a, const complex_coord& b){
	return complex_coord(a + b.re, b.im);	
}

complex_coord operator+(const complex_coord& b, double a){
	return a + b;	
}

complex_coord operator-(const complex_coord& a, const complex_coord& b){
	return complex_coord(a.re - b.re, a.im - b.im);
}

complex_coord operator-(double a, const complex_coord& b){
	return complex_coord(a - b.re, -b.im);	
}

complex_coord operator-(const complex_coord& b, double a){
	return complex_coord(b.re - a, b.im);	
}

complex_coord operator*(const complex_coord& a, const complex_coord& b){
	return complex_coord(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
}

complex_coord operator*(double a, const complex_coord& b){
	return complex_coord(a * b.re,  a * b.im);	
}

complex_coord operator*(const complex_coord& b, double a){
	return a * b;	
}

complex_coord operator/(const complex_coord& a, const complex_coord& b){
	return complex_coord((a.re * b.re + a.im * b.im)/(b.re * b.re + b.im * b.im), 
				   (a.im * b.re - a.re * b.im)/(b.re * b.re + b.im * b.im));
}

complex_coord operator/(double a, const complex_coord& b){
	return complex_coord(a)/b;	
}

complex_coord operator/(const complex_coord& b, double a){
	if (a == 0){
		cout << "Division by zero!" << endl;
		return complex_coord();
	}
	return complex_coord(b.re / a, b.im / a);	
}

complex_coord operator+=(complex_coord& a, const complex_coord& b){
	return a = a + b;
}

complex_coord operator-=(complex_coord& a, const complex_coord& b){
	return a = a - b;
}

complex_coord operator*=(complex_coord& a, const complex_coord& b){
	return a = a * b;
}

complex_coord operator*=(complex_coord& a, double b){
	return a = a * b;
}

complex_coord operator/=(complex_coord& a, const complex_coord& b){
	return a = a / b;
}

complex_coord operator/=(complex_coord& a, double b){
	return a = a / b;
}

complex_coord operator-(complex_coord& a){
	return -1 * a;
}

bool operator==(const complex_coord& a, const complex_coord& b){
	return a.im == b.im && a.re == b.re;
}

bool operator!=(const complex_coord& a, const complex_coord& b){
	return a.im != b.im || a.re != b.re;
}

ostream& operator<<(ostream& s, const complex_coord& a){
	return s << "Re: " << a.re << " Im: " << a.im << endl;
}

double complex_coord::mod() const {
	return sqrt(re * re + im * im);
}

double complex_coord::arg()const{
	return atan2(im, re);
}
