// GNU Scientific Library, release 2.7 Book chapter 38
// https://www.gnu.org/software/gsl/doc/html/multiroots.html
// g++ main.cpp -o main -lgsl -lcblas
// The multidimensional solver = solving nonlinear system with n equations and n unknowns
// This program solves the Rosenbrock system of equations

#include <stdlib.h>
#include <stdio.h>
#include <gsl/gsl_vector.h>
#include <gsl/gsl_multiroots.h>

struct rparams
{
	double a;
	double b;
};

// f1(x,y) = x^4 + y^4
// f2(x,y) = x^4 - y^4
// the solution of this system is (x,y)=(0,0)
int rosenbrock_f (const gsl_vector * x, void *params, gsl_vector * f)
{
	const double x0 = gsl_vector_get (x, 0);
	const double x1 = gsl_vector_get (x, 1);

	//const double y0 = 4*pow(x0,3) ;
	//const double y1 = 4*pow(x1,3);

	const double y0 = 4*pow(x0,3) ;
	const double y1 = -4*pow(x1,3);

	gsl_vector_set (f, 0, y0);
	gsl_vector_set (f, 1, y1);

	return GSL_SUCCESS;
}

int print_state (size_t iter, gsl_multiroot_fsolver * s)
{
	printf ("n = %3u x = % .3f y = % .3f " "\t f1(x,y) = % .3e f2(x,y) = % .3e\n",
	iter,
	gsl_vector_get (s->x, 0),
	gsl_vector_get (s->x, 1),
	gsl_vector_get (s->f, 0),
	gsl_vector_get (s->f, 1));
	return 0;
}

int main (void)
{
	const gsl_multiroot_fsolver_type *T;
	gsl_multiroot_fsolver *s;

	int status;
	size_t i, iter = 0;

	const size_t n = 2;
	struct rparams p = {1.0, 10.0};
	gsl_multiroot_function f = {&rosenbrock_f, n, &p};

	//double x_init[2] = {-10.0, 0.0};
	//double x_init[2] = {-3.0, 1.0};	
	//double x_init[2] = {0.0, 5.0};
	double x_init[2] = {5.0, 0.0};
	gsl_vector *x = gsl_vector_alloc (n);

	gsl_vector_set (x, 0, x_init[0]);
	gsl_vector_set (x, 1, x_init[1]);

	T = gsl_multiroot_fsolver_hybrids;
	s = gsl_multiroot_fsolver_alloc (T, 2);
	gsl_multiroot_fsolver_set (s, &f, x);

	print_state (iter, s);

	do
	{
		iter++;
		status = gsl_multiroot_fsolver_iterate (s);

		print_state (iter, s);

	if (status)   /* check if solver is stuck */
		break;

	status = gsl_multiroot_test_residual (s->f, 1e-7);
	}
	while (status == GSL_CONTINUE && iter < 1000);

	printf ("status = %s\n", gsl_strerror (status));

	gsl_multiroot_fsolver_free (s);
	gsl_vector_free (x);

	return 0;
}