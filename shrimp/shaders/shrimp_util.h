/* 
    shrimp_util.h

    Some small, commonly needed macros and functions.
    These are based on, and replace, the similar functions found
    in patterns.h by Larry Gritz as distributed with BMRT.
    Some of the macros are also based on similar ones given in
    rmannotes.sl by Steve May, or taken from Darwyn Peachey's chapter
    in "Texturing and Modelleling" by Ebert et al.
*/


#ifndef SHRIMPUTIL_H
#define SHRIMPUTIL_H 1


/*
    filter width macros, used to estimate correct sample rate for
    antialiasing. ( from Apodaca92 )
*/
#ifndef MINFILTWIDTH
#  define MINFILTWIDTH 1.0e-7
#endif
/*
#ifndef filterwidth
#  define filterwidth(x)  ( max( abs( Du(x)*du ) + abs( Dv(x)*dv ), MINFILTWIDTH ) )
#endif
#ifndef filterwidthp
#  define filterwidthp(p) ( max( sqrt( area(p) ), MINFILTWIDTH ) )
#endif
*/
float filterwidth( float x )
{
	return max( abs( Du(x)*du ) + abs( Dv(x)*dv ), MINFILTWIDTH );
}

float filterwidth( point p )
{
	return max( sqrt( area(p) ), MINFILTWIDTH );
}

/* 
    note this is a smooth pulse that performs its own antialiasing
    over the sample width given by fwidth. It is identical to the 
    PULSE macro given by Peachey in chapter 2 of "Texturing and Modelling"
    Ebert et al. except with smoothstep replacing the step calls.
    If a sharp pulse is absolutly required, this can be used with fwidth = 0
*/
#define pulse( a, b, x, fwidth ) (smoothstep((a)-(fwidth),(a),(x)) - \
                                        smoothstep((b)-(fwidth),(b),(x)))


/*
    The following 2 macros are useful in generating tiling patterns.
    repeat transforms surface coords into coords in the current tile.
    whichtile returns the number of the current tile.
*/
#define repeat( x, freq )	( mod( (x) * (freq), 1 ) )
#define whichtile( x, freq )	( floor( (x) * (freq) ) )


/*
    This is the same as mix except blend allows a non-scalar 3rd arg.
*/
#define blend( a, b, x ) ( (a) * (1 - (x)) + (b) * (x) )


/*
    Adds offset to the point, but wraps around so 0<=x<=1
*/
#define shift( x, offset ) ( mod( (x) + (offset), 1 ) )


/* 
    Just shorthand, but it makes things more readable
*/
#define odd(x)            (mod((x), 2) == 1)
#define even(x)           (mod((x), 2) == 0) 


/* 
    Rotate the point (x,y) about the point (ox,oy) by theta radians
    Returns the answer in (rx,ry)
*/ 
void 
rotate2d( float x, y, theta, ox, oy; 
          output float rx, ry; )
{
    float sint = sin(theta);
    float cost = cos(theta);
    rx = ( x - ox )*cost - ( y - oy )*sint + ox;
    ry = ( x - ox )*sint + ( y - oy )*cost + oy;
}


/*
    Converts cartesian to polar coordinates (2D)
*/
void
topolar2d( float x, y;
           output float r, theta; )
{
    r = sqrt( x*x + y*y );
    theta = atan( y, x );
}


/* 
    boolean ops (from Perlin85)
*/
#define intersection( a, b ) ( (a) * (b) )
#define union( a, b )        ( (a) + (b) - (a)*(b) )
#define difference( a, b )   ( (a) - (a)*(b) )
#define complement( a )      ( 1 - (a) )
#define exclusiveor( a, b )  ( difference( union( (a),(b) ), intersection( (a),(b) ) ) ) 

#endif
