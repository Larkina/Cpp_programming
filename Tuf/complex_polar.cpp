#include "complex_polar.h"
#include <iostream>
#include <math.h>

using namespace std;

#define EPS 0.000000001

complex_polar::complex_polar(double _re, double _im) {
	r = sqrt(_re * _re + _im * _im);
	fi = atan2(_im, _re);
}

complex_polar::complex_polar(double _re) {
	fi = atan2(0, _re);
	r = abs(_re);
}

complex_polar::complex_polar(): r(0), fi(0) {}

complex_polar::complex_polar(const complex_coord& a){
	fi = a.arg();
	r = a.mod();
}

double complex_polar::GetRe() const {
	return r * cos(fi);
}

double complex_polar::GetIm() const {
	return r * sin(fi);
}

complex_polar operator+(const complex_polar& a, const complex_polar& b){
	return complex_polar(a.GetRe() + b.GetRe(), a.GetIm() + b.GetIm());
}

complex_polar operator-(const complex_polar& a, const complex_polar& b){
	return complex_polar(a.GetRe() - b.GetRe(), a.GetIm() - b.GetIm());
}

complex_polar operator*(const complex_polar& a, const complex_polar& b){
	complex_polar t;
	t.r = a.r * b.r;
	t.fi = a.fi + b.fi;
	return t;
}

complex_polar operator/(const complex_polar& a, const complex_polar& b){
	if (b.r == 0)
		return complex_polar();
	complex_polar t;
	t.r = a.r / b.r;
	t.fi = a.fi - b.fi;
	return t;
}

complex_polar operator+=(complex_polar& a, const complex_polar& b){
	return a = a + b;
}

complex_polar operator-=(complex_polar& a, const complex_polar& b){
	return a = a - b;
}

complex_polar operator*=(complex_polar& a, const complex_polar& b){
	return a = a * b;
}

complex_polar operator/=(complex_polar& a, const complex_polar& b){
	return a = a / b;
}

complex_polar operator-(complex_polar& a){
	return -1 * a;
}

bool operator==(const complex_polar& a, const complex_polar& b){
	return abs(a.r - b.r) <= EPS && abs(a.fi - b.fi) <= EPS;
}

bool operator!=(const complex_polar& a, const complex_polar& b){
	return !(a==b);
}

ostream& operator<<(ostream& s, const complex_polar& a){
	return s << "Radius: " << a.r << " Angle: " << a.fi << endl;
}

double complex_polar::mod() const {
	return r;
}

double complex_polar::arg()const{
	return fi;
}
