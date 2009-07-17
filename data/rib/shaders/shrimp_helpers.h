#ifndef SHRIMP_HELPERS_H
	#define SHRIMP_HELPERS_H

#ifndef EPS
#define EPS 0.0001
#endif

#ifndef MINFILTWIDTH
#define MINFILTWIDTH 1.0e-6
#endif

#ifndef SQR
#define SQR(X)	( (X) * (X) )
#endif

#ifndef luminance
#define luminance(c)	comp(c,0)*0.299 + comp(c,1)*0.587 + comp(c,2)*.114
#endif

#define S_E		2.718281828459045
#define S_PI	3.141592653589793
#define S_PI_2	1.570796326794896
#define S_2PI	6.283185307179586
#define S_1_PI	0.318309886183790

/* for optional arguments to shadeops, blocks need to know if the optional
 * arguments are set, we just need a symbol UND(efined) */
#define UND		23

////////////////////////////////////////////////////////////////////////////////
/* Hyperbolic cosine */
float cosh( float theta; ) {
	return ( exp(theta) + exp(-theta) ) / 2;
}
/* Hyperbolic sine */
float sinh( float theta; ) {
	return ( exp(theta) - exp(-theta) ) / 2;
}
/* Hyperbolic tangent */
float tanh( float theta; ) {
	return (exp(theta) - exp(-theta)) / (exp(theta) + exp(-theta));
}

////////////////////////////////////////////////////////////////////////////////
/* 
 * Rotate the point (x,y) about the point (ox,oy) by theta radians
 * Returns the answer in (rx,ry)
 * */ 
////////////////////////////////////////////////////////////////////////////////

void 
rotate2d( float x, y, theta, ox, oy; 
          output float rx, ry; )
{
	float sint = sin(theta);
	float cost = cos(theta);
	rx = ( x - ox )*cost - ( y - oy )*sint + ox;
	ry = ( x - ox )*sint + ( y - oy )*cost + oy;
}

////////////////////////////////////////////////////////////////////////////////
/* 
 * boolean ops (from Perlin85)
 * */
////////////////////////////////////////////////////////////////////////////////

#define intersection( a, b )	( (a) * (b) )
#define union( a, b )			( (a) + (b) - (a)*(b) )
#define difference( a, b )		( (a) - (a)*(b) )
#define complement( a )			( 1 - (a) )
#define exclusiveor( a, b )		( difference( union( (a),(b) ), \
									intersection( (a),(b) ) ) ) 

////////////////////////////////////////////////////////////////////////////////
// From shrimp_util.h //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* 
 * shrimp_util.h
 *
 * Some small, commonly needed macros and functions.
 * These are based on, and replace, the similar functions found
 * in patterns.h by Larry Gritz as distributed with BMRT.
 * Some of the macros are also based on similar ones given in
 * rmannotes.sl by Steve May, or taken from Darwyn Peachey's chapter
 * in "Texturing and Modelleling" by Ebert et al.
 * */

/*
 * This is the same as mix except blend allows a non-scalar 3rd arg.
 * */

#define blend( a, b, x ) ( (a) * (1 - (x)) + (b) * (x) )

/*
 * The following 2 macros are useful in generating tiling patterns.
 * repeat transforms surface coords into coords in the current tile.
 * whichtile returns the number of the current tile.
 * */
#define repeat( x, freq )			( mod( (x) * (freq), 1 ) )
#define whichtile( x, freq )		( floor( (x) * (freq) ) )

/*
 * Adds offset to the point, but wraps around so 0<=x<=1
 * */
#define shift( x, offset )			( mod( (x) + (offset), 1 ) )

/* 
 * Just shorthand, but it makes things more readable
 * */
#define odd(x)						(mod((x), 2) == 1)
#define even(x)						(mod((x), 2) == 0) 

/*
 * Some definitions from rmannotes
 * */
#define pulse( a, b, x )				( step( a, x ) - step( b, x ) )
#define filteredpulse( a, b, x, dx )	( max( 0, ( min( (x-dx/2)+dx, b) - \
											max( x-dx/2, a)) / dx ) )
#define boxstep( a, b, x )			clamp( ( (x)-(a) ) / ( (b)-(a) ), 0, 1 )

/* uniformly distributed noise */
#define udn(x,lo,hi) (smoothstep(.25, .75, noise(x)) * ((hi) - (lo)) + (lo))
#define udn2(x,y,lo,hi) (smoothstep(.25, .75, noise(x,y)) * ((hi)-(lo))+(lo))

////////////////////////////////////////////////////////////////////////////////

#ifndef filterwidth
#	define filterwidth(x)  ( max( abs( Du(x)*du ) + abs( Dv(x)*dv ), \
			MINFILTWIDTH ) )
#endif

#ifndef filterwidthp
#	define filterwidthp(p) ( max( sqrt( area(p) ), MINFILTWIDTH ) )
#endif

#ifndef fadeout
#	define fadeout(g,g_avg,featuresize,fwidth) \
	( mix( g, g_avg, smoothstep( .2, .6, fwidth/featuresize)))
#endif

////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Schlick's fresnel approximation /////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

float schlickfresnel(
                        normal Nf;
                        vector Vf;
                        float ior;
        )
{
	float kr = ( ior - 1.0 ) / ( ior + 1.0 );
	kr *= kr;
	return kr + ( 1.0 - kr ) * pow( 1.0 - (Nf.Vf), 5);
}

////////////////////////////////////////////////////////////////////////////////
// Surface curvature shader, based on Mario Marengo's work from odforce.net ////
// based on Andreas Baerentzen paper ///////////////////////////////////////////
// http://www.imm.dtu.dk/~jab/curvature.ps /////////////////////////////////////
// Used with Mario's permission (thanks ;)) ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// This form of the quad eqn. was taken from
// http://mathworld.wolfram.com/QuadraticEquation.html
// It avoids numerical problems when b^2 > 4ac

void solvequad(
                float a, b, c;
                output float k1, k2;
        )
{
    float q = b * b - 4 * a * c;
    if ( q < 0 ) {
        k1 = 0;
        k2 = 0;
    }
    q = -.5 * ( b + sign(b) * sqrt(q));
    k1 = q / a;
    k2 = c / q;
}

/* note: tweak color mapping later */
color scurvature(
                    uniform string ctype;
                    float cmin, cmax;
                    uniform float greyscale;
                    normal Nn;
                    vector In;
        )
{
    normal Nf = faceforward( Nn, In );

    float result = 0;
    color out = color(0);
	extern point P;

    /* The needed partials */
    vector  Xu = Du(P),
			Xv = Dv(P),
			Xuu = Du(Xu),
			Xuv = Du(Xv),
			Xvv = Dv(Xv);

    /* Coefficients of the first fundamental form (I) */
    float   EE = Xu.Xu,
			FF = Xu.Xv,
			GG = Xv.Xv;

    /* Coefficients of the second fundamental form (II) */
    float   ee = Nf.Xuu,
			ff = Nf.Xuv,
			gg = Nf.Xvv;

    /* Coefficients for the quadeq. */
    float   dist = EE * GG - FF * FF;
    float   a = (ff * FF - ee * GG ) / dist,
			b = (gg * FF - ff * GG ) / dist,
			c = (ee * FF - ff * EE ) / dist,
			d = (ff * FF - gg * EE ) / dist;

    /* Solve for the Principal Curvatures (Kmin and Kmax) */
    float K1, K2;

    solvequad( 1, a + d, a * d - c * b, K1, K2 );
	
    float Kmin = min( K1, K2 );
    float Kmax = max( K1, K2 );

    /* Mean: H = (K1+K2)/2 or H=(1/2) ((eG-sfF+gE)/(EG-F^2))
	 * Gaussian K=K1*K2 or K = eg-f^2/EG-F^2
	 * */

    if ( ctype == "mean" ) {
        result = ( ee * GG - 2 * ff * FF + gg * EE ) / ( 2 * dist );
    } else if ( ctype == "amean" ) {
        result = abs( (ee * GG - 2 * ff * FF + gg * EE ) / ( 2 * dist ) );
    } else if ( ctype == "gauss" ) {
        result = ( ee * gg - ff * ff ) / dist;
    } else if ( ctype == "min" ) {
        result = Kmin;
    } else if( ctype == "max" ) {
        result = Kmax;
    } else { result = 0; } // no ctype

	/* greyscale or color */
    if ( greyscale == 1.0 ) {
        float g = 1 - spline( result, cmin, cmax, 0, 1 );
		out = color(g);
    } else {
		/* rgb */
		color c1 = color( 1, 0, 0 ),
			  c2 = color( 0, 1, 0 ),
			  c3 = color( 0, 0, 1 );
        out = spline( ( clamp( result, cmin, cmax ) - cmin ) / (cmax - cmin ),
                c1, .8 * c1, c2, .8 * c3, c3 );
    }

    return out;
}

////////////////////////////////////////////////////////////////////////////////
// extra helpers, from Larry Gritz's patterns.h ////////////////////////////////
// slightly tweaked for shrimp use, and we only want some functions in /////////
// particular. /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/************************************************************************
 * patterns.h - Some handy functions for various patterns.  Wherever
 *              possible, antialiased versions will also be given.
 *
 * Author: Larry Gritz (lg AT larrygritz DOT com)
 *
 * Reference:
 *   _Advanced RenderMan: Creating CGI for Motion Picture_, 
 *   by Anthony A. Apodaca and Larry Gritz, Morgan Kaufmann, 1999.
 *
 * $Revision: 1.2 $    $Date: 2003/12/24 06:18:06 $
 *
 ************************************************************************/

/* Antialiased abs().  
 * Compute the box filter of abs(t) from x-dx/2 to x+dx/2.
 * Hinges on the realization that the indefinite integral of abs(x) is 
 * sign(x) * 1/2 x*x;
 * */
float filteredabs (float x, dx)
{
    float integral (float t) {
	return sign(t) * 0.5 * t*t;
    }

    float x0 = x - 0.5*dx;
    float x1 = x0 + dx;
    return (integral(x1) - integral(x0)) / dx;
}

////////////////////////////////////////////////////////////////////////////////

/* Antialiased smoothstep(e0,e1,x).  
 * Compute the box filter of smoothstep(e0,e1,t) from x-dx/2 to x+dx/2.
 * Strategy: divide domain into 3 regions: t < e0, e0 <= t <= e1,
 * and t > e1.  Region 1 has integral 0.  Region 2 is computed by
 * analytically integrating smoothstep, which is -2t^3+3t^2.  Region 3
 * is trivially 1.
 * */
float filteredsmoothstep (float e0, e1, x, dx)
{
    float integral (float t) {
	return -0.5*t*t * (t*t - 2*t);
    }

    /* Compute x0, x1 bounding region of integration, and normalize so that
     * e0==0, e1==1 */
    float edgediff = e1 - e0;
    float x0 = (x-e0)/edgediff;
    float fw = dx / edgediff;
    x0 -= 0.5*fw;
    float x1 = x0 + fw;

    /* Region 1 always contributes nothing */
    float int = 0;
    /* Region 2 - compute integral in region between 0 and 1 */
    if (x0 < 1 && x1 > 0)
    	int += integral(min(x1,1)) - integral(max(x0,0));
    /* Region 3 - is 1.0 */
    if (x1 > 1)
    	int += x1-max(1,x0);
    return int / fw;
}

////////////////////////////////////////////////////////////////////////////////

/* A pulse train: a signal that repeats with a given period, and is
 * 0 when 0 <= mod(x,period) < edge, and 1 when mod(x,period) > edge.
 * */
float pulsetrain (float edge, period, x)
{
    return pulse (edge, period, mod(x,period));
}

////////////////////////////////////////////////////////////////////////////////

/* Filtered pulse train: it's not as simple as just returning the mod
 * of filteredpulse -- you have to take into account that the filter may
 * cover multiple pulses in the train.
 * Strategy: consider the function that is the integral of the pulse
 * train from 0 to x. Just subtract!
 * */

float filteredpulsetrain (float edge, period, x, dx)
{
    /* First, normalize so period == 1 and our domain of interest is > 0 */
    float w = dx/period;
    float x0 = x/period - w/2;
    float x1 = x0+w;
    float nedge = edge / period;   /* normalized edge value */

    /* Definite integral of normalized pulsetrain from 0 to t */
    float integral (float t) { 
        extern float nedge;
        return ((1-nedge)*floor(t) + max(0,t-floor(t)-nedge));
    }

    /* Now we want to integrate the normalized pulsetrain over [x0,x1] */
    return (integral(x1) - integral(x0)) / w;
}

////////////////////////////////////////////////////////////////////////////////

float
smoothpulse (float e0, e1, e2, e3, x)
{
    return smoothstep(e0,e1,x) - smoothstep(e2,e3,x);
}

////////////////////////////////////////////////////////////////////////////////

float
filteredsmoothpulse (float e0, e1, e2, e3, x, dx)
{
    return filteredsmoothstep(e0,e1,x,dx) - filteredsmoothstep(e2,e3,x,dx);
}

////////////////////////////////////////////////////////////////////////////////

/* A pulse train of smoothsteps: a signal that repeats with a given
 * period, and is 0 when 0 <= mod(x/period,1) < edge, and 1 when
 * mod(x/period,1) > edge.  
 * */

float smoothpulsetrain (float e0, e1, e2, e3, period, x)
{
    return smoothpulse (e0, e1, e2, e3, mod(x,period));
}

////////////////////////////////////////////////////////////////////////////////

/* varyEach takes a computed color, then tweaks each indexed item
 * separately to add some variation.  Hue, saturation, and lightness
 * are all independently controlled.  Hue adds, but saturation and
 * lightness multiply.
 * */

color varyEach (color Cin; float index, varyhue, varysat, varylum;)
{
    /* Convert to "hsl" space, it's more convenient */
    color Chsl = ctransform ("hsl", Cin);
    float hue = comp( Chsl, 0), sat = comp( Chsl, 1), lum = comp( Chsl, 2);
	
    /* Modify Chsl by adding Cvary scaled by our separate h,s,l controls */
    hue += varyhue * ( cellnoise( index+3 ) - 0.5 );
    sat *= 1 - varysat * ( cellnoise( index-14 ) - 0.5 );
    lum *= 1 - varylum * ( cellnoise( index+37 ) - 0.5 );
    Chsl = color ( mod ( hue, 1 ), clamp( sat, 0, 1 ), clamp( lum, 0, 1 ) );
	
    /* Clamp hsl and transform back to rgb space */
    return ctransform ("hsl", "rgb", clamp( Chsl, color (0), color (1) ) );
}

////////////////////////////////////////////////////////////////////////////////

/* Given 2-D texture coordinates ss,tt and their filter widths ds, dt,
 * and the width and height of the grooves between tiles (assuming that
 * tile spacing is 1.0), figure out which (integer indexed) tile we are
 * on and what coordinates (on [0,1]) within our individual tile we are
 * shading.
 * */

float
tilepattern(
            float ss, tt, ds, dt;
	        float groovewidth, grooveheight;
	        output float swhichtile, twhichtile;
	        output float stile, ttile;)
{
    swhichtile = floor (ss);
    twhichtile = floor (tt);
    stile = ss - swhichtile;
    ttile = tt - twhichtile;

    return filteredpulsetrain (groovewidth, 1, ss+groovewidth/2, ds)
             * filteredpulsetrain (grooveheight, 1, tt+grooveheight/2, dt);
}

////////////////////////////////////////////////////////////////////////////////

/* basic brick tiling pattern --
 *   inputs:
 *      x, y                    positions on a 2-D surface
 *      tilewidth, tileheight   dimensions of each tile
 *      rowstagger              how much does each row stagger relative to
 *                                   the previous row
 *      rowstaggervary          how much should rowstagger randomly vary
 *      jaggedfreq, jaggedamp   adds noise to the edge between the tiles
 *   outputs:
 *      row, column             index which tile the sample is in
 *      xtile, ytile            position within this tile (0-1)
 * */

void basicbrick (float x, y;
	        	uniform float tilewidth, tileheight;
	        	uniform float rowstagger, rowstaggervary;
	        	uniform float jaggedfreq, jaggedamp;
	        	output float column, row;
	        	output float xtile, ytile;
    )
{
    point PP;
    float scoord = x, tcoord = y;

    if (jaggedamp != 0.0) {
	/* Make the shapes of the bricks vary just a bit */
	PP = point noise (x*jaggedfreq/tilewidth, y*jaggedfreq/tileheight);
	scoord += jaggedamp * xcomp (PP);
	tcoord += jaggedamp * ycomp (PP);
    }

    xtile = scoord / tilewidth;
    ytile = tcoord / tileheight;
    row = floor (ytile);   /* which brick row? */

    /* Shift the columns randomly by row */
    xtile += mod (rowstagger * row, 1);
    xtile += rowstaggervary * (noise (row+0.5) - 0.5);

    column = floor (xtile);
    xtile -= column;
    ytile -= row;
}

////////////////////////////////////////////////////////////////////////////////
// Alternative surface curvature shader by Matthew Parrot //////////////////////
// http://atabet.com/curvature/curvature.htm ///////////////////////////////////
// Derived from Advanced Renderman by Apodaca and Gritz, and Mathworld.com /////
// slightly tweaked/changed to fit shrimp's structure //////////////////////////
////////////////////////////////////////////////////////////////////////////////

void mpcurvature(
					point pp;
					output varying float kmax, kmin;
		)
{
	/* Calculates the minimum and maximum surface curvature at point P
	 * derived from Advanced Renderman, by Apodaca and Gritz, and 
	 * Mathworld.com.
	 * Implementation by Matthew Parrot, mparrot@vt.edu */

	float ku, kv, kuv; // curvature in u and v
	vector dpdu = Du(pp);
	float ddpddu = length( Du(Du(pp)));
	vector dpdv = Dv(pp);
	float ddpddv = length( Dv(Dv(pp)));
	float ddpdudv = length( Du(Dv(pp)));

	ku = ddpddu / pow( length(dpdu), 2);
	kv = ddpddv / pow( length(dpdv), 2);
	kuv = ddpdudv / ( length(dpdu) * length(dpdv));

	float theta = atan(((2 * kuv) / (ku-kv)))/ 2;
	float pm = 2 * kuv * sin(theta) * cos(theta); //+ minus portion of curvature
	float base = ku * pow( sin( theta), 2) + kv * pow( cos(theta), 2);
	float kmaxt = base + pm;
	float kmint = base - pm;
	kmax = max( kmaxt, kmint);
	kmin = min( kmaxt, kmint);
}

////////////////////////////////////////////////////////////////////////////////
// Bias, Gain, Gamma functions, by Rudy Cortes /////////////////////////////////
// from rendermanacademy.com Function Of the Week section //////////////////////
////////////////////////////////////////////////////////////////////////////////

/* behaves like a brigthness filter */
float bias( float x, val )
{
	return (val > 0) ? pow(x, log(val) / log(0.5)) : 0;
}

/* behaves like a contrast filter */
float gain( float x, val)
{
	return 0.5 * ((x < 0.5) ? bias (2*x, 1-val): (2-bias(2-2*x, 1-val)));
}

////////////////////////////////////////////////////////////////////////////////
// An fast lookup table implemention of the error function follows, ////////////
// courtesy of Mario Marengo (thanks once again). //////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* Error function (approximated as a lookup table) */

float mm_erf(	float x; )
{
	float ax = abs(x);
	float ret = 0;

	if (ax >= 4.0) {
		ret = 1.0;
	} else {
		ret = spline( "linear", ax/ 4.0,
				0.000000, 0.112463, 0.222703, 0.328627, 0.428392,
				0.520500, 0.603856, 0.677801, 0.742101, 0.796908,
				0.842701, 0.880205, 0.910314, 0.934008, 0.952285,
				0.966105, 0.976348, 0.983790, 0.989091, 0.992790,
				0.995322, 0.997021, 0.998137, 0.998857, 0.999311,
				0.999593, 0.999764, 0.999866, 0.999925, 0.999959,
				0.999978, 0.999988, 0.999994, 0.999997, 0.999998,
				0.999999, 1.000000, 1.000000, 1.000000, 1.000000,
				1.000000 );
	}
	return ret;
}

/* Complementary error function */

float mm_erfc( float x; ) {
	return 1 - mm_erf(x);
}

////////////////////////////////////////////////////////////////////////////////

#endif
