#include "polar.h"
#include <iostream>
#include <math.h>

using namespace std;

#define EPS 0.000000001

complex_polar::complex_polar(double _re, double _im): re(_re), im(_im) {
	r = sqrt(re * re + im * im);
	fi = atan2(im, re);
}

complex_polar::complex_polar(double _re): re(_re), im(0) {
	fi = atan2(im, re);
	r = abs(re);
}

complex_polar::complex_polar(): r(0), fi(0), re(0), im(0) {}

complex_polar::complex_polar(const complex_coord& a){
	fi = a.arg();
	r = a.mod();
	re = a.re;
	im = a.im;
}

void complex_polar::update_re_and_im(){
	re = r * cos(fi);
	im = r * sin(fi);
}

complex_polar operator+(const complex_polar& a, const complex_polar& b){
	complex_coord t(a.r * cos(a.fi), a.r * sin(a.fi)), t1(b.r * cos(b.fi), b.r * sin(b.fi)); 
	return t + t1;
}

complex_polar operator-(const complex_polar& a, const complex_polar& b){
	complex_coord t(a.r * cos(a.fi), a.r * sin(a.fi)), t1(b.r * cos(b.fi), b.r * sin(b.fi)); 
	return t - t1;
}

complex_polar operator*(const complex_polar& a, const complex_polar& b){
	complex_polar t;
	t.r = a.r * b.r;
	t.fi = a.fi + b.fi;
	t.update_re_and_im();
	return t;
}

complex_polar operator*(double a, const complex_polar& b){
	return complex_polar(a) * b;
}

complex_polar operator*(const complex_polar& b, double a){
	return complex_polar(a) * b;
}

complex_polar operator/(const complex_polar& a, const complex_polar& b){
	if (b.r == 0)
		return complex_polar();
	complex_polar t;
	t.r = a.r / b.r;
	t.fi = a.fi - b.fi;
	t.update_re_and_im();
	return t;
}

complex_polar operator/(double a, const complex_polar& b){
	return complex_polar(a) / b;
}

complex_polar operator/(const complex_polar& b, double a){
	return b / complex_polar(a);
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

complex_polar operator*=(complex_polar& a, double b){
	return a = a * b;
}

complex_polar operator/=(complex_polar& a, const complex_polar& b){
	return a = a / b;
}

complex_polar operator/=(complex_polar& a, double b){
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