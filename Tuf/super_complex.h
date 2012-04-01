#ifndef PARENT_COPMLEX
#define PARENT_COPMLEX

#include <iostream>

class parent_complex {
public:
<<<<<<< HEAD

	virtual double GetRe() const = 0;
	virtual double GetIm() const = 0;
=======
	double re, im;
>>>>>>> 877dca99a80b638ecb9a7a6905f178de21f129cf

	virtual double mod() const = 0;
	virtual double arg() const = 0;

};

#endif