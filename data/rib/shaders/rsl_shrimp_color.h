#ifndef SHRIMP_COLOR_H
#define SHRIMP_COLOR_H 1

#include "rsl_shrimp_helpers.h"

/* Set of functions to deal with color conversion, and some color related
 * utilities. Conversion from RGB to spec6 and vice-versa, taken from
 * Mario Marengo's VEX glass shader. */

#define LAMBDA  { 642, 580, 529, 491, 464, 439 } // RYGCBV wavelengths

////////////////////////////////////////////////////////////////////////////////
// Convert rgb to rygcbv
void
rgbToSpec6(
			color rgb;
			output varying float rygcbv[6];
		)
{
#if RENDERER == aqsis // can only access components with (xyz)comp
	float R = comp(rgb, 0), G = comp(rgb, 1), B = comp(rgb, 2);
	float R2 = SQR(R), G2 = SQR(G), B2 = SQR(B);
	// can't seem to be able to assign to arrays no matter what O_o
	// as of 1.4.2
	rygcbv[0] = R * .5; rygcbv[1] = (R2 + G2 - B) * w;
	rygcbv[2] = G * .5; rygcbv[3] = (G2 + B2 - R) * w;
	rygcbv[4] = B * .5; rygcbv[5] = (B2 + R2 - G) * w;
#else
	float R2 = rgb[0] * 2, G2 = rgb[1] * 2, B2 = rgb[2] * 2, w = 1/6;
	rygcbv[0] = rgb[0] * .5; rygcbv[1] = (R2 + G2 - rgb[2]) * w;
	rygcbv[2] = rgb[1] * .5; rygcbv[3] = (G2 + B2 - rgb[0]) * w;
	rygcbv[4] = rgb[2] * .5; rygcbv[5] = (B2 + R2 - rgb[1]) * w;
#endif
}

////////////////////////////////////////////////////////////////////////////////
// convert rygcbv to rgb
color
spec6ToRgb(
			float rygcbv[6];
		)
{
	float y2 = rygcbv[1] * 2, c2 = rygcbv[3] * 2, v2 = rygcbv[5] * 2, w = 1/3;
	return color(	rygcbv[0] + (v2 + y2 - rygcbv[3]) * w,
					rygcbv[2] + (y2 + c2 - rygcbv[5]) * w,
					rygcbv[4] + (c2 + v2 - rygcbv[1]) * w );
}

////////////////////////////////////////////////////////////////////////////////
#endif /* SHRIMP_COLOR_H */

