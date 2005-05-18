#ifndef FRACTAL_H
#define FRACTAL_H

/* 
	Some noise and Fractal functions.
	These are based on the functions given in noises.h written by
	Larry Gritz and distributed with BMRT. see www.bmrt.org
	Used with permission.
*/

#include "shrimp_util.h"

#ifndef snoise
/*
 * Signed noise -- the original Perlin kind with range (-1,1) We prefer
 * signed noise to regular noise mostly because its average is zero.
 * We define three simple macros:
 *   snoise(p) - Perlin noise on either a 1-D (float) or 3-D (point) domain.
 *   snoisexy(x,y) - Perlin noise on a 2-D(float, float), or 4-D(point, float) domain.
 *   vsnoise(p) - vector-valued Perlin noise on either 1-D or 3-D domain.
 *   vsnoisexy(x,y) - vector-valued Perlin noise on a 2D or 4D domain.
 */
#define snoise(p) (2 * (float noise(p)) - 1)
#define snoisexy(x,y) (2 * (float noise(x,y)) - 1)
#define vsnoise(p) (2 * (vector noise(p)) - 1)
#define vsnoisexy(x,y) (2 * (vector noise(x,y)) - 1)
#endif

/* If we know the filter size, we can crudely antialias snoise by fading
 * to its average value at approximately the Nyquist limit.
 */
#define filteredsnoise(p,width) (snoise(p) * (1-smoothstep (0.2,0.75,width)))
#define filteredsnoisexy(x,y,width) (snoisexy(x,y) * (1-smoothstep (0.2,0.75,width)))
#define filteredvsnoise(p,width) (vsnoise(p) * (1-smoothstep (0.2,0.75,width)))
#define filteredvsnoisexy(x,y,width) (vsnoisexy(x,y) * (1-smoothstep (0.2,0.75,width)))


/* Having filteredsnoise leads easily to an antialiased version of fBm. */
float fBm( point p; float filtwidth;
           uniform float maxoctaves, lacunarity, gain )
{
    uniform float i;
    uniform float amp = 1;
    varying point pp = p;
    varying float sum = 0, fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * filteredsnoise (pp, fw);
	amp *= gain;  pp *= lacunarity;  fw *= lacunarity;
    }
    return sum;
}

float fBm( float x, filtwidth;
			uniform float maxoctaves, lacunarity, gain )
{
    uniform float i;
    uniform float amp = 1;
    varying float xx = x;
    varying float sum = 0, fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * filteredsnoise (xx, fw);
	amp *= gain;  xx *= lacunarity;  fw *= lacunarity;
    }
    return sum;
}


float fBm( float x, y, filtwidth;
			uniform float maxoctaves, lacunarity, gain )
{
    uniform float i;
    uniform float amp = 1;
    varying float xx = x;
    varying float yy = y;
    varying float sum = 0, fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * filteredsnoisexy (xx, yy, fw);
	amp *= gain;  
	xx *= lacunarity;  yy *= lacunarity;
	fw *= lacunarity;
    }
    return sum;
}


float fBm( point p; float t, filtwidth;
			uniform float maxoctaves, lacunarity, gain )
{
    uniform float i;
    uniform float amp = 1;
    varying point pp = p;
    varying float tt = t;
    varying float sum = 0, fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * filteredsnoisexy (pp, tt, fw);
	amp *= gain;  
	pp *= lacunarity;  tt *= lacunarity;
	fw *= lacunarity;
    }
    return sum;
}

/* Typical use of fBm: 
#define fBm_default(p)  fBm (p, sqrt(area(p)), 4, 2, 0.5)
*/

/* A vector-valued antialiased fBm. */
vector
vfBm (point p; float filtwidth;
      uniform float maxoctaves, lacunarity, gain)
{
    uniform float i;
    uniform float amp = 1;
    varying point pp = p;
    varying vector sum = 0;
    varying float fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
	sum += amp * filteredvsnoise (pp, fw);
	amp *= gain;  pp *= lacunarity;  fw *= lacunarity;
    }
    return sum;
}

vector
vfBm (float x, filtwidth;
      uniform float maxoctaves, lacunarity, gain)
{
    uniform float i;
    uniform float amp = 1;
    varying float xx = x;
    varying vector sum = 0;
    varying float fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
	sum += amp * filteredvsnoise (xx, fw);
	amp *= gain;  xx *= lacunarity;  fw *= lacunarity;
    }
    return sum;
}

vector
vfBm (float x, y, filtwidth;
      uniform float maxoctaves, lacunarity, gain)
{
    uniform float i;
    uniform float amp = 1;
    varying float xx = x;
    varying float yy = y;
    varying vector sum = 0;
    varying float fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
	sum += amp * filteredvsnoisexy (xx, yy, fw);
	amp *= gain;  
	xx *= lacunarity; yy *= lacunarity;  
	fw *= lacunarity;
    }
    return sum;
}

vector
vfBm (point p; float t, filtwidth;
      uniform float maxoctaves, lacunarity, gain)
{
    uniform float i;
    uniform float amp = 1;
    varying point pp = p;
    varying float tt = t;
    varying vector sum = 0;
    varying float fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
	sum += amp * filteredvsnoisexy (pp, tt, fw);
	amp *= gain;  
	pp *= lacunarity;  tt *= lacunarity;
	fw *= lacunarity;
    }
    return sum;
}


/* Typical use of vfBm: 
#define vfBm_default(p)  vfBm (p, sqrt(area(p)), 4, 2, 0.5)
*/


/* The stuff that Ken Musgrave calls "VLNoise" */
#define VLNoise(Pt,scale) (snoise(vsnoise(Pt)*scale+Pt))
#define VLNoisexy(x,y,scale)(snoisexy(vsnoise(x)*scale+x,vsnoise(y)*scale+y))
#define filteredVLNoise(Pt,fwidth,scale) \
            (filteredsnoise(filteredvsnoise(Pt,fwidth)*scale+Pt,fwidth))
#define filteredVLNoisexy(x,y,fwidth,scale) \
			(filteredsnoisexy(filteredsnoise(x,fwidth)*scale+x,\
			filteredsnoise(y,fwidth)*scale+y,fwidth))

float
VLfBm (point p; float filtwidth;
       uniform float maxoctaves, lacunarity, gain, scale)
{
    uniform float i;
    uniform float amp = 1;
    varying point pp = p;
    varying float sum = 0;
    varying float fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * filteredVLNoise (pp, fw, scale);
	amp *= gain;  pp *= lacunarity;  fw *= lacunarity;
    }
    return sum;
}

float
VLfBm (float x, filtwidth;
       uniform float maxoctaves, lacunarity, gain, scale)
{
    uniform float i;
    uniform float amp = 1;
    varying float xx = x;
    varying float sum = 0;
    varying float fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * filteredVLNoise (xx, fw, scale);
	amp *= gain;  xx *= lacunarity;  fw *= lacunarity;
    }
    return sum;
}

float
VLfBm (float x, y, filtwidth;
       uniform float maxoctaves, lacunarity, gain, scale)
{
    uniform float i;
    uniform float amp = 1;
    varying float xx = x;
    varying float yy = y;
    varying float sum = 0;
    varying float fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * filteredVLNoisexy (xx, yy, fw, scale);
	amp *= gain;  
	xx *= lacunarity; yy *= lacunarity;  
	fw *= lacunarity;
    }
    return sum;
}

float
VLfBm (point p; float t, filtwidth;
       uniform float maxoctaves, lacunarity, gain, scale)
{
    uniform float i;
    uniform float amp = 1;
    varying point pp = p;
    varying float tt = t;
    varying float sum = 0;
    varying float fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * filteredVLNoisexy (pp, tt, fw, scale);
	amp *= gain;  
	pp *= lacunarity; tt *= lacunarity; 
	fw *= lacunarity;
    }
    return sum;
}


/* Typical use of vfBm: 
#define VLfBm_default(p)      VLfBm (p, sqrt(area(p)), 4, 2, 0.5, 1.0)
*/



/* Antialiased turbulence.  Watch out -- the abs() call introduces infinite
 * frequency content, which makes our antialiasing efforts much trickier!
 */
float turbulence (point p; float filtwidth;
                  uniform float maxoctaves, lacunarity, gain)
{
    uniform float i;
    uniform float amp = 1;
    varying point pp = p;
    varying float sum = 0, fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * abs(filteredsnoise (pp, fw));
	amp *= gain;  pp *= lacunarity;  fw *= lacunarity;
    }
    return sum;
}

float turbulence (float x, filtwidth;
                  uniform float maxoctaves, lacunarity, gain)
{
    uniform float i;
    uniform float amp = 1;
    varying float xx = x;
    varying float sum = 0, fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * abs(filteredsnoise (xx, fw));
	amp *= gain;  xx *= lacunarity;  fw *= lacunarity;
    }
    return sum;
}

float turbulence (float x, y, filtwidth;
                  uniform float maxoctaves, lacunarity, gain)
{
    uniform float i;
    uniform float amp = 1;
    varying float xx = x;
    varying float yy = y;
    varying float sum = 0, fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * abs(filteredsnoisexy (xx, yy, fw));
	amp *= gain;  
	xx *= lacunarity; yy *= lacunarity;
	fw *= lacunarity;
    }
    return sum;
}

float turbulence (point p; float t, filtwidth;
                  uniform float maxoctaves, lacunarity, gain)
{
    uniform float i;
    uniform float amp = 1;
    varying point pp = p;
    varying float tt = t;
    varying float sum = 0, fw = filtwidth;

    for (i = 0;  i < maxoctaves && fw < 1.0;  i += 1) {
#pragma nolint
	sum += amp * abs(filteredsnoisexy (pp, tt, fw));
	amp *= gain;  
	pp *= lacunarity; tt *= lacunarity;  
	fw *= lacunarity;
    }
    return sum;
}

/* Typical use of turbulence: 
#define turbulence_default(p)  turbulence (p, sqrt(area(p)), 4, 2, 0.5)
*/


/* Ken Musgrave's Ridged MultiFractal 
   For an explanation see "Texturing and Modelling" chap 9
*/ 
float Ridged( 	point p; 
				float filtwidth;
				uniform float maxoctaves, lacunarity, offset, gain )
{
	uniform float i;
	uniform float amp = 1.0;
	varying float value = 0, signal;
	varying point pp = p;
	varying float fw = filtwidth, weight = 1.0;

	for( i = 0; i < maxoctaves && fw < 1.0; i += 1 )
	{
		signal = abs( filteredsnoise( pp, fw ) );
		signal = offset - signal;
		signal *= signal;
		signal *= weight;
		value += signal * amp;
		amp *= gain;
		pp *= lacunarity; fw *= lacunarity;
		weight = signal * 2.0;
		weight = clamp( weight, 0.0, 1.0 );

	}

	return ( value );
}

float Ridged( 	float x, filtwidth;
				uniform float maxoctaves, lacunarity, offset, gain )
{
	uniform float i;
	uniform float amp = 1.0;
	varying float value = 0, signal;
	varying float xx = x;
	varying float fw = filtwidth, weight = 1.0;

	for( i = 0; i < maxoctaves && fw < 1.0; i += 1 )
	{
		signal = abs( filteredsnoise( xx, fw ) );
		signal = offset - signal;
		signal *= signal;
		signal *= weight;
		value += signal * amp;
		amp *= gain;
		xx *= lacunarity; fw *= lacunarity;
		weight = signal * 2.0;
		weight = clamp( weight, 0.0, 1.0 );

	}

	return ( value );
}
float Ridged( 	float x, y, filtwidth;
				uniform float maxoctaves, lacunarity, offset, gain )
{
	uniform float i;
	uniform float amp = 1.0;
	varying float value = 0, signal;
	varying float xx = x;
	varying float yy = y;
	varying float fw = filtwidth, weight = 1.0;

	for( i = 0; i < maxoctaves && fw < 1.0; i += 1 )
	{
		signal = abs( filteredsnoisexy( xx, yy, fw ) );
		signal = offset - signal;
		signal *= signal;
		signal *= weight;
		value += signal * amp;
		amp *= gain;
		xx *= lacunarity; yy *= lacunarity;
		fw *= lacunarity;
		weight = signal * 2.0;
		weight = clamp( weight, 0.0, 1.0 );

	}

	return ( value );
}
float Ridged( 	point p; float t, filtwidth;
				uniform float maxoctaves, lacunarity, offset, gain )
{
	uniform float i;
	uniform float amp = 1.0;
	varying float value = 0, signal;
	varying point pp = p;
	varying float tt = t;
	varying float fw = filtwidth, weight = 1.0;

	for( i = 0; i < maxoctaves && fw < 1.0; i += 1 )
	{
		signal = abs( filteredsnoisexy( pp, tt, fw ) );
		signal = offset - signal;
		signal *= signal;
		signal *= weight;
		value += signal * amp;
		amp *= gain;
		pp *= lacunarity; tt *= lacunarity;
		fw *= lacunarity;
		weight = signal * 2.0;
		weight = clamp( weight, 0.0, 1.0 );

	}

	return ( value );
}

/* Typical use of ridged: 
#define ridged_default(p)  ridged (p, sqrt(area(p)), 4, 2, 0.7, 0.5)
*/


#endif
