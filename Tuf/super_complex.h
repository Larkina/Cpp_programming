#ifndef PARENT_COPMLEX
#define PARENT_COPMLEX

#include <iostream>

class parent_complex {
public:
	double re, im;

	virtual double mod() const = 0;
	virtual double arg() const = 0;

};

#endif