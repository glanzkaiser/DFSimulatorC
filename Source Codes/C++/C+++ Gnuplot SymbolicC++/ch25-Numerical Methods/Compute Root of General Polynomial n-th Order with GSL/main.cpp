// GNU Scientific Library, release 2.7 Book
// g++ main.cpp -o main -lgsl -lcblas
// Compute roots of the general polynomial

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <gsl/gsl_poly.h>

using namespace std;

int main (void)
{
	int i;
	/* coefficients of P(x) = 5 - 5x^2 + 5x^4 */
	double a[5] = { 5, 0, -5, 0, 5 };
	double z[10];

	gsl_poly_complex_workspace * w = gsl_poly_complex_workspace_alloc(5);
	gsl_poly_complex_solve(a, 5, w, z);
	gsl_poly_complex_workspace_free(w);

	printf ("z | \t  Real \t \t \t | Complex \n");
	printf ("************************************************************\n");
	for (i=0; i < 4; i++)
	{
		printf ("z%d = %+ .20f \t %.20f\n",
				i, z[2*i], z[2*i+1] );
	}

	return 0;
}