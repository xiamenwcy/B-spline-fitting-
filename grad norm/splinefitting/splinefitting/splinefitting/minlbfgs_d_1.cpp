#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "optimization.h"

using namespace alglib;
void function1_grad(const real_1d_array &x, double &func, real_1d_array &grad, void *ptr) 
{
	//
	// this callback calculates f(x0,x1) = 100*(x0+3)^4 + (x1-3)^4
	// and its derivatives df/d0 and df/dx1
	//
	func = 100*pow(x[0]+3,4) + pow(x[1]-3,4);
	grad[0] = 400*pow(x[0]+3,3);
	grad[1] = 4*pow(x[1]-3,3);
}

int main(int argc, char **argv)
{
	//
	// This example demonstrates minimization of f(x,y) = 100*(x+3)^4+(y-3)^4
	// using LBFGS method.
	//
	real_1d_array x = "[0,0]";
	double epsg = 0.0000000001;
	double epsf = 0;
	double epsx = 0;
	ae_int_t maxits = 0;
	minlbfgsstate state;
	minlbfgsreport rep;

	minlbfgscreate(1, x, state);
	minlbfgssetcond(state, epsg, epsf, epsx, maxits);
	alglib::minlbfgsoptimize(state, function1_grad);
	minlbfgsresults(state, x, rep);

	printf("%d\n", int(rep.terminationtype)); // EXPECTED: 4
	printf("%s\n", x.tostring(2).c_str()); // EXPECTED: [-3,3]
	return 0;
}