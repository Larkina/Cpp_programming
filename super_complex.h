#ifndef PARENT_COPMLEX
#define PARENT_COPMLEX

#include <iostream>

class parent_complex {
public:

	virtual double GetRe() const = 0;
	virtual double GetIm() const = 0;

	virtual double mod() const = 0;
	virtual double arg() const = 0;

};

#endif