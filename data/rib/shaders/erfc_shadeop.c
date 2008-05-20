#include <stdio.h>
#include <math.h>
#include "shadeop.h"

/* Quick shadeop to access glibc's complementary error function. For point
 * type variables, double precision, float for float variables. */

SHADEOP_TABLE(erfc) =
{
	{ "float f_erfc( float )", "erfc_init", "erfc_cleanup"},
	{ "point p_erfc( point )", "erfc_init", "erfc_cleanup"},
	{ "vector p_erfc( vector )", "erfc_init", "erfc_cleanup"},
	{ "normal p_erfc( normal )", "erfc_init", "erfc_cleanup"},
	{ "" }
};

SHADEOP_INIT( erfc_init )
{
	return 0x0; /* No init data */
}

/* Returns the complementary error function. Argv[0]=pointer to result */

SHADEOP ( f_erfc )
{
	/* pointer to result */
	float *result = ( float* ) argv[0];
	/* pointer to 1st argument */
	float *theta = ( float* ) argv[1];
	*result = ( float ) erfcf( *theta );

	return 0;
}

SHADEOP ( p_erfc )
{
	float *result = ( float* ) argv[0];
	float *theta = ( float* ) argv[1];
	double pp[3];
	for (int i = 0; i <= 2; ++i) {
		pp[i] = ( double ) theta[i];
		result[i] = erfc( pp[i] );
	}
	return 0;
}

SHADEOP_CLEANUP( erfc_cleanup )
{
	/* do nothing */
}

