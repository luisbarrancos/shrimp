////////////////////////////////////////////////////////////////////////////////

#include "shrimp_helpers.h"
#include "shrimp_extras.h" /* for PDFs and Geometric attenuation, for the 
							   Cook-Torrance model */
#include "shrimp_aov.h"		/* for the AOVs macros. Note that we initialize
							   all the AOVs to zero in the first statement
							   of the preview shader with INIT_AOV_PARAMETERS*/
#include "odwikicomplex.h"	/* Complex math, from the Odforce.net's Odwiki,
							   including full formula for complex Fresnel. */

#ifndef SHRIMP_SHADING_MODELS
#define SHRIMP_SHADING_MODELS

#ifndef SQR
#define SQR(X) ( (X) * (X) )
#endif

////////////////////////////////////////////////////////////////////////////////
// Wrapped diffuse illumination model, based on ZJ's wrapped diffuse model /////
////////////////////////////////////////////////////////////////////////////////

color
wrappeddiffuse(
				float wangle;
				normal Nn;
				vector In;
		)
{
	normal Nf = faceforward( Nn, In );
	
	extern point P;
	color C = color(0);

	illuminance( P, Nf, PI)
	{
		extern vector L;
		extern color Cl;
		
		uniform float nondiff = 0;
		lightsource("__nondiffuse", nondiff);
		
		if (nondiff < 1) {
			vector Ln = normalize(L);
			C += Cl * (1-nondiff) * 1 - min(1, acos(Ln.Nn)/radians(90+wangle));
		}
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Rim lighting shader /////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

float
rimlighting(
				float rwidth;
				float dx;
				normal Nn;
				vector In; // usually viewer vector,can be user supplied vector
		)
{
	normal Nf = faceforward( Nn, In);
	vector Vf = -In;
	float C = 0;
	
	if (dx == 0.0) {
		C = smoothstep(1.0 - rwidth, 1.0, 1 - Vf.Nf);
	} else {
		C = filteredsmoothstep(1.0 - rwidth, 1.0, 1 - Vf.Nf, dx);
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Minnaert limb darkening term (Note: Nvidia uses a different approach - //////
// in which the limb coefficient is i nthe 0,1 range, this one is in the 1,2 ///
// range. //////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

color
Minnaert(
            float k;
            normal Nn;
            vector In;
        )
{
    normal Nf = faceforward(Nn, In);
	vector Vf = -In;
	
	float ndotv = max( 0, Nf.Vf);
	float thetak = pow( ndotv, k-1);
	
    extern point P;
	color Cminnaert = color(0);
	
    illuminance( P, Nf, PI/2 )
    {
        extern vector L;
        extern color Cl;
		
		uniform float nondiff = 0;
		lightsource("__nondiffuse", nondiff);
	
		if (nondiff < 1) {
	        vector Ln = normalize(L);
    	    float ndotl = max( 0, Ln.Nf);
        	Cminnaert += Cl * (1-nondiff) * pow( ndotl, k);
		}
    }
    Cminnaert *= thetak;

    return Cminnaert;
}

////////////////////////////////////////////////////////////////////////////////
// Hapke-Lommel-Seeliger lunar surface BRDF ////////////////////////////////////
// Szymon Rusinkiewicz's implementation, based on "A Theoretical photometric ///
// function for the Lunar Surface", in Journal of Geophysical Research,vol.68 //
// no.15, 1963 /////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// slightly tweaked to fit shrimp's structure //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Szymon Rusinkiewicz
 *
 * brdf_hls.cc
 * The Hapke/Lommel-Seeliger Lunar-surface BRDF with
 * Schönberg backscattering and the Hapke retrodirective
 * function.
 *
 * Hapke, Bruce. "A Theoretical Photometric Function for
 * the Lunar Surface", in
 * Journal of Geophysical Research, Vol.68, No.15, 1963
*/

#ifndef EPS
#define EPS 0.0001
#endif

float Eval(
            vector vin, vout;
            normal vn;
            float g, f, r;
        )
{
    float cosalpha = clamp( vin.vout, EPS, 1.0-EPS);
    float sinalpha = sqrt( 1.0 - SQR( cosalpha));
    float tanalpha = sinalpha/cosalpha;
    float alpha = acos( cosalpha);

    float R = (alpha < PI/2.0-EPS) ?
        2.0 - tanalpha/2.0/g*(1.0-exp(-g/tanalpha))*(3.0-exp(-g/tanalpha)) : 1;
    float S = 2.0/3.0/PI*((sinalpha+(PI-alpha)*cosalpha)/PI
			+ f*SQR(1.0 - cosalpha));
	return r*R*S/(vin.vn + vout.vn);
}

color Hapke(
                float sden, fscat, refl;
                normal Nn;
                vector In;
        )
{
    normal Nf = faceforward( Nn, In);
    vector Vf = -In;

    float cos_theta_r = clamp(Nf.Vf, EPS, 1);

    extern point P;
	color Ct = color(0);
	
    illuminance( P, Nf, PI/2 )
	{
        extern vector L;
        extern color Cl;
		
		uniform float nondiff = 0;
		lightsource("__nondiffuse", nondiff);
		
		if (nondiff < 1) {
        	vector Ln = normalize(L);
        	Ct += Cl * (1-nondiff) * Eval( Ln, Vf, Nf, sden, fscat, refl) 
					* Ln.Nf * PI;
		}
    }
    return Ct;
}

////////////////////////////////////////////////////////////////////////////////
// Lawrence B. Wolff diffuse model, based in "Improved Diffuse Reflection //////
// Models for Computer Vision", by Lawrence B. Wolff, Shree K. Nayar, and //////
// Michael Oren. ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#ifndef AIR
#define AIR 1.000293 /* ior for air */
#endif

/* formula for the Fresnel reflection factor for unpolarized  light */
float nfresnel( float cos_theta, eta; )
{
	float g2 = sqrt( eta * eta - 1 + (cos_theta * cos_theta) );
	float A = g2 - cos_theta;
	float B = g2 +cos_theta;
	float tmp = .5 * ( (A*A) / (B*B) );
	float AA = B * cos_theta -1;
	float BB = A * cos_theta + 1;
	float tmp2 = 1 + ( (AA*AA) / (BB*BB) );
	return tmp * tmp2;
}

/* "The diffuse reflection model proposed by Wolff, models reflection from
 * smooth dielectric materials as a combination of subsurface light scattering
 * distribution produced from internal inhomogeneities coupled with the 
 * refraction of externally incidend and internally scattered light at the 
 * air/surface dielectric boundary.", from "Improved Diffuse Reflection Models
 * for Computer Vision", by Lawrence B. Wolff, Shree K. Nayar, and
 * Michael Oren. */

color Wolff(
				normal Nn;
				vector In;
				float ior;
		)
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -In;

	/* store preset quantities whenever possible */
	float cos_theta_r = Vf.Nf;
	color C = color(0);
	extern point P;

	illuminance( P, Nf, PI/2 )
	{
		uniform float nondiff = 0;
		lightsource("__nondiffuse", nondiff);
		
		if (nondiff < 1) {
			extern vector L;
			extern color Cl;
			vector Ln = normalize(L);
			float cos_theta_i = Ln.Nf;
			/* first Fresnel term accounting for refraction of externally
			 * incident light. */
			float F = 1 - nfresnel( cos_theta_i, ior );
			C += (1-nondiff) * Cl * F * cos_theta_i;
		}
	}
	/* getting cosine of transmitted angle, for the second Fresnel term,
	 * accounting for the refraction of internally scattered light. */
	float eta = AIR/ior;
	float cos_theta_t = sqrt( max( 0, 1 - (eta*eta * (1 - (cos_theta_r *
							cos_theta_r)) )));
	/* 2nd Fresnel term */
	float F2 = 1 - nfresnel( cos_theta_t, eta );

	return C * F2;
}

////////////////////////////////////////////////////////////////////////////////
// Oren-Nayar generalization of Lambert's reflection model /////////////////////
// implementation by Szymon Rusinkiewicz  //////////////////////////////////////
// from http://unix.math2.us.edu.pl/~perry/mp/wyklBRDF.pdf /////////////////////
////////////////////////////////////////////////////////////////////////////////
// slighly tweaked to fit shrimp's structure ///////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Oren and Nayar's generalization of Lambert's reflection
 * model. The roughness parameter gives the standard deviation
 * of angle orientatations of the presumed surface grooves.
 * When roughness = 0, the model is Lambertian.
 * */

/* NOTE: this is the "qualitative" model, without inter-reflections */

color
OrenNayar(
            float roughness;
            normal Nn;
            vector In;
        )
{
	vector Nf = faceforward (Nn, In);
	vector Vf = -In;
	
	/* surface roughness coeffs for oren/nayar's formula */
	float sigma2 = roughness * roughness;
	float A = 1 - 0.5 * sigma2 / (sigma2 + 0.33);
	float B = 0.45 * sigma2 / (sigma2 + 0.09);
	float ndotv = Vf.Nf;

	/* useful precomputed quantities */
	float theta_r = acos( ndotv ); /* angle between V and N */
	vector V_perp_N = normalize(Vf-Nf * (ndotv) ); /* part of V perpend to N */

	extern point P;
	color C = color(0);
	
	illuminance (P, Nf, PI/2 )
	{
		extern vector L;
        extern color Cl;
		
		uniform float nondiff = 0;
		lightsource ("__nondiffuse", nondiff);
        
		if (nondiff < 1) {
			vector Ln = normalize(L);
			float cos_theta_i = Ln.Nf;
			float cos_phi_diff = V_perp_N . normalize(Ln - Nf * cos_theta_i);
			float theta_i = acos( cos_theta_i );
			float alpha = max( theta_i, theta_r );
			float beta = min( theta_i, theta_r );
			
			C += Cl * (1-nondiff) * cos_theta_i * (A + B * max( 0,
						cos_phi_diff ) * sin( alpha ) * tan( beta ) );
		}
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Oren-Nayar diffuse model, implementation by Larry Gritz, from ///////////////
// The RenderMan Repository - http://www.renderman.org /////////////////////////
// This implementation is the 3 coefficients implementation with ///////////////
// inter-reflections ///////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* renamed LG_orennayar.sl -- tal AT renderman DOT org */
/*
 * orennayar.sl - rough diffuse surface
 *
 * 
 * DESCRIPTION:
 *   Makes a rough surface using a BRDF which is more accurate than
 *   Lambert.  Based on Oren & Nayar's model (see Proc. SIGGRAPH 94).
 *
 *   Lambertian (isotropic) BRDF is a simple approximation, but not
 *   an especially accurate one for rough surfaces.  Truly rough surfacs
 *   tend to act more like retroreflectors than like isotropic scatterers.
 * 
 * PARAMETERS:
 *   Ka, Kd - just like matte.sl
 *   sigma - roughness (0 is lambertian, larger values are rougher)
 *
 * AUTHOR:  Larry Gritz
 *
 * REFERENCES:
 *   Oren, Michael and Shree K. Nayar.  "Generalization of Lambert's
 *         Reflectance Model," Computer Graphics Annual Conference
 *         Series 1994 (Proceedings of SIGGRAPH '94), pp. 239-246.
 *
 * NOTES:
 *   1. Note that this is really just an illuminance loop that gathers
 *      light from the sources and applies Oren & Nayar's local reflectance
 *      model to the result.  It could easily be packaged up as a macro
 *      or a function and used in any other shader, in place of diffuse().
 *   2. Examination of why rough surfaces are not Lambertian will lead
 *      you to the solution to the famous "flat full moon" problem.
 *
 * HISTORY:
 *   14 June 1994 -- written by Larry Gritz
 *
 */

/* tweaked a bit to fit Shrimp's structure.
 * TODO: try and optimize this a bit, if possible */

color
LG_OrenNayar(
				color Cdiff;
				float sigma;
				normal Nn;
				vector In;
		)
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -In;
	/* store preset quantites whenever possible */
	float cos_theta_r = Vf.Nf;
	float theta_r = acos( cos_theta_r );
	float sigma2 = sigma * sigma;
	float C1 = 1 - .5 * sigma2 / (sigma2 + .33);

	color C = color(0), L1 = color(0), L2 = color(0);
	extern point P;

	illuminance( P, Nf, PI/2 ) {

		uniform float nondiff = 0;
		lightsource("__nondiffuse", nondiff);

		if (nondiff < 1) {
			extern vector L;
			extern color Cl;
			vector Ln = normalize(L);
			float cos_theta_i = Ln.Nf;
			float cos_phi_diff = normalize(Vf - Nf * cos_theta_r) .
								 normalize(Ln - Nf * cos_theta_i);
			float theta_i = acos( cos_theta_i );
			float alpha = max( theta_i, theta_r );
			float beta = min( theta_i, theta_r );
			
			float C2 = .45 * sigma2 / (sigma2 + .09);
			
			if (cos_phi_diff >= 0) {
				C2 *= sin(alpha);
			} else {
				C2 *= (sin(alpha) - pow( 2 * beta / PI, 3));
			}
			/* C3 coefficient isn't used in the Qualitative model */
			float C3 = .125 * sigma2 / (sigma2 + .09) * pow(( 4 * alpha
						* beta) / (PI * PI), 2);
			
			L1 = Cdiff * (cos_theta_i * (C1 + cos_phi_diff * C2 * tan(beta)
						+ (1 - abs( cos_phi_diff)) * C3 * tan( (alpha
								+ beta) / 2 )));
			L2 = (Cdiff * Cdiff) * (.17 * cos_theta_i * sigma2 / (sigma2
						+ .13) * (1 - cos_phi_diff * (4 * beta * beta) /
							(PI * PI)));
			
			C += (1-nondiff) * Cl * (L1 + L2);
		}
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Oren-Nayar-Wolff diffuse model, based on the paper "Improved Diffuse ////////
// Reflection Models for Computer Vision", by Lawrence B. Wolff, Shree K. //////
// Nayar, Michael Oren, and on Larry Gritz's implementation of the full ////////
// Oren-Nayar model, with inter-reflections, from The RenderMan Repository /////
// http://www.renderman.org ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* "The diffuse reflection model proposed by Wolff, models reflection from
 * smooth dielectric materials as a combination of a subsurface light 
 * scattering distribution produced from internal inhomogeneities coupled
 * with the refraction of externally incident, and internally scattered
 * light at the air-surface dielectric boundary." */
/* The Oren-Nayar-Wolff implementation is based on the full model considering
 * inter-reflections. */

color
OrenNayarWolff(
				float sigma, ior;
				color Cdiff;
				normal Nn;
				vector In;
		)
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -In;

	/* store preset quantities whenever possible */
	float cos_theta_r = Vf.Nf;
	float theta_r = acos( cos_theta_r );
	float sigma2 = sigma * sigma;

	color C = color(0), L1 = color(0), L2 = color(0);
	float eta = AIR/ior;
	extern point P;
	
	illuminance( P, Nf, PI/2 ) {

		uniform float nondiff = 0;
		lightsource("__nondiffuse", nondiff);

		extern vector L;
		extern color Cl;

		vector Ln = normalize(L);
		float cos_theta_i = Ln.Nf;
		float cos_phi_diff = normalize(Vf-Nf * cos_theta_r) .
								normalize(Ln - Nf * cos_theta_i );
		float theta_i = acos( cos_theta_i );
		float alpha = max( theta_i, theta_r );
		float beta = min( theta_i, theta_r );

		/* transmitted angle */
		float cos_theta_tl = sqrt( max( 0, 1 - (eta*eta * (1 - 
							(cos_theta_i * cos_theta_i) )) ));

		/* 1st Oren-Nayar coefficient */
		float C1 = (1 - .5 * sigma2 / (sigma2 + .33)) * (1 - nfresnel(
					cos_theta_i, ior )) * (1 - nfresnel( cos_theta_tl, eta ));
		/* 2nd coefficient */
		float C2 = .45 * sigma2 / (sigma2 + .09);
		if (cos_phi_diff >= 0) {
			C2 *= sin(alpha);
		} else {
			C2 *= (sin(alpha) - pow( 2 * beta / PI, 3));
		}
		/* 3rd coefficient (Qualitative model only uses C1+C2) */
		float C3 = .125 * sigma2 / (sigma2 + .09) * pow(( 4 * alpha *
					beta) / (PI * PI), 2);

		/* Final L1 term */
		L1 = Cdiff * (cos_theta_i * (C1 + cos_phi_diff * C2 * tan(beta)
					+ (1 - abs( cos_phi_diff )) * C3 * tan( (alpha
							+ beta) / 2 )));

		/* Final L2 term */
		L2 = (Cdiff * Cdiff) * (.17 * cos_theta_i * sigma2 / (sigma2
					+ .13) * (1 - cos_phi_diff * (4 * beta * beta) /
						(PI * PI)));

		C += (1 - nondiff) * Cl * (L1 + L2);
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Note: below follows the Ashikhmin-Shirley diffuse term, based on the ////////
// implementation by Peter Stuart, as well as further below, the specular //////
// term, for those wanting to experiment with things. The complete model is ////
// further below. Also note that the diffuse term and specular terms are ///////
// inter-dependent, but for the sake of giving the user the possibility to /////
// experiment a bit, i thought we could include the separate terms as well. ////
// So things were tweaked a bit, in order to fit shrimp's structure. ///////////
////////////////////////////////////////////////////////////////////////////////
// based on "An anisotropic Phong BRDF Model", by Michael Ashikhmin and ////////
// Peter Shirley ///////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* 
 * ashshir.sl
 * Simple surface using Ashikmin-Shirley BRDF
 * Peter Stuart
 * $Id: ashshir.sl,v 1.4 2003/05/05 05:22:41 ophi Exp $
 * description: Ashikmin and Shirley BRDF lighting model as described
 * in "An Anisotropic Phong Light Reflection Model." Most of the work
 * is done in ashShirModel.h by two functions - one for dealing with
 * direct lighting, and the other for dealing with environment lighting.
 *
 * ---- surface parameters ----------
 * rd: diffuse reflectance
 * rs: specular reflectance
 * nu: specular exponent along xdir
 * nv: specular exponent perpendicular to xdir
 * refl: amount of reflection to use
 * envname: name of environment map to use. If this is "" the shader will
 *   try to raytrace the environment if there are samples (envsamp > 0)
 * envsamp: number of samples to use when sampling the environment
*/

color
anisophongdiff(
				normal Nn;
				vector In;
				float Kd, Ks;
				)
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -In;
	
    extern point P;
    color C = color(0);

    illuminance( P, Nf, PI/2 )
    {
        extern vector L;
        extern color Cl;
		
		uniform float nondiff = 0;
		lightsource("__nondiffuse", nondiff);
		
		if (nondiff < 1) {
	        vector Ln = normalize(L);

    	    float secta, sectb, sectc;
       		float ndotl = Nf.Ln;
        	float ndotv = Nf.Vf;

        	secta = (28*Kd) / (23*PI);
        	sectb = 1-pow( (1-( ndotl/2)), 5);
        	sectc = 1-pow( (1-( ndotv/2)), 5);

        	C += Cl * (1-nondiff) * ndotl * secta * (1-Ks) * sectb * sectc;
		}
    }
    return C;
}

////////////////////////////////////////////////////////////////////////////////
// James F. Blinn specular term (Phong-Blinn) //////////////////////////////////
// from "Models of Light Reflection for Computer Synthesized Pictures", ////////
// Computer Graphics, Vol.11, No.2, July 1977, page 192-198 (?) ////////////////
////////////////////////////////////////////////////////////////////////////////

color phong_blinn(
					normal Nn;
					vector In;
					float size;
					)
{
	normal Nf = faceforward(Nn, In);
	vector Vf = -In;
	
    extern point P;
	color C = color(0);
	
    illuminance( P, Nf, PI/2 )
    {
        extern vector L;
        extern color Cl;
		
		uniform float nonspec = 0;
		lightsource("__nonspecular", nonspec);
		
		if (nonspec < 1) {
	        vector Ln = normalize(L);
    	    vector Hn = normalize(Ln + Vf);
			
        	float ndoth = Nf.Hn;
        	C += Cl * (1-nonspec) * pow( max( 0.0, ndoth), size) * (Nf.Ln);
		}
    }
    return C;
}

////////////////////////////////////////////////////////////////////////////////
// Larry Gritz's LocIllumGlossy ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// slightly tweaked to fit shrimp's structure //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* LocIllumGlossy - possible replacement for specular(), with a more 
 * uniformly bright core and sharper falloff. Good specular function for
 * something made of glass or liquid, in which roughness = related to the
 * size of the highlight, larger is bigger, and sharpness = 1 is infinitely
 * sharp, 0 is very dull
 */

color
LocIllumGlossy(
				normal Nn;
				vector In;
				float roughness, sharpness;
				)
{
	normal Nf = faceforward( Nn, In);
	vector Vf = -In;
    
	float w = .18 * (1-sharpness);
	
	extern point P;
    color C = color(0);
	
	illuminance (P, Nf, PI/2 )
	{
		extern vector L;
        extern color Cl;
        
		uniform float nonspec = 0;
		lightsource ("__nonspecular", nonspec);
		
		if (nonspec < 1) {
			vector Ln = normalize(L);
			vector Hn = normalize(Vf+Ln);

			C += Cl * (1-nonspec) * smoothstep( .72-w, .72+w,
					pow( max( 0.0, Nf.Hn), 1/roughness ) );
		}
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Variation on Greg Ward's isotropic specular /////////////////////////////////
// Note that you can just pass identical values to x and y anisotropy, in the //
// Ward anisotropic shader, and get the same results, altough at a slight //////
// extra expense. //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

color
Wardisotropy(
				normal Nn;
				vector In;
				float roughness;
		)
{
    normal Nf = faceforward( Nn, In);
    vector Vf = -In;

	extern point P;
	color C = color(0);
	
	illuminance (P, Nf, PI/2 )
	{
		extern vector L;
		extern color Cl;
		
		uniform float nonspec = 0;
		lightsource("__nonspecular", nonspec);
		
		if (nonspec < 1) {
	        vector Ln = normalize(L);
    	    float ndotl = Nf.Ln;

			vector Hn = normalize(Ln + Vf);
			float ndoth = Nf.Hn;
			float ndotv = Nf.Vf;

			float tandelta = max( 0.0, sqrt( 1.0 - (ndoth*ndoth)) / ndoth);
			float tandelta2 = tandelta * tandelta;
			float m2 = roughness * roughness;

			C += Cl * (1-nonspec) * ndotl * ( exp( -(tandelta/m2)) /
							(4 * m2 * sqrt( ndotl * ndotv )) );
		}
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Greg Ward Larson's anisotropic model ////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// slightly tweaked to fit shrimp's structure //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Greg Ward Larson's anisotropic specular local illumination model.
 * The derivation and formulae can be found in:  Ward, Gregory J.
 * "Measuring and Modeling Anisotropic Reflection," ACM Computer
 * Graphics 26(2) (Proceedings of Siggraph '92), pp. 265-272, July, 1992.
 * Notice that compared to the paper, the implementation below appears to be
 * missing an factor of 1/PI, and to hav an extra L.N term.
 * This is not an error! It is because the paper's formula is for the BRDF,
 * which is only part of the kernel of the light integral, whereas shaders
 * must compute the result of the integral.
 * 
 * Inputs:
 *  N - unit surface normal
 *  V - unit viewing direction (from P toward the camera)
 *  xdir - a unit tangent of the surface which defines the reference
 *  direction for the anisotropy.
 *  roughness - the apparent roughness of the surface in xdir.
 *  yroughness - the roughness for the direction of the surface
 *  tangent which is perpendicular to xdir.
 */

color
LocIllumWardAnisotropic(
							normal Nn;
							vector In, xdir;
							float xroughness, yroughness;
		)
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -In;

	float cos_theta_r = clamp( Nf.Vf, 0.0001, 1);
	vector X = xdir / xroughness;
	vector Y = (Nf ^ xdir) / yroughness;

	extern point P;
	color C = color(0);
	
	illuminance( P, Nf, PI/2 )
	{
		extern vector L;
		extern color Cl;
		
		uniform float nonspec = 0;
		lightsource("__nonspecular", nonspec);
		
		if (nonspec < 1) {
			vector Ln = normalize(L);
			float cos_theta_i = Ln.Nf;
			
			if (cos_theta_i > 0.0) {
				vector Hn = normalize(Vf + Ln);
				
				float rho = exp( -2 * ( SQR( X.Hn ) + SQR( Y.Hn )) /
						(1+ Hn.Nf)) / sqrt( cos_theta_i * cos_theta_r );
				
				C += Cl * (1-nonspec) * cos_theta_i * rho;
			}
		}
	}
	return C / (4 * xroughness * yroughness);
}

////////////////////////////////////////////////////////////////////////////////
// Christophe Schlick isotropic BRDF ///////////////////////////////////////////// based on his paper, 'An inexpensive BRDF model for physically based /////////
// rendering, Eurographics'94, published in Computer Graphics Forum, v13, n3 ///
// p199-162, September 1994. ///////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

color schlickspec(
                    normal Nn;
                    vector In;
                    float roughness;
        )
{
	normal Nf = faceforward( Nn, In);
	vector Vf = -In;
	
    extern point P;
	color C = color(0);
    
    illuminance( P, Nf, PI/2 )
    {
        extern vector L;
        extern color Cl;
		
		uniform float nonspec = 0;
		lightsource("__nonspecular", nonspec);
		
		if (nonspec < 1) {
			vector Ln = normalize(L);
			
			vector Rn = normalize( reflect( -Ln, Nf));
        	float Nr = 1 / (roughness * roughness);
			
        	float rdotv = max( 0, Rn.Vf);
        	float coeff = rdotv / (Nr - Nr * rdotv + rdotv);
			
        	C += Cl * (1-nonspec) * coeff * (Nf.Ln);
		}
    }
    return C;
}

////////////////////////////////////////////////////////////////////////////////
// Anisotropic version of Cristophe Schlick's BRDF, with geometric /////////////
// attenuation, based on his paper: 'An inexpensive BRDF model for /////////////
// physically based rendering', Eurographics'94, published in Computer /////////
// Graphics Forum, v13, n3, p199-162, September 1994. //////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* Approximation of the Smith geometric attenuation function */
float sgeoattenuation(
						float costheta, roughness;
		)
{
	float g1 = roughness - roughness * costheta + costheta;
	return costheta / g1;
}

/* Angle dependence */
float angledependence(
						float cosbeta, isotropy;
		)
{
	float i2 = isotropy * isotropy;
	float cosbeta2 = cosbeta * cosbeta;
	return sqrt( isotropy / (i2 - i2 * cosbeta2 + cosbeta2));
}

/* Zenith dependence */
float zenithdependence(
						float cosbeta, roughness;
		)
{
	float cosbeta2 = cosbeta * cosbeta;
	float zz = 1 - (1 - roughness) * cosbeta2;
	return roughness / (zz * zz);
}

/* TODO: re-read all this (Schlick's papers) */
color aschlick(
				float roughness, isotropy, ior;
				normal Nn;
				vector In, dir;
		)
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -In;
	vector xdir = normalize(Nf ^ dir);

	float costheta = Vf.Nf;

	extern point P;
	color C = color(0);

	illuminance( P, Nf, PI/2 )
	{
		uniform float nonspec = 0;
		lightsource("__nonspecular", nonspec);

		if (nonspec < 1) {
			
			extern vector L;
			extern color Cl;

			vector Ln = normalize(L);
			vector Hn = normalize(Vf + Ln);

			float cospsi = Ln.Nf;
			float cosbeta = Hn.xdir;

			/* self-obscuration */
			float G = sgeoattenuation( costheta, roughness) *
						sgeoattenuation( cospsi, roughness );
			/* anisotropy */
			float A = angledependence( cosbeta, isotropy );
			float Z = zenithdependence( Nf.Hn, roughness );
			
			float D = Z * A * G / (4 * cospsi * costheta) * cospsi;

			C += Cl * (1-nonspec) * D;
		}
	}
	float F = schlickfresnel( Nf, Vf, ior );

	return clamp(F*C, color(0), color(1));
}				

////////////////////////////////////////////////////////////////////////////////
// Cook-Torrance specular term. With Beckmann, Trowbridge-Reitz, Ward, and /////
// Heidrich-Seidel microfacet distribution functions, and the default //////////
// Torrance-Sparrow geometric attenuation, Smith attenuation, and He-Torrance //
// attenuation. ////////////////////////////////////////////////////////////////
// TODO: Check Kelemen's paper. ////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

color
cooktorrance(
				normal Nn;
				vector In, anisodir;
				float ior, k, roughness;
				uniform float distromodel, geomodel;
		)
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -normalize(In);

	/* Store quantities */
	float costheta = Nf.Vf;
	
	float D = 0, G = 0, F = 0;
	color Ccook = color(0);

	extern point P;
	illuminance( P, Nf, PI/2 )
	{
		uniform float nonspec = 0;
		lightsource("__nonspecular", nonspec);
		
		if (nonspec < 1) {
			extern vector L;
			extern color Cl;
			vector Ln = normalize(L);
			
			/* In some references, as some available sources, the fresnel term
			 * is the angle between viewer and mean surface normal, but the
			 * microfacets normal is the bisector vector of the incident
			 * vector and the viewer vector. Since the microfacets are tiny
			 * reflectors, we're modelling the probability of them being
			 * oriented in such a way that they cast specular highlights, via
			 * the probability distribution functions, then calculate the
			 * shadowing and masking relative to the adjacent microfacets,
			 * and finally the reflection coefficient of the microfacets
			 * being lit in the incident vector direction. So, as reference,
			 * microfacet normal H != mean surface normal N. */
			vector Hn = normalize(Ln+Vf);

			/* store preset quantities */
			float cosalpha = Nf.Hn;
			float cospsi = Nf.Ln;
			float cospsi2 = Ln.Hn;

			/* Probability distribution functions */
			if (distromodel == 0) {
				D = beckmann( cosalpha, roughness );
			} else if (distromodel == 1) {
				D = ward( cosalpha, roughness );
			} else if (distromodel == 2) {
				D = trowbridge_reitz( cosalpha, roughness );
			} else {
				D = heidrich_seidel( Nf, Vf, Ln, anisodir, roughness );
			}

			/* Geometric attenuation term */
			if (geomodel == 0) {
				G = torrance_sparrow( costheta, cosalpha, cospsi, cospsi2 );
			} else if (geomodel == 1) {
				G = smith( cospsi, costheta, roughness );
			} else {
				G = he_torrance( costheta, cospsi, roughness );
			}

			/* Using the full formula fresnel for unpolarized light, from 
			 * the Odforce.net's Odwiki, by Mario Marengo and the Odforce
			 * community. */
			F = fresnel_kr( Ln.Hn, cx_set( ior, k ) );

			/* Aqsis produced some strange artifacs when getting the amount
			 * of reflected light from the microfacets. Apparent solution
			 * seems to clamp the value. */
#if RENDERER == aqsis
			F = clamp( F, 0, 1 );
#endif

			/* TODO: Re-read Heidrich & Seidel's paper, iirc, the anisotropic
			 * specular term was meant to be coupled with an isotropic
			 * specular term - confirm this - for the time being the
			 * isotropic specular will be added via specularbrdf() shadeop */

			/* no specularbrdf() in Aqsis? */
#if RENDERER == aqsis
			Ccook += Cl * (1-nonspec) * ((D*G*F / (costheta * cospsi)) *
					cospsi);
#else
			Ccook += Cl * (1-nonspec) * ((D*G*F / (costheta * cospsi)) *
				cospsi + ( (distromodel == 3) ?
					specularbrdf( Ln, Nf, Vf, roughness*.5) : color(0) ) );
#endif
		}
	}
	/* at high grazing angles, the values seem to go up a lot(?)
	 * (it is mentioned in the literature though... ) */
	return clamp(Ccook, color(0), color(1));
}

////////////////////////////////////////////////////////////////////////////////
// Ashikhmin-Shirley specular term /////////////////////////////////////////////
// based on Peter Stuart's implementation, original implementation further  ////
// below. Read notes about this model's diffuse term earlier in this header ////
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Model from "An anisotropic Phong BRDF model", by Michael Ashikhmin and //////
// Peter Shirley. //////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* 
 * ashshir.sl
 * Simple surface using Ashikmin-Shirley BRDF
 * Peter Stuart
 * $Id: ashshir.sl,v 1.4 2003/05/05 05:22:41 ophi Exp $
 * description: Ashikmin and Shirley BRDF lighting model as described
 * in "An Anisotropic Phong Light Reflection Model." Most of the work
 * is done in ashShirModel.h by two functions - one for dealing with
 * direct lighting, and the other for dealing with environment lighting.
 *
 * ---- surface parameters ----------
 * rd: diffuse reflectance
 * rs: specular reflectance
 * nu: specular exponent along xdir
 * nv: specular exponent perpendicular to xdir
 * refl: amount of reflection to use
 * envname: name of environment map to use. If this is "" the shader will
 *   try to raytrace the environment if there are samples (envsamp > 0)
 * envsamp: number of samples to use when sampling the environment
*/

color
anisophongspec(
				normal Nn;
				vector In;
				float nu, nv, ior;
				)
{
	normal Nf = faceforward( Nn, In);
	vector Vf = -In;
	
	/* preset quantities */
	float ndotv = Nf.Vf;

    extern vector dPdu, dPdv;
	extern point P;
	color C = color(0);

    illuminance( P, Nf, PI/2 )
    {
        extern vector L;
        extern color Cl;
		
		uniform float nonspec = 0;
		lightsource("__nonspecular", nonspec);
		
		if (nonspec < 1) {
	        vector Ln = normalize(L);
    	    vector Hv = normalize(Ln+Vf);

	        vector vu = normalize(dPdu);
    	    vector vv = normalize(dPdv);
			
			/* preset quantities */
			float ndoth = Nf.Hv;
			float ndoth2 = ndoth * ndoth;
			float ndotl = Nf.Ln;

        	float speccont = sqrt( (nu+1) * (nv+1) / (8*PI));
			
			float nu2 = nu * SQR( Hv.vu );
			float nv2 = nv * SQR( Hv.vv );
			float nunv = (nu2 + nv2) / (1 - ndoth2);
			float nh = pow( ndoth, nunv );

			float nhmax = ndoth * max( ndotl, ndotv);
			
			C += Cl * (1-nonspec) * ndotl * (speccont * (nh / nhmax));
		}
    }
    return C * schlickfresnel( Nn, Vf, ior );
}

////////////////////////////////////////////////////////////////////////////////
// Stephen Westin's brushed metal //////////////////////////////////////////////
// from The RenderMan Repository / http://www.renderman.org ////////////////////
////////////////////////////////////////////////////////////////////////////////
// slightly tweaked for shrimp use, and we need the specular term only /////////
////////////////////////////////////////////////////////////////////////////////

/* renamed to SHW_brushedmetal for RMR -- tal@SpamSucks_cs.caltech.edu */

/*
 * brushdemetal.sl -- brushed metal (anisotropic)
 *
 * DESCRIPTION:
 *   An attempt at an anisotropic surface.
 *   The surface is idealized as a bed of slightly rough parallel
 *   cylinders. For the cylinders,
 *   I use Kajiya's Phong-like highlight from a cylinder (SIGGRAPH '89),
 *   coupled with an arbitrary shadowing/masking function. Direction
 *   of anisotropy (i.e. the axis of the cylinders) is simply the "U"
 *   direction of patch parameter.
 *
 * PARAMETERS:
 *   Ka, Kd, Ks, roughness, specularcolor - work just like the plastic
 *
 * ANTIALIASING: should antialias itself fairly well
 *
 * AUTHOR: written by Stephen H. Westin, Ford Motor Company Corporate Design
 *
 * last modified  02 December 1995 S. H. Westin
 *
 *
 * HISTORY:
 *   12/24/98 tal -- Updated to newer rman syntax
 *
 */

color
shw_brushed_metal(
					float roughness;
					normal Nn;
					vector In, vdir;
					)
{
    float aniso;                   /* Anisotropic scale factor */
    float shad;                    /* Phong-like shadow/masking function */
    
    float sin_light, sin_eye;      /* Sines of angles from tangent vector */
    float cos_light, cos_eye;      /* Cosines of angles from tangent vector */
    
    normal Nf = faceforward (Nn, In);
    vector Vf = -In;
    
    /* "Specular" highlight in the Phong sense: directional-diffuse */
    cos_eye = -vdir.Vf;
    sin_eye = sqrt( 1.0 - cos_eye * cos_eye);
    
    extern point P;
	color C = color(0);
    
    illuminance ( P, Nf, PI/2 )
    {
        extern vector L;
        extern color Cl;
		
		uniform float nonspec = 0;
		lightsource("__nonspecular", nonspec);
		
		if (nonspec < 1) {
			
			vector Ln = normalize(L);
			vector Hn = 0.5 * ( Vf + Ln );
			
	        cos_light = vdir.Ln;
    	    sin_light = sqrt( 1.0 - cos_light * cos_light );
			
        	aniso = max( cos_light*cos_eye + sin_light*sin_eye, 0.0 );
       		shad = max( Nf.Vf, 0.0 ) * max( Nf.Ln, 0.0 );
			
        	C += Cl * (1-nonspec) * pow( aniso, 1.0/roughness ) * shad;
		}
    }
    return C;
}

////////////////////////////////////////////////////////////////////////////////
// Peter Stuart's implementation of the Ashikhmin-Shirley BRDF. ////////////////
// includes environment sampling. //////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// slightly tweaked to fit shrimp's structure //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * Ashkihmin-Shirley BRDF
 * Peter Stuart
 * $Id: ash-shir.sl,v 1.9 2003/05/05 05:22:41 ophi Exp $
 * description: Ashikmin and Shirley BRDF lighting model as described
 * in "An Anisotropic Phong Light Reflection Model." A local illumination
 * version and an environment map version are both included. The environment
 * map version uses the importance sampling as described in the paper to reduce
 * variance.
 * 
 * ---- local illumination surface parameters ----------
 * N: normal direction
 * V: view direction
 * xdir: direction of anisotropy - can be primary or secondary
 * rd: diffuse reflectance
 * rs: specular reflectance
 * nu: specular exponent along xdir
 * nv: specular exponent perpendicular to xdir
 *
 * ---- environment illumination surface parameters ----------
 * N: normal direction
 * V: view direction
 * xdir: direction of anisotropy - can be primary or secondary
 * rd: diffuse reflectance
 * rs: specular reflectance
 * nu: specular exponent along xdir
 * nv: specular exponent perpendicular to xdir
 * samples: number of samples to take of the environment map
 * envmap: name of environment map
*/

/* ---- fast fresnel --------
 * H: vector halfway between V and L ((V+L) / 2)
 * V: view vector (-I/|I|)
 * f0: reflectance at normal incidence
 *
 * Schlick's approximation to the fresnel function
 */
float fastFresnel(vector Hn, Vf; float f0;)
{
    return f0 + (1-f0)*pow(1 - (Hn.Vf), 5);
}

/******** local illumination model **********/

color LocIllumAshShir(
                        normal Nn;
                        vector In, xdir;
						color Cdiff, Cspec;
		                float Kd, Ks, nu, nv;
						DECLARE_AOV_OUTPUT_PARAMETERS
                        )
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -normalize(In);
	
	/* store preset quantities */
	float ndotv = Nf.Vf;
	
    vector u_dir = xdir;
    vector v_dir = Nf ^ xdir;

    float rho_d = 0, rho_s = 0;

    /* calculations that can be done one time ... */
	
	float diffcont = ((28*Kd) / 23) * (1-Ks) * (1 - pow( 1-ndotv/2, 5));
	float speccont = sqrt( (nu+1) * (nv+1)) / 8;

    extern point P;
    
    illuminance(P, Nf, PI/2 )
	{
        extern vector L;
        extern color Cl;

        vector Ln = normalize(L);
		/* store preset quantities */
		float ndotl = Nf.Ln;

        uniform float nondiff = 0, nonspec = 0;
        lightsource("__nondiffuse", nondiff);
        lightsource("__nonspecular", nonspec);
		
        if (nondiff < 1) {
			rho_d = diffcont * (1 - pow( 1-ndotv/2, 5));
        }
		
        if (nonspec < 1) {
			vector Hn = normalize(Vf + Ln);
			/* store preset quantities */
			float ndoth = Nf.Hn;
			
			float nunv2 = ((nu * SQR( Hn.u_dir)) + (nv * SQR( Hn.v_dir))) /
							(1 - SQR( ndoth ));

			rho_s = speccont * pow( ndoth, nunv2) / (ndoth * max( ndotv,
						ndotl)) * fastFresnel( Hn, Vf, Ks );
        }
		
		float maxndotl = max( 0, ndotl);
		
		aov_diffuse += (1-nondiff) * Cl * rho_d * maxndotl;
		aov_specular += (1-nonspec) * Cl * rho_s * maxndotl;
		
    }
    return Cdiff * aov_diffuse + Cspec * aov_specular;
}

/******* "global" illumination model ********/

/* ---- function to sample environment ----
 * P: location of sample
 * R: reflection vector
 * envname: name of environment map - use raytracing if ""
 */
color SampleEnvironment(
                            point Pp;
                            vector Rn;
                            uniform string envname;
                            )
{
    color C = 0;
    if (envname != "") {
        vector Rnn;
        Rnn = vtransform("current", "object", Rn);
        C = color environment(envname, Rnn);
    } else {
        C = trace(Pp, Rn);
    }
    return C;
}

/* ---- helper function -----
 * nu, nv: anisotropic specular exponents
 * e1: random variable [0,1]
 */
float calcPhi(float nu, nv; float e1)
{
    return atan( sqrt( (nu+1)/(nv+1) ) * tan( PI*e1/2) );
}

///////////////////////////////////////////////////////////////////////////////
/* Someone mentioned PRMan allowed a custom distribution of rays in gather()
 * but there's nothing about this on the public specs, nor in 3delight's docs.
 * In any case, this deserves some more reading on the topic to try and 
 * speed up things. */

color EnvIllumAshShir(
                        normal Nf;
                        vector Vf, xdir;
		                float rd, rs, nu, nv;
		                uniform float samples;
		                uniform string envmap;)
{
    uniform float i;
    color C = color(0);

    for (i=0; i<samples; i+=1) {
        float e1=random(), e2=random();
        float ph;

    /* Split up the hemisphere into quarters and remap e1 to one quarter.
       This helps to stratify the samples, hopefully decreasing variance... */
    /* FIXME this can be done better... */
        if (e1 >= 0 && e1 < 0.25)
            ph = calcPhi(nu, nv, 1 - 4*(0.25 - e1));
        else if (e1 >= 0.25 && e1 < 0.5)
            ph = calcPhi(nu, nv, 1 - 4*(0.5 - e1)) + PI/2;
        else if (e1 >= 0.5 && e1 < 0.75)
            ph = calcPhi(nu, nv, 1 - 4*(0.75 - e1)) + PI;
        else
            ph = calcPhi(nu, nv, 1 - 4*(1 - e1)) - PI/2;
    
        float cosph = cos(ph);
        float sinph = sin(ph);
		float th = acos( pow( 1-e2, 1/ (nu * cosph * cosph + nv * sinph 
						* sinph + 1) ) );

        if (th <= PI/2) { /* we don't want thetas below hemisphere */
    
            /* transform H (halfway vector) into space where frame is
	        <xdir, ydir, N> */
            vector ydir = Nf ^ xdir;
			vector Hn = cosph * sin(th) * xdir + sinph * sin(th) * ydir
						+ cos(th) * Nf;
			
            extern point P;
			
            C += rs * SampleEnvironment(P, 2*Hn - Vf, envmap)
                    * fastFresnel(Hn,Vf,rs);

            /* now generate the diffuse part using cos-weighted distribution. */
            e1 = random();
            e2 = random();
			Hn = cos( 2 * PI * e1) * sqrt(1-e2) * xdir + sin( 2 * PI * e1)
					* sqrt(1-e2) * ydir + sqrt(e2) * Nf;
      
            C += rd * SampleEnvironment(P, Hn, envmap);

			/* FIXME - instead of sampling over the hemisphere, get the
			 * cos-weighted average value, which can be done with a
			 * cos-weighted filtered call to environment. The problem is
			 * that such a filter doesn't seem to exist :( */

			/* C += rd * color environment( envmap, xdir, ydir, -xdir, -ydir,
			 * "filter", "gaussian" ); */
        }
    }
    if (samples > 0) C /= samples;
    return C;
}

////////////////////////////////////////////////////////////////////////////////
// Stephen H. Westin's velvet shader ///////////////////////////////////////////
// from The RenderMan Repository , http://www.renderman.org ////////////////////
////////////////////////////////////////////////////////////////////////////////
// slightly tweaked to fit shrimp's structure //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * velvet.sl -- velvet
 *
 * DESCRIPTION:
 *   An attempt at a velvet surface.
 *   This phenomenological model contains three compnents:
 *   - A retroreflective lobe (back toward the light source)
 *   - Scattering near the horizon, regardless of incident direction
 *   - A diffuse color
 * 
 * PARAMETERS:
 *   Ks:	controls retroreflective lobe
 *   Kd:	scales diffuse color
 *   Ka:	ambient component (affects diffuse color only)
 *   sheen:	color of retroreflective lobe and horizon scattering
 *   roughness: shininess of fabric (controls retroreflection only)
 *
 * ANTIALIASING: should antialias itself fairly well
 *
 * AUTHOR: written by Stephen H. Westin, Ford Motor Company
 *
 * HISTORY:
 * 	2001.02.01	westin AT graphics DOT cornell DOT edu 
 *			Fixed retroreflection lobe (sign error); added
 *			"backscatter" parameter to control it; added
 *			"edginess" parameter to control horizon scatter;
 *			defined SQR()
 *
 * prev modified  28 January 1997 S. H. Westin
 */

// modified for inclusion in this header //

color velvet(
                float Ks, backscatter, edginess, roughness;
                color sheen;
                normal Nn;
                vector In;
				DECLARE_AOV_OUTPUT_PARAMETERS
        )

{
    normal Nf = faceforward( Nn, In);
    vector Vf = -In;

    float cosine, sine;

    extern point P;
	color rlobe = color(0), horizonscatter = color(0);
	
    illuminance( P, Nf, PI/2)
	{
        extern vector L;
        extern color Cl;
        
        uniform float nonspec = 0;
        lightsource("__nonspecular", nonspec);
		
        if (nonspec < 1) {
            vector Ln = normalize(L);
		
            /* Retroreflective lobe */
			cosine = max( Ln.Vf, 0);
			rlobe += (1-nonspec) * Cl * sheen * backscatter
								* pow( cosine, 1/roughness);
			/* Horizon scattering */
			cosine = max( Nf.Vf, 0);
			sine = sqrt( 1.0 - SQR( cosine ));
			horizonscatter += (1-nonspec) * Cl * sheen * Ln.Nf *
								pow( sine, edginess );
		}
    }
	
	aov_scattering += Ks * rlobe;
	aov_rimlighting += Ks * horizonscatter;
    return aov_scattering + aov_rimlighting;
}

////////////////////////////////////////////////////////////////////////////////
// Matt Pharr's skin shader based on Hanrahan-Krueger model ////////////////////
////////////////////////////////////////////////////////////////////////////////
// Slightly tweaked to fit Shrimp's structure //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* 
 * skin.sl 
 * 
 * Copyright (C) 2000-2001, Matt Pharr <mmp AT Exluna DOT com > 
 * 
 * This software is placed in the public domain and is provided as is 
 * without express or implied warranty. 
 * 
 * Surface shader that implements a shading model that should have a visual 
 * appearence generall similar to that of skin.  Based on phenomenological 
 * information about skin reflectance from Hanrahan and Krueger, 
 * "Reflection from layered surfaces due to subsurface scattering", 
 * proceedings of Siggraph 1993. 
 *
 * See SIGGRAPH 2001 course notes, "Advanced RenderMan 3: Render Harder,"
 * for notes and background information.
 */ 

/* Evaluate the Henyey-Greenstein phase function for two vectors with
 * an asymmetry value g.  v1 and v2 should be normalized and g should 
 * be in the range (-1, 1).  Negative values of g correspond to more
 * back-scattering and positive values correspond to more forward scattering.
 * */

float phase(vector v1, v2; float g) {
	float costheta = -v1 . v2;
	return (1. - g*g) / pow(1. + g*g - 2.*g*costheta, 1.5);
}

/* Compute a the single-scattering approximation to scattering from
 * a one-dimensional volumetric surface.  Given incident and outgoing
 * directions wi and wo, surface normal n, asymmetry value g (see above),
 * scattering albedo (between 0 and 1 for physically-valid volumes),
 * and the thickness of the volume, use the closed-form single-scattering
 * equation to approximate overall scattering. */

float singleScatter(vector wi, wo; normal n; float g, albedo, thickness) {
    float win = abs(wi . n);
    float won = abs(wo . n);

    return albedo * phase(wo, wi, g) / (win + won) *
		(1. - exp(-(1/win + 1/won) * thickness));
}

vector efresnel(vector II; normal NN; float eta; output float Kr, Kt;) {
    vector R, T;
    fresnel(II, NN, eta, Kr, Kt, R, T);
    Kr = smoothstep(0., .5, Kr);
    Kt = 1. - Kr;
    return normalize(T);
}

/* Implements overall skin subsurface shading model.  Takes viewing and
 * surface normal information, the base color of the skin, a
 * color for an oily surface sheen, the ratio of the indices of 
 * refraction of the incoming ray (typically ~1 for air) to the index
 * of refraction for the transmitted ray (say something like 1.4 for
 * skin), and the overall thickness of the skin layer.  Then loops
 * over light sources with illuminance() and computes the reflected
 * skin color. */

color subsurfaceSkin(
						vector Vf;
						normal Nn;
						color skinColor, sheenColor;
                     	float eta, thickness;
						)
{
	normal Nf = faceforward( Nn, Vf );
	
	float Kr, Kt, Kr2, Kt2;
	extern point P;
	color C = color(0);

	vector T = efresnel(Vf, Nf, eta, Kr, Kt);
	    
	illuminance(P, Nf, PI/2 )
	{
        extern vector L;
        extern color Cl;
		
	    vector Ln = normalize(L);
	    vector H = normalize(Ln + Vf);

		/* preset quantities */
		float ldotn = Ln.Nf;
		float hdotn = H.Nf;
		
	    if ( hdotn > 0) {
			C += Kr * sheenColor * Cl * ldotn * pow( hdotn, 4);
		}
	    C += Kr * sheenColor * Cl * ldotn * .2;

	    vector T2 = efresnel(-Ln, Nf, eta, Kr2, Kt2);

		C += skinColor * Cl * ldotn * Kt * Kt2 *
				( singleScatter( T, T2, Nf, .8, .8, thickness) +
				  singleScatter( T, T2, Nf, .3, .5, thickness) +
				  singleScatter( T, T2, Nf, 0, .4, thickness ) );
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Matt Pharr's implementation of the Kubelka-Munk model ///////////////////////
////////////////////////////////////////////////////////////////////////////////
// Slightly tweaked to fit Shrimp's structure - with some notes from ///////////
// Matt Pharr's presentation at Siggraph2001. See the Siggraph 2001 course /////
// notes for more details. /////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* 
 * km.h
 * 
 * Copyright (C) 2001, Matt Pharr <mmp AT Exluna DOT com > 
 * 
 * This software is placed in the public domain and is provided as is 
 * without express or implied warranty. 
 *
 * Basic implementation of the Kubelka-Munk model for the composition
 * of layered surfaces.  See SIGGRAPH 2001 course notes, "Advanced 
 * RenderMan 3: Render Harder," for notes and background information.
 */

/* Note: this seems to kill both aqsis (1.4phase2) and pixie (r1162), but
 * this behaviour exists for quite some time */
/* FIXME: read more on this model, particularly Neumann's Constructions on
 * BRDFs, the chapter on "sandwiched/layered models". I'm not using this
 * right. */

/* Hyperbolic sine function */
void sinhcosh( float t; output float sinh, cosh; )
{
    float t2 = t;
    if (t2 > 10)
		t2 = 10.;
    float ex = exp(t2);
    float invex = 1. / ex;

    sinh = 0.5 * (ex - invex);
    cosh = 0.5 * (ex + invex);
}

/* This function estimates the attenuation coefficient sigmaA and scattering
 * coefficient sigmaS, for the Kubelka-Munk shading model, given the
 * reflectivity of an infinitely thick sample of the layer under consideration.
 * */
void KMEstimateCoeffs( color Rinf; output color sigma_a, sigma_s; )
{
    if (Rinf == color(0) ) {
        sigma_a = color(1) ;
        sigma_s = color(0) ;
    }
    else {
		/* someone mentioned lots of float/color type errors in prman 13,
		 * - any reports on this would be apretiated - */
        color a_over_s = (color(1) - Rinf) * (color(1) - Rinf)
			/ (color(2) * Rinf);
        sigma_a = color(1);
        sigma_s = sigma_a / a_over_s;
    }
}

/* This function gives the reflection and transmission coefficients for the
 * layer. Given the reflection value, we might then use it in place of the
 * diffuse coefficient Kd in a standard light reflection model, such as 
 * Lambertian diffuse, or Oren-Nayer diffuse. For a thin translucent object
 * we might use both of them together and gather incident light from both sides
 * of the object. */
void KM(	color sigma_a, sigma_s;
			float thickness;
			output varying color R, T; )
{
    float i;
	extern uniform float ncomps;
	
    for (i = 0; i < ncomps; i += 1) {
        float s = comp(sigma_s, i), a = comp(sigma_a, i);
        float aa = (s+a)/s;
        float b = sqrt(max(aa*aa - 1., 0.));

        float sh, ch;
        sinhcosh(b*s*thickness, sh, ch);

        setcomp(R, i, sh / (aa * sh + b * ch));
        setcomp(T, i, b  / (aa * sh + b * ch));
    }
}

/* Computing the reflectivity of an infinitely-thin layer from the KM
 * scattering and attenuation parameters. */
color KMInfinite( color sigma_a, sigma_s; )
{
	float i;
	extern uniform float ncomps;
	
    color R = color(0);
    for (i = 0; i < ncomps; i += 1) {
        float a = comp(sigma_a, i) / comp(sigma_s, i);
        float r = 1. + a - sqrt(a*a + 2.*a);
        setcomp(R, i, r);
    }
    return R;
}

/* Given the reflectances and transmittances of two layers, compute the new
 * aggregate reflectance and transmittance of them together. */
color KMComposeR( color R1, T1, R2, T2; )
{
    return R1 + T1*R2*T1 / (color(1) - R1*R2);
}

color KMComposeT( color R1, T1, R2, T2; )
{
    return T1*T2 / (color(1) - R1*R2);
}

/* Function that computes shading for a composite surface where a diffuse layer
 * has been placed on top of a surface with a standard diffuse-glossy specular
 * shading model. We compute the Kubelka-Munk reflection and transmission
 * coefficients given sigmaA and sigmaS, and the thickness of the added layer,
 * compute a new diffuse reflection coefficient Kdnew and then compute
 * plausible values for the specular coefficients Ksnew and roughness, that
 * model the effect of the added layer on the light passing through it. */
color KMOverGlossy(	normal Nn;
					vector V;
					color Kd, Ks, thickcolor;
                   	float thickness, roughness;
					DECLARE_AOV_OUTPUT_PARAMETERS )
{
	color R1 = color(0), T1 = color(0);
	color sigma_a = color(0), sigma_s = color(0);

    normal Nf = faceforward( Nn, V, Nn);

	KMEstimateCoeffs( thickcolor, sigma_a, sigma_s );
    KM(sigma_a, sigma_s, thickness, R1, T1);

	color Kdnew = KMComposeR( R1, T1, Kd, color(0) );
	color Ksnew = KMComposeR( color(0), T1, Ks, color(0) );

    float KsRatio = comp( Ks, 0 ) / comp( Ksnew, 0 );
    float roughnew = roughness * KsRatio;

	aov_surfacecolor = Kdnew;
	aov_specularcolor = Ksnew;
	aov_diffuse = diffuse(Nf);
	aov_specular = specular(Nf, -V, roughnew);
	
	return aov_surfacecolor * aov_diffuse + aov_specularcolor * aov_specular;
}

////////////////////////////////////////////////////////////////////////////////
// Peter Stuart's implementation of the Granier-Heidrich thin film /////////////
// interference BRDF. //////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Slightly tweaked to fit Shrimp's structure. /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/************************************************************
 * file: granier.sl
 * author:  Peter Stuart <stuart@cis.ohio-state.edu>
 * date: 12/07/2002
 * $Id: granier.sl,v 1.1 2003/01/25 16:49:45 ophi Exp $
 * description: Thin film interference BRDF as described in
 * "A Simple layered RGB BRDF model" by Granier and Heidrich.
 *
 * ---- surface parameters ----------
 * N: normal direction of substrate
 * N1: normal of surface under substrate
 * V: view direction
 * e0: specular exponent for light reflected from substrate
 * e1: specular exponent for light reflected from surface
 * d: thickness of substrate
 * ior: rgb index of refraction for substrate
 * lambda: rgb wavelengths (use [645 525 445])
 * Kd: diffuse coefficient
 * Ks: specular coefficient
*/

color
LocIllumGranier(
					normal Nn, N1; vector Vf;
					float e0, e1, d;
					float ior[3]; float lambda[3];
					color SurfaceColor;
					float Kd, Ks;
					DECLARE_AOV_OUTPUT_PARAMETERS
					)
{

	/* initialize everything */
	float Kr = 0, Kt = 0, Kro = 0, Kto = 0;
	float specf = 0, difff = 0, td = 0;
	vector ti = vector(0), ri = vector(0);
	vector rti = vector(0), to = vector(0), ro = vector(0);
	color Cdiff = color(0), Cspec = color(0);
	color diff = color(0), spec = color(0);

	/****** perform diffuse first *********/
	uniform float i;
	for ( i = 0; i < 3; i += 1) {
		td = (80 / 21) * ( ior[i] / SQR( ior[i] + 1) );
		difff = 1 + 2 * cos( 4 * PI * ior[i] * d / lambda[i] )
				* sqrt( td * (1 - td) );
		setcomp( diff, i, difff/2 );
	}
	
	/****** specular *********/
	extern point P;

	illuminance(P, Nn, PI/2 )
	{
		extern vector L;
		extern color Cl;

		/* store preset quantities whenever possible */
		vector Ln = normalize(L);
		float maxndotl = max( 0, Nn.Ln );

		uniform float nondiff = 0, nonspec = 0;
		lightsource("__nondiffuse", nondiff);
		lightsource("__nonspecular", nonspec);
		
		if (nonspec < 1)
		{
			for ( i = 0; i < 3; i += 1) 
			{	
			/* construct reflected & refracted rays from L, V and substrate */
				fresnel( -Ln, Nn, 1/ior[i], Kr, Kt, ri, ti);
				fresnel( -Vf, Nn, 1/ior[i], Kro, Kto, ro, to);
				
				ri = normalize(ri);
				ti = normalize(ti);
				to = normalize(to);
				
				/* construct reflected ray from L refracted in substrate */
				rti = normalize( reflect( ti, N1 ) );
				
				/* total internal reflection */
				if ( (ti . N1) >= 0 || (to . N1) >= 0 || (rti . to) >= 0) {
					Kt = 0;
				}
				
				specf = Kr * pow( ri.Vf, e0) + Kt * Kto * pow( rti.-to, e1 );
				setcomp(spec, i, specf);
			}
			/* specular */
			Cspec += (1-nonspec) * Cl * spec * maxndotl;
		}

		/* diffuse term */
		if (nondiff < 1) {
			Cdiff += (1-nondiff) * Cl * diff * maxndotl;
		}
	}

	/* build AOVs */
	aov_surfacecolor += SurfaceColor;
	aov_diffuse += Kd * Cdiff;
	aov_specular += Ks * Cspec;
	
	return aov_surfacecolor * aov_diffuse + aov_specular;
}

////////////////////////////////////////////////////////////////////////////////
// Stephen Westin's implementation of the Lafortune model, with some data //////
// for the lobes, taken from version by Ryan Heniser (that you can find at /////
// The RenderMan Academy (www.rendermanacademy.com). ///////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Slightly tweaked for Shrimp's structure /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/*
 * lafortune.sl -- Implement the BRDF representation of Lafortune et al.
 *
 * DESCRIPTION:
 *	Implement the BRDF representation described in "Non-Linear
 *	Approximation of Reflectance Functions", by Eric P. F. Lafortune,
 *	Sing-Choong Foo, Kenneth E. Torrance, and Donald P. Greenberg, in
 *	SIGGRAPH 97 Proceedings.
 *
 * PARAMETERS:
 *   coeff:	Coefficients for each lobe. There will be
 *		3 coefficients per lobe per wavelength.
 *		for each lobe of Nlobes:
 *		  for each channel of N_WAVES:
 *		    cxy, cz, n
 *		where cxy, cz are the directional and scale components
 *		n is the exponent for the cosine
 *
 *   Cs:	Diffuse color of surface. This provides the diffuse
 *		term that is an integral part of the model. This
 *		will be the diffuse component from the Lafortune
 *		model multiplied by pi, as the RenderMan definition
 *		of reflectance is different.
 * colormatrix:	3x3 color transformation matrix, if needed.
 *		This is here because measured data may be in the
 *		RGB space of some sensor (e.g. a digital camera)
 *		and may need correction for display. Since the three
 *		channels are represented independently (i.e. each
 *		channel will have different directionality), this
 *		correction must be done on a per-pixel basis.
 *		Since the correction may be different for each
 *		shader, we must do it here. Default is the identity
 *		matrix.
 *
 * ANTIALIASING: should antialias itself fairly well
 *
 * AUTHOR: written by Stephen H. Westin, Cornell University Program of
 *	Computer Graphics
 *
 * HISTORY:
 *
 * initial version 22 March 1999 S. H. Westin
 *
 * 22 March 1999 S. H. Westin
 *		Flipped sign on Cx to agree with description in SIGGRAPH paper
 * 25 October 2000 S. H. Westin
 *		Multiply lobes by incident cosine.
 * 27 October 2000 S. H. Westin
 *		Multiply lobes by incident cosine. Before, I was trying to
 *		use diffuse(), which doesn't work.
 *
 */

/* Number of coefficients per lobe: 3 for an isotropic surface */
#define LOBESIZE 3
/* Number of wavelengths (wired in) */
#define N_WAVES 3
/* Number of lobes (wired in) */
#define Nlobes 3

#define COEFFLEN (LOBESIZE*N_WAVES*Nlobes)

/* Default BRDF: flat blue paint */
/* Use "Color  [ .3094 .39667 .70837 ]" for consistency with default */

color
lafortunersl (
				float Ka, Kd, Ks;
				color surfacecolor;
				uniform float coeff[27];
				uniform float colormatrix[9];
				normal Nn;
				vector V, dir;
				DECLARE_AOV_OUTPUT_PARAMETERS
				)
{
	
	varying vector local_z;
	varying vector local_x, local_y;/* Unit vector in "u" and "v" directions */
	varying vector Ln; /* Normalized vector to light */
	varying float x, z, f; /* subterms */
	varying float fr=0,fg=0,fb=0;/* RGB components of the non-Lambertian term */
	uniform float basepointer, j; /* loop counters */

	/* Get unit vector in "u" parameter direction */
	local_x = normalize ( dir );
	
	local_z = faceforward ( Nn, V);
	
	/* Get a local coordinate system. */
	local_y = local_z^local_x;
  
	/* The first term is the diffuse component. This should be the
	 * diffuse component in the Lafortune model multiplied by pi. */
	
	color cdiff = color(0), cspec = color(0);
		
	extern point P;
	
	illuminance ( P, local_z, PI/2 )
	{
		extern vector L;
		extern color Cl;

		Ln = normalize(L);
		
		uniform float nondiff = 0, nonspec = 0;
		lightsource("__nondiffuse", nondiff);
		lightsource("__nonspecular", nonspec);

		if (nondiff < 1) {
			cdiff += (1-nondiff) * Ln.local_z;
		}
		
		if (nonspec < 1) {
    
			/* Compute the terms
			 * x = x_in * x_view  +  y_in * y_view
			 * z = z_in * z_view
			 * */
			
			x = local_x.V * local_x.Ln + local_y.V * local_y.Ln;
			z = - ( local_z.V * local_z.Ln );

			/* Coefficient structures:
			 * * for each lobe of Nlobes:
			 * * for each channel of N_WAVES:
			 * * cxy, cz, n
			 * * where cxy, cz are the directional and scale components
			 * * and n is the exponent for the cosine
			 * */
			
			for ( basepointer=0; basepointer < COEFFLEN ;
					basepointer += LOBESIZE * N_WAVES )
			{
				uniform float rexponent = coeff[basepointer+2],
							  gexponent = coeff[basepointer+LOBESIZE+2],
							  bexponent = coeff[basepointer+2*LOBESIZE+2];
				
				fr = fg = fb = 0.0;
				f = -x * coeff[basepointer] + z * coeff[basepointer+1];
				
				if ( f > 0.001*rexponent ) {
					fr = pow ( f, rexponent );
				}
				
				f = -x * coeff[basepointer+LOBESIZE] 
					+ z * coeff[basepointer+LOBESIZE+1];
				
				if ( f > 0.001*gexponent ) {
					fg = pow ( f, gexponent );
				}
				
				f = -x * coeff[basepointer+2*LOBESIZE]
					+ z * coeff[basepointer+2*LOBESIZE+1];
				
				if ( f > 0.001*bexponent ) {
					fb = pow ( f, bexponent );
				}
			}

			cspec += Cl * (1-nonspec) * color "rgb" (fr,fg,fb)
						* (local_z.Ln);
		}
	}
	
	/* Color correction from camera space */
	/* use dot product with rows of matrix */
	
	fr = colormatrix[0]*comp(cspec,0)
		+ colormatrix[1]*comp(cspec,1) + colormatrix[2]*comp(cspec,2);
	fg = colormatrix[3]*comp(cspec,0)
		+ colormatrix[4]*comp(cspec,1) + colormatrix[5]*comp(cspec,2);
	fb = colormatrix[6]*comp(cspec,0)
		+ colormatrix[7]*comp(cspec,1) + colormatrix[8]*comp(cspec,2);
	
	cspec = color "rgb" ( fr, fg, fb );

	aov_surfacecolor += surfacecolor;
	aov_ambient += Ka * ambient();
	aov_diffuse += Kd * cdiff;
	aov_specular += Ks * cspec;
	
	return aov_surfacecolor * (aov_ambient + aov_diffuse) + aov_specular;
}

////////////////////////////////////////////////////////////////////////////////
// based on ATI's paper 'Hair Rendering and Shading', by Thorsten Scheuermann //
// 3D application research group, ATI research Inc. ////////////////////////////
// this is a hair rendering technique originally made for polygon hair models //
// a mix of Kajiya-Kay hair shader model, and Marscher's model, presented at  //
// Siggraph2003 ////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

// shifting specular highlights along lenght of hair
vector shifttangent(
					vector Tn;
					normal Nf;
					float shift;
		)
{
	vector shiftedt = Tn + shift * Nf;
	return normalize(shiftedt);
}

/* Specular strand lighting */
float strandspecular(
						vector Tn, Vn, Ln;
						float exponent;
		)
{
	vector Hn = normalize(Ln + Vn);
	float dotth = Tn.Hn;
	float sinth = max( 0.0, sqrt( 1.0 - dotth * dotth ) );
	float diratten = smoothstep(-1.0, 0.0, dotth);
	return diratten * pow( sinth, exponent);
}

/* Main */
color tshair(
					float Ka, Kd, Ks; //ambient, diffuse, specular coefficients
					float shift; // primary specular highlight shift
                    float shift2; // secondary specular highlight shift
					float exponent; // primary specular exponent
                    float exponent2; // secondary specular exponenet
                    float specmask; // specular mask, to shift secondary spec
					color Cdiff; // surface color,sometimes bound to geo
					color Cbase; // hair base color
					color Ctip; // hair tip color
					color Cspec; // primary specular color
                    color Cspec2; // secondary specular color
					normal Nn; // normal vector
					vector Vf; // viewer vector
					DECLARE_AOV_OUTPUT_PARAMETERS
		)
{
	/* We're going to need dPdv for direction, P for the illuminance
	 * construct, and the v coordinate for the color blend in the color
	 * contribution. */
	
	extern vector dPdv;
	extern point P;
	extern float v;
	
	vector T = normalize(dPdv);
	normal Nf = faceforward( Nn, Vf );
	
    vector t1 = shifttangent( T, Nf, shift - .5);
    vector t2 = shifttangent( T, Nf, shift2 - .5);
	
	float dottin = T.Vf;

	color Cdd = color(0);
	color Css = color(0);
	
	illuminance( P, Nf, PI/2 )
	{
		extern vector L;
		extern color Cl;
		vector Ln = normalize(L);
		
		uniform float nondiff = 0, nonspec = 0;
		lightsource("__nondiffuse", nondiff);
		lightsource("__nonspecular", nonspec);
		
		if (nondiff < 1) {
			/* Scaled diffuse term. Note that in the paper they use
			 * ambient occlusion to fake the hair shadowing. */
			Cdd = clamp( mix( .25, 1.0, Nf.Ln), 0, 1);
		}
		
		if (nonspec < 1) {
			/* Primary specular */
    	    Css = Cspec * (1-nonspec) *  strandspecular( t1, Vf, Ln, exponent);

        	/* Secondary specular */
        	Css += Cspec2 * (1-nonspec) * specmask *
				strandspecular( t2, Vf, Ln, exponent2);
		}
	}

	aov_surfacecolor += mix( Cbase, Ctip, v);
	aov_ambient += Ka * ambient();
	aov_diffuse += Kd * Cdd;
	aov_specular += Ks * Css;

	return aov_surfacecolor * (aov_ambient + aov_diffuse) + aov_specular;
}

////////////////////////////////////////////////////////////////////////////////
// Hair shader, Kajiya-Kay model, based on Mario Marengo's work, from //////////
// http://forums.odforce.net/index.php?showtopic=2208&st=180 ///////////////////
// slightly tweaked for shrimp /////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

color kajiyakay(
					float Ka, Kd, Ks; //ambient, diffuse, specular coefficients
					float rough; // specular roughness
					color Cdd; // "hidden" surface color,sometimes bound to geo
					color Cbase; // hair base color
					color Ctip; // hair tip color
					color Css; // specular color
					normal Nn; // normal vector
					vector Vf; // viewer vector
					DECLARE_AOV_OUTPUT_PARAMETERS
		)
{
	/* We're going to need dPdv for direction, P for the illuminance
	 * construct, and the v coordinate for the color blend in the color
	 * contribution. */
	extern vector dPdv;
	extern point P;
	extern float v;
	
	vector T = normalize(dPdv);
	normal Nf = faceforward( Nn, Vf );
	
	float dottin = T.Vf;

	color Cdiff = color(0);
	color Cspec = color(0);
	float dottl, sdottl;
	
	illuminance( P, Nf, PI/2 )
	{
		extern vector L;
		extern color Cl;
		vector Ln = normalize(L);
		
		uniform float nondiff = 0, nonspec = 0;
		lightsource("__nondiffuse", nondiff);
		lightsource("__nonspecular", nonspec);
		
		/* Diffuse term */
		if (nondiff < 1) {
			dottl = T.Ln;
			sdottl = max( 0.0, sqrt( 1.0 - dottl * dottl ));
			Cdiff += Cl * (1-nondiff) * sdottl;
		}
		
		/* Specular term */
		if (nonspec < 1) {
			dottl = T.Ln;
			sdottl = max( 0.0, sqrt(1.0 - dottl * dottl));
			Cspec += Cl * (1-nonspec) * pow(dottl*dottin + sdottl
						*sqrt(1.0 - dottin*dottin), 1.0/rough);
		}
	}
	
	/* blend base color and tip color based on v coordinate */
	aov_surfacecolor = Cdd * mix( Cbase, Ctip, v);
	aov_specularcolor = Css;
	aov_ambient = Ka * ambient();
	aov_diffuse = Kd * Cdiff;
	aov_specular = Ks * Cspec;
		
	return aov_surfacecolor * (aov_ambient + aov_diffuse) +
				(aov_specularcolor * aov_specular);
}

////////////////////////////////////////////////////////////////////////////////
// Gooch Non-PhotoRealistic shading model, by Mike King ////////////////////////
// taken from The RenderMan Repository, http://www.renderman.org ///////////////
////////////////////////////////////////////////////////////////////////////////
// slightly tweaked to fit shrimp's structure //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* Renamed to MKgooch.sl for RMR -- tal AT renderman DOT org */

/* s_gooch.sl - a simple implementation of the Gooch
 *              non-photorealistic lighting model
 *
 * DESCRIPTION   : This model is described in "A Non-Photorealistc
 *                 Lighting Model For Automatic Technical 
 *                 Illustration" in the Siggraph 1998 Proceedings.
 *                 http://www.cs.utah.edu/~gooch/SIG98/abstract.html
 *
 * INPUTS        : 
 *  Ka           : ambient factor
 *  Kd           : diffuse factor
 *  Ks           : specular factor
 *  alpha        : Gooch cool color factor
 *  beta         : Gooch warm color factor
 *  b            : used to construct the cool color
 *  y            : used to construct the warm color
 *  roughness    : specular roughness
 *  specularcolor: specular hilight color
 *
 * AUTHOR: written by Mike King
 *               
 ***************************************************/

color MKgooch(
                normal Nn;
                vector In;
                float Ka, Kd, Ks, calpha, cbeta, roughness, b, y;
                color SurfaceColor, SpecularColor;
				DECLARE_AOV_OUTPUT_PARAMETERS
                )
{
    normal Nf = faceforward( Nn, In);
    vector Vf = -In;
    
    color blue = color(0, 0, b);
    color yellow = color(y, y, 0);
    color cgooch = color(0);
    
    float ldotn, blendval;
    color kcool, kwarm;

    kcool = blue + (SurfaceColor * calpha);
    kwarm = yellow + (SurfaceColor * cbeta);
    
    extern point P;
	
    illuminance( P, Nf, PI)
	{
        extern vector L;
        vector Ln = normalize(L);
        
        ldotn = Ln.Nf;
        blendval = .5 * (1+ldotn);
        cgooch += mix( kcool, kwarm, blendval);
    }
	
	aov_surfacecolor += SurfaceColor;
	aov_specularcolor += SpecularColor;
	aov_ambient += Ka * ambient();
	aov_diffuse += Kd * cgooch;
	aov_specular += Ks * specular( Nf, Vf, roughness);

	return aov_ambient + aov_diffuse + aov_specularcolor * aov_specular;	
}

////////////////////////////////////////////////////////////////////////////////
// Stephen H. Westin's wood shader, Cornell University Program of Computer /////
// Graphics. REFERENCE: Stephen R. Marschner, Stephen H. Westin, Adam Arbree ///
// and Jonathan T. Moon, "Measuring and Modelling the Appearance of Finished ///
// Wood", SIGGRAPH 2005. ///////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
// Slightly tweaked to fit Shrimp's structure. /////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* Note: Mario Marengo mentioned a problem (and a solution) regarding specifying
 * surface tangents to build the local space of the fiber vectors - we need
 * to extract texture gradients from the geometry. */

/*
 * woodreflectance.sl -- wood (anisotropic)
 *
 * DESCRIPTION:
 *   Simple wood shader, driven by four textures:
 *    RGB diffuse color
 *    RGB fiber (anisotropic highlight) color
 *    x,y,z of unit vector giving local fiber orientation in local
 *      coordinates
 *    beta, a "roughness" parameter to control width of highlight.
 *   If any of these files is not specified, we fall back on a
 *    uniform parameter. So far, every map has had uniform beta.
 *
 * PARAMETERS:
 *
 *   diffuse_texture: name of file containing 3-channel texture
 *     modulating color across the patch.
 *
 *   fiber_texture: name of file containing 3-channel texture
 *     modulating fiberColor across the patch. This map is divided by
 *     20 because it generally contains values greater than 1, which
 *     would be clamped in an integer pixel format.
 *
 *   axis_texture: name of file containing 3-channel texture
 *     modulating fiberAxis across the patch. Values are mapped
 *     [0:max] -> [-1:1] for each component, since most image file
 *     formats are unsigned.
 *
 *   beta_texture: name of file containing 1-channel texture
 *     modulating beta across the patch.
 *
 *   eta: Index of refraction of surface finish. Used to modulate
 *     highlight and subsurface with varying angle. eta=0 used to
 *     signal absence of overcoat.
 *
 *   color, fiberColor: fallback diffuse and directional colors if
 *     texture is missing
 *
 *   fiberAxis: fallback fiber direction if texture is missing
 *
 *   beta: width of subsurface highlight if texture is missing
 *
 *   roughness: width of surface (white) highlight
 *
 *   Ka, Kd, Ks: normal Renderman coefficients. Ka and Kd modulate the
 *     diffuse component (parameter "color"), and Ks is a fudge factor
 *     on the surface (white) highlight.
 *
 * ANTIALIASING: provided by texture lookup
 *
 * REFERENCE: Stephen R. Marschner, Stephen H. Westin,
 *              Adam Arbree, and Jonathan T. Moon,
 *            "Measuring and Modeling the Appearance of
 *               Finished Wood", SIGGRAPH 2005
 *
 * AUTHOR: written by Stephen H. Westin,
 *                    Cornell University Program of
 *                    Computer Graphics
 *         last modified by $Author: westin $
 *
 * VERSION: $Revision: 1.2 $
 *
 * HISTORY:
 * $Log: woodreflectance.sl,v $
 * Revision 1.2  2005/05/10 20:02:15  westin
 * Modified to use 4 TIFF texture maps rather than a single
 *  10-channel map.
 *
 * Revision 1.1  2005/05/09 21:10:18  westin
 * Working version of shader; used for animation on Proceedings DVD-ROM.
 *
 */

color
woodreflectance(
                    float eta, beta, roughness;
                    float Ka, Kd, Ks;
                    vector fiberAxis, In;
                    normal Nn;
                    color diffuseColor, fiberColor;
					DECLARE_AOV_OUTPUT_PARAMETERS
        )
{
    uniform float sqrt2pi = 2.5066283;
    extern vector dPdu;
    extern float u, v;
    extern point P;

    vector local_z;             /* Surface normal in "world" space */
    vector local_x, local_y;    /* Unit vector in "u" and "v" direction */

    normal Nf = faceforward( Nn, In);
    color highlight;
    vector axis;
    float tx_beta;
    vector Rdir = vector(0); /* Dummy */

    vector ssInDir, ssOutDir; /* Light and eye vector, possibly refracted */
    float thInPrime, thOutPrime;
    float halfAngle, diffAngle;
    float fiberFactor, geometryFactor;

    float Kr, Kt;           /* for output of fresnel() */
    float ssAtten;          /* Attenuation from going through the smooth
                             * interface twice */
    
    /* Get local coordinate system in terms of native parameters (u, v).
     * We should really use (s, t). */
    local_z = Nf;
	
    /* Get unit vector in "u" parameter direction */
    local_x = normalize( dPdu );
	
    /* Get final local basis vector y perpendicular to x and z. */
    local_y = local_z ^ local_x;

    /* If there is a clear overcoat, calculate refraction direction and
     * attenuation. */
    if ( eta != 1.0 ) {
        fresnel ( In, Nf, 1.0/eta, Kr, Kt, Rdir, ssOutDir );
        ssOutDir = -ssOutDir;
        /* Use (1-Kr) rather than Kt, because we are dealing with power,
         * not radiance. */
        ssAtten = 1 - Kr;
    } else {
        ssOutDir = -In;
        ssAtten = 1.0;
    }
    normalize(ssOutDir);

    color axisTemp;
    highlight = fiberColor;
    axis = comp( fiberAxis, 0 ) * local_x + comp( fiberAxis, 1 ) * local_y +
            comp( fiberAxis, 2 ) * local_z;
    normalize(axis);    
    tx_beta = beta;
    thOutPrime = asin( ssOutDir.axis);

    /* Calculate anisotropic highlight for each light */	
    illuminance( P, Nf, PI/2 /* Hemisphere */ ) {
		
        extern vector L;
        extern color Cl;
		
        vector Ln = normalize(L);
		float dummy, ssAttenOut;

        /* Refract at smooth surface */
        if ( eta != 1.0 ) {
            fresnel( -Ln, local_z, 1.0/eta, Kr, Kt, Rdir, ssInDir);
            /* Use (1-Kr) rather than Kt, because we are dealing with power,
             * not radiance. */
            ssAttenOut = 1 - Kr;
        } else {
            ssInDir = -Ln;
            ssAttenOut = 1.0;
        }

        float ssFactor = max( 0, -ssInDir.local_z) * ssAtten*ssAttenOut;
        thInPrime = asin( -ssInDir.axis);
        halfAngle = thOutPrime + thInPrime;
        diffAngle = thOutPrime - thInPrime;
		
        /* Compute value of Gaussian at this angle */
        fiberFactor = tx_beta * exp( -pow( halfAngle / tx_beta, 2)/2 )
                                / sqrt2pi;
        float cosIncline = cos( diffAngle / 2);
        geometryFactor = 1 / pow( cosIncline, 2);
        fiberFactor *= geometryFactor;
		
        /* Add in diffuse term, attenuated by surface term. */
        aov_diffuse += Cl * Kd * ssFactor;
		
        /* Add in fiber highlight, also attenuated. */
        aov_specular += Cl * fiberFactor * highlight * ssFactor;
		
        /* Second Fresnel call is for strength of surface highlight. */
        vector Hn = normalize( -In + Ln );
        fresnel( In, Hn, 1.0/eta, Kr, Kt);
		
        /* Blinn/Phong highlight with Fresnel attenuation. */
        aov_specular += Cl * Ks * Kr * pow( max( 0, Hn.local_z), 1/roughness);
    }
	
	aov_surfacecolor += diffuseColor;
	aov_ambient += Ka * ambient();

	return aov_surfacecolor * (aov_ambient + aov_diffuse) + aov_specular;
}

////////////////////////////////////////////////////////////////////////////////
// Raytraced glass shader, based on Larry Gritz's glass shader, and on Mario ///
// Marengo's glass shader (altough not even remotely as good/complete as ///////
// Mario's VEX shader). The Larry Gritz glass shader was taken from ////////////
// The RenderMan Repository - http://www.renderman.org  ////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* Tweaked to fit Shrimp's structure and needs, added attenuation, blend
 * factors for reflection and refraction, as Mario Marengo suggested in his
 * VEX glass shader ( http://forums.odforce.net/index.php?showtopic=4196 ).
 * Dispersion, or optics tables not added yet. (TODO?). */

/* Compute the color of a glass-like surface with coherent reflections
 * and refractions.
 * */

/* LocIllumGlossy, but we already have Nf and Vf set in the glass body */
color
locillumglassy(
				normal Nf;
				vector Vf;
				float roughness, sharpness;
		)
{
	float w = .18 * (1 - sharpness);
	
	extern point P;
	color C = color(0);
	
	illuminance( P, Nf, PI/2)
	{
		extern vector L;
		extern color Cl;

		uniform float nonspec = 0;
		lightsource("__nonspecular", nonspec);
		
		if (nonspec < 1) {
			vector Ln = normalize(L);
			vector Hn = normalize(Ln + Vf);
			C += Cl * ((1 - nonspec) * smoothstep(.72-w, .72+w,
						pow( max( 0, Nf.Hn), 1/roughness)));
		}
	}
	return C;
}

/* glass body */
color
rtglass(
			float Ka, Kd, Ks, Kr, Kt, ior, roughness, sharpness;
			color basecolor, attencolor;
			float krblur, ktblur, aexp, aamp;
			uniform float samples, refrmaxdist, reflmaxdist;
			uniform string spectype;
			uniform float rbounces, sbounces, krefl, krefr;
			vector In; normal Nn;
			uniform string envmap;
			DECLARE_AOV_OUTPUT_PARAMETERS
	   )

{
	
#if RENDERER == pixie
	/* Pixie's shader compiler protests about the binary conditionals, so
	 * do nothing - there's a custom version of the glass shader for Pixie
	 * further below.
	 * (read: lame excuse to use Pixie's built-in dispersion later :)) */
#else
	normal Nf = faceforward( Nn, In );
	float idotn = In.Nn; /* need to know the face orientation, hence Nn */

	vector refldir = vector(0), refrdir = vector(0);
	float kr = 0, kt = 0;

	/* if I.N>0, ray is entering the medium, else ray is exiting and eta is the
	   reverse of the ior when ray is entering the medium. */
	float entering = (idotn > 0) ? 1 : 0;
	float eta = (idotn > 0) ? ior : 1/ior;

	/* If we're inside medium, reverse the normals for internal reflections */
	normal Tn = (entering == 1) ? -Nn : Nn ;

	fresnel( In, Tn, eta, kr, kt, refldir, refrdir);

	kt = 1 - kr; /* physically incorrect but portable */
	kr *= Kr; kt *= Kt;

	/* get current ray depth and scale down samples as ray depth goes up */
	/* if needed */
	uniform float raydepth = 0;
	rayinfo("depth", raydepth);
	uniform float rsamples = (raydepth > 1) ? max( 1, samples /
								pow( 2, raydepth)) : samples ;

	/* we don't need ambient nor diffuse at higher ray levels (if at all?).
	 * As for speculars, restricted to number of specular bounces, if faces
	 * are facing outwards only. Note: scale specular by fresnel term?
	 * What about diffuse? Wolff's smooth dielectric surfaces model ? */
	float ka = (raydepth > 0) ? 0 : Ka;
	float kd = (raydepth > 0) ? 0 : Kd;
	float ks = (raydepth > sbounces || entering == 1) ? 0 : Ks;
	kr = (raydepth > rbounces) ? 0 : kr;

	color crefl = color(0), crefr = color(0);

	/* should be raytrace, but added envmap, just in case */
	if (kr > 0) /* reflections, if active */
		crefl = environment( envmap, refldir, "samples", rsamples,
					"blur", krblur, "maxdist", reflmaxdist );
	if (kt > 0) /* refractions, if active */
		crefr = environment( envmap, refrdir, "samples", rsamples,
					"blur", ktblur, "maxdist", refrmaxdist );

	/* attenuation, when there are ray hits */
	extern vector I; /* we just passed the normalized viewer as argument
						but we need the ray lenght */
	color attenrefl = 1, attenrefr = 1;
	if (raydepth > 0 && (kr > 0 || kt > 0)) {
		float ilen = length(I);
		float d = (aamp == 1) ? ilen * aexp : pow( ilen, aamp) * aexp;
		if (ilen < 1e38) { /* consider ray hits only (restrict to maxdist?) */
			color atten = (attencolor != color(1)) ?
				color( exp( comp( attencolor,0) * -d),
					   exp( comp( attencolor,1) * -d),
					   exp( comp( attencolor,2) * -d) ) : color(1);
			attenrefr *= (kt > 0 && entering == 0) ? atten : color(1);
			attenrefl *= (kr > 0 && entering == 1) ? atten : color(1);
		}
	}
	
	/* Well, Aqsis doesn't supports raytracing yet, but we might as well
	 * just leave everything in place (there's always frankenrender,
	 * but i haven't tested it this way (w/BMRT's rayserver)) */
#if RENDERER == aqsis
	if (Ka > 0) aov_ambient +=  Ka * ambient();
	if (Kd > 0) aov_diffuse += Kd * diffuse(Nf);
	if (Ks > 0) {
		if (spectype == "glossy")
			aov_specular += locillumglassy( Nf, -In, roughness, sharpness);
		else aov_specular += specular(Nf, -In, roughness);
	}
	/* attenuation blends */
	if (Kr > 0) {
		if (krefl > 0) aov_reflection += mix( kr * crefl, kr * crefl
						* attenrefl, krefl);
		else aov_reflection += kr * crefl;
	}
	if (Kt > 0) {
		if (krefr > 0) aov_refraction += mix( kt * crefr, kt * crefr
						* attenrefr, krefr);
		else aov_refraction += kt * crefr;
	}
#else
	
	/* set illumination terms, if active */
	aov_ambient += (ka == 0) ? color(0) : ka * ambient();
	aov_diffuse += (kd == 0) ? color(0) : kd * diffuse(Nf);
	aov_specular += (ks == 0) ? color(0) : ks * ( (spectype == "glossy" ) ?
					locillumglassy( Nf, -In, roughness, sharpness) :
					specular( Nf, -In, roughness) );
	
	/* blend between pure and attenuated medium */
	aov_reflection += (kr == 0) ? color(0) : ( (krefl == 0) ? kr * crefl :
						mix( kr * crefl, kr * crefl * attenrefl, krefl ) ) ;
	aov_refraction += (kt == 0) ? color(0) : ( (krefr == 0) ? kt * crefr :
						mix( kt * crefr, kt * crefr * attencolor
							* attenrefr, krefr ) );
	
#endif

#endif
	
	return aov_ambient + aov_diffuse + aov_specular + aov_reflection
						+ aov_refraction;
}

/* Pixie doesn't likes binary conditionals, we might as well make a custom
 * version (and using Pixie's dispersion effect, TODO later). */

color
rtglasspixie(
			float Ka, Kd, Ks, Kr, Kt, ior, roughness, sharpness;
			color basecolor, attencolor;
			float krblur, ktblur, aexp, aamp;
			uniform float samples, refrmaxdist, reflmaxdist;
			uniform string spectype;
			uniform float rbounces, sbounces, krefl, krefr;
			vector In; normal Nn;
			uniform string envmap;
			DECLARE_AOV_OUTPUT_PARAMETERS
	   )

{
	normal Nf = faceforward( Nn, In );
	float idotn = In.Nn; /* need to know the face orientation, hence Nn */

	vector refldir = vector(0), refrdir = vector(0);
	float kr = 0, kt = 0;

	/* if I.N>0, ray is entering the medium, else ray is exiting and eta is the
	   reverse of the ior when ray is entering the medium. */
	float entering = 0;
	float eta = 1 / ior;
	normal Tn = Nn;

	if (idotn > 0) {
		entering = 1; eta = ior;
		Tn = -Nn; /* we're inside the medium, so reverse surface normals */
	}

	fresnel( In, Tn, eta, kr, kt, refldir, refrdir);

	kt = 1 - kr; /* physically incorrect but portable */
	kr *= Kr; kt *= Kt;

	/* get current ray depth and scale down samples as ray depth goes up */
	/* if needed */
	uniform float raydepth = 0;
	rayinfo("depth", raydepth);
	uniform float rsamples = samples;
	if (raydepth > 1) rsamples = max(1, samples/pow( 2, raydepth));

	/* we don't need ambient nor diffuse at higher ray levels (if at all?).
	 * As for speculars, restricted to number of specular bounces, if faces
	 * are facing outwards only. Note: scale specular by fresnel term?
	 * What about diffuse? Wolff's smooth dielectric surfaces model ? */
	float ka = Ka, kd = Kd, ks = Ks;
	if (raydepth > 0) {
		kd = 0; kd = 0;
	}
	if (raydepth > sbounces || entering == 1) ks = 0;
	if (raydepth > rbounces) kr = 0;

	color crefl = color(0), crefr = color(0);

	/* should be raytrace, but added envmap, just in case */
	if (kr > 0) /* reflections, if active */
		crefl = environment( envmap, refldir, "samples", rsamples,
					"blur", krblur, "maxdist", reflmaxdist );
	if (kt > 0) /* refractions, if active */
		crefr = environment( envmap, refrdir, "samples", rsamples,
					"blur", ktblur, "maxdist", refrmaxdist );


	/* attenuation, when there are ray hits */
	extern vector I; /* we just passed the normalized viewer as argument
						but we need the ray lenght */
	color attenrefl = 1, attenrefr = 1;
	if (raydepth > 0 && (kr > 0 || kt > 0)) {
		float ilen = length(I);
		float d = pow( ilen, aamp) * aexp;
		color atten = color ( exp( comp( attencolor, 0) * -d),
								exp( comp( attencolor, 1) * -d),
								exp( comp( attencolor, 2) * -d) );
		if (kt > 0 && entering == 0) attenrefr *= atten;
		if (kr > 0 && entering == 1) attenrefl *= atten;
	}

	if (ka > 0) aov_ambient +=  Ka * ambient();
	if (kd > 0) aov_diffuse += Kd * diffuse(Nf);
	if (ks > 0) {
		if (spectype == "glossy")
				aov_specular += locillumglassy( Nf, -In, roughness, sharpness);
		else aov_specular += specular(Nf, -In, roughness);
	}
	/* attenuation blends */
	if (kr > 0) {
		if (krefl > 0) aov_reflection += mix( kr * crefl, kr * crefl
											* attenrefl, krefl);
		else aov_reflection += kr * crefl;
	}
	if (kt > 0) {
		if (krefr > 0) aov_refraction += mix( kt * crefr, kt * crefr
											* attenrefr, krefr);
		else aov_refraction += kt * crefr;
	}
		
	return aov_ambient + aov_diffuse + aov_specular + aov_reflection +
			aov_refraction;
}

////////////////////////////////////////////////////////////////////////////////
// David C. Banks fast anisotropic model, from: ////////////////////////////////
// "Illumination in Diverse Codimensions". /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

color
banksaniso(
			color cdiff, cspec;
			float Kd, Ks, roughness;
			normal Nn;
			vector In, adir;
			DECLARE_AOV_OUTPUT_PARAMETERS
		)
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -In;
	vector xdir = normalize( adir );

	float costheta = Vf.xdir;

	extern point P;

	illuminance( P, Nf, PI/2 )
	{
		extern vector L;
		extern color Cl;

		vector Ln = normalize(L);
		float cospsi = Ln.xdir;
		float pd = 1;

		uniform float nondiff = 0, nonspec = 0;
		lightsource("__nondiffuse", nondiff);
		lightsource("__nonspecular", nonspec);

		if (nondiff < 1) {
			
			pd = sqrt( 1 - cospsi * cospsi);
			float ldotn = Ln.Nf;
			aov_diffuse += (1-nondiff) * Cl * ldotn * Kd * pd;
		}

		if (nonspec < 1) {

			float ps = sqrt( 1 - costheta * costheta );
			float ldotn = Ln.Nf;
			aov_specular += (1-nonspec) * Cl * ldotn * Ks *
							pow( pd*ps - cospsi*costheta, 1/roughness);
		}
	}
	return (cdiff * aov_diffuse) + (cspec * aov_specular);
}

////////////////////////////////////////////////////////////////////////////////
// Paul S.Strauss empirical BRDF, from :  //////////////////////////////////////
// "A Realistic Lighting Model for Computer Animators" /////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* Model constants */
#define KF	1.12	/* Fresnel adjustment constant */
#define KG	1.01	/* Geometric attenuation adjustment constant */
#define	KJ	0.10	/* Specular reflectivity adjustment constant */

/* Surface white color */
#define CWHITE	color( 1, 1, 1)

/* Strauss's fresnel approximation (expects angles in radians, not cosine
 * of angles, which are then divided by PI/2 to fit the expected parameter
 * range [0,1], and the same for the geometric attenuation approximation. */
float straussfresnel( float x; )
{
	float f1 = 4 * SQR(KF-1) * x * (x-PI*KF);
	float f2 = (2*KF-1) * SQR(2*x-PI*KF);
	return -(f1 / f2);
}

/* Strauss's geometric attenuation approximation */
float straussgeoatten( float x; )
{
	float g1 = SQR(KG) * (2*x-PI) * (2*x-2*PI*KG+PI);
	float g2 = (2*KG-1) * SQR(2*x-PI*KG);
	return g1 / g2;
}

color strauss(
				color Csurface;
				/* smoothness [0,1] = perfect diffuse/specular
				 * metalness  [0,1] = perfect nonmetal/metal */
				float smoothness, metalness;
				float transparency;
				normal Nn; vector In; /* normalized normal/viewer */
				DECLARE_AOV_OUTPUT_PARAMETERS
		)
{
	normal Nf = faceforward( Nn, In );
	vector Vf = -In;

	/* preset quantities */
	float cosgamma = Vf.Nf;
	
	/* attenuate diffuse reflection for metallic surfaces */
	float d = (1 - metalness * smoothness);
	
	/* diffuse reflectivity as function of roughness and transparency */
	float rd = (1 - pow( smoothness, 3)) * (1 - transparency);

	/* specular reflectivity at normal incidence */
	float rn = (1 - transparency) - rd;
	/* shininess exponent h */
	float h = 3 / (1-smoothness);

	extern point P;
	color Cdiff = color(0), Cspec = color(0);

	illuminance( P, Nf, PI/2 )
	{
		uniform float nondiff = 0, nonspec = 0;
		lightsource("__nondiffuse", nondiff);
		lightsource("__nonspecular", nonspec);

		extern vector L;
		extern color Cl;

		vector Ln = normalize(L);
		/* preset quantities */
		float cosalpha = Ln.Nf;

		/* diffuse contribution */
		if (nondiff < 1) {
			Cdiff += Cl * (1-nondiff) * rd * d * cosalpha;
		}
		
		/* specular contribution */
		if (nonspec < 1) {
			
			vector Hn = normalize(Ln + Vf);

			/* preset quantities */
			float ralpha = acos( cosalpha );

			/* reflectivity adjustment to account for off-specular peaks */
			float F = straussfresnel( ralpha );
			float j = F * straussgeoatten( ralpha ) *
							straussgeoatten( acos( cosgamma ) );
			
			/* adjusted reflectivity */
			float rj = min( 1, rn + (rn + KJ) * j);

			/* specular reflectivity */
			float rs = pow( max( 0, Nf.Hn), h) * rj;

			/* specular color, approaching white at grazing angles */
			color Csw = CWHITE + metalness * (1-F) * (Csurface - CWHITE);

			Cspec += Cl * (1-nonspec) * rs * Csw * cosalpha;
		}
	}

	aov_surfacecolor += Csurface;
	aov_diffuse += Cdiff;
	aov_specular += Cspec;
	
	return aov_surfacecolor * aov_diffuse + aov_specular;
}

////////////////////////////////////////////////////////////////////////////////
// Fur surface shader, by Clint Hanson and Armin Bruderlin, from ///////////////
// The RenderMan Repository - www.renderman.org ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* slightly tweaked to fit shrimp's structure */

/* Renamed to SIG2k_srf_fur to be consistent with the RMR
 * -- tal AT renderman DOT org
 * */

/* fur shader shader, wich clumping and specular model, by Clint Hanson,
 * and Armin Bruderlin. */

color
fnc_diffuselgt(
				color Cin; /* Light color */
				vector Lin; /* Light position */
				vector Nin; /* Surface normal */
		)
{
	color Cout = Cin;
	vector LN, NN;
	float Atten;

	/* normalize the stuff */
	LN = normalize( Lin );
	NN = normalize( Nin );

	/* diffuse calculation */
	Atten = max( 0, LN.NN );

	Cout *= Atten;
	
	return (Cout);
}

#ifndef luminance
#define luminance(c)	comp(c,0)*0.299 + comp(c,1)*0.587 + comp(c,2)*.114
#endif

/* main */

color
SIG2k_srf_fur(
				float Ka, Kd, Ks; /* usual meaning */
				float roughness1, roughness2, spec1, spec2;
				float start_spec, end_spec, spec_size_fade;
				float illum_width, var_fade_start, var_fade_end;
				float clump_dark_strength;
				/* Hair color */
				color rootcolor, tipcolor, specularcolor, static_ambient;
				/* Variables passed from the RIB */
				uniform float hair_col_var, hair_length, hair_id;
				uniform normal surface_normal;
				varying vector clump_vect;
				DECLARE_AOV_OUTPUT_PARAMETERS
		)
{
	extern vector dPdv, I; /* we're in a function */
	
	vector T = normalize(dPdv); /* tangent along length of hair */
	vector V = -normalize(I); /* view vector */
	float Kspec = Ks; /* Specular coefficient copy */
	
	vector nL;
	varying normal nSN = normalize( surface_normal );
	vector S = nSN^T; /* Cross product of tangent along hair & surface normal */
	vector N_hair = (T^S) ; /* normal for hair oriented away from surface */
	vector norm_hair;

	float l = clamp( nSN.T, 0, 1 ); /* T and surface normal dot for blend */
	float clump_darkening = 1.0;
	float T_Dot_nL = 0;
	float T_Dot_e = 0;
	float Alpha = 0, Beta = 0, Kajiya = 0, darkening = 1.0;

	/* values from light */
	uniform float nonspecular = 0;
	uniform color SpecularColor = color(1);

	/* When the hair is exactly perpendicular to the surface, use the surface
	 * normal, when the hair is exactly tangent to the surface, use the hair
	 * normal, otherwise, blend between the two normals in a linear fashion. */
	norm_hair = (l * nSN) + ( (1-l) * N_hair);
	norm_hair = normalize( norm_hair );

	/* Make the specular only hit in certain parts of the hair. V is along the
	 * length o fthe hair. */
	extern float v;
	Kspec *= min( smoothstep( start_spec, start_spec + spec_size_fade, v),
				1 - smoothstep( end_spec, end_spec - spec_size_fade, v ) );

	/* Loop over lights, catch highlights as if this was a thin cylinder.
	 * Specular illumination model from James T. Kajiya and Timothy L. Kay,
	 * (1989) "Rendering Fur with Three Dimensional Textures", Computer
	 * Graphics 23, 3, 271-280. */

	extern point P;
	color C = color(0);
	
	illuminance( P, norm_hair, radians( illum_width ) )
	{
		extern vector L;
		extern color Cl;

		nL = normalize(L);

		T_Dot_nL = T.nL;
		T_Dot_e = T.V;
		Alpha = acos( T_Dot_nL );
		Beta = acos( T_Dot_e );

		Kajiya = T_Dot_nL * T_Dot_e + sin( Alpha ) * sin( Beta );

		/* Calculate diffuse components */
		if ( clump_dark_strength > 0.0 ) {
			clump_darkening = 1 - ( clump_dark_strength *
					abs( clamp( nL.normalize(-1 * clump_vect), -1, 0 )));
		} else {
			clump_darkening = 1.0;
		}

		/* Get light source parameters */
		if ( lightsource("__nonspecular", nonspecular) == 0)
			nonspecular = 0;
		if ( lightsource("__SpecularColor", SpecularColor) == 0)
			SpecularColor = color(1);

		aov_diffuse += clump_darkening * fnc_diffuselgt( Cl, L, norm_hair);

		aov_specular += Cl * (1-nonspecular) * clump_darkening *
						( (spec1 * pow( Kajiya, 1/roughness1)) +
						  (spec2 * pow( Kajiya, 1/roughness2)) )
						* SpecularColor;
	}

	aov_ambient = Ka * ambient() + static_ambient;
	aov_specularcolor = specularcolor;
	aov_diffuse = Kd * aov_diffuse;
	aov_specular = Kspec * v * aov_specular;
	

	darkening = clamp( hair_col_var, 0, 1);
	darkening = (1 - ( smoothstep( var_fade_end, var_fade_start,
					abs( luminance( aov_diffuse ))) * darkening ));

	aov_surfacecolor = mix( rootcolor, tipcolor, v) * darkening;

	C = (aov_surfacecolor * (aov_ambient + aov_diffuse)) +
		(aov_specularcolor * aov_specular);
	
	return clamp( C, color(0), color(1) );
}

////////////////////////////////////////////////////////////////////////////////

#endif
