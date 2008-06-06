////////////////////////////////////////////////////////////////////////////////
// Siggraph 2000 shadow spot light shader, by Tal Lancaster, from //////////////
// The RenderMan Repository, http://www.renderman.org //////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* Slightly tweaked to fit shrimp's structure and needs */

/* Modified shadowspot to better handle attenuation.
 * 
 * bias -- to overide the global shadow bias value.  -1 the light will
 *   use the global shadow bias value.  Otherwise whatever value is here
 *   is what will be used for this lights shadow bias.
 * blur -- amount to soften the shadows edges.
 *
 * 
 * Tal Lancaster  talrmr@SpamSucks_pacbell.net
 * 02/12/00
 * 
 * Modification History
 * 03/25/00  Added comments.
 */

color
sig2kshadowspot(
				 float intensity; color lightcolor;
				 point from, to;
				 uniform float coneangle, conedeltaangle, beamdistribution;
				 uniform string shadowname, shadowfilter;
				 float shadowsamples, shadowblur, shadowbias, atten,
				 shadowwidth;
		)
{
	float attenuation, cosangle;
	vector A = (to - from) / length(to - from);
	uniform float cosoutside = cos( coneangle ),
				  cosinside = cos( coneangle - conedeltaangle );

	color C = color(0);
	illuminate( from, A, coneangle ) {
		extern vector L;
		extern point Ps;

		cosangle = L.A / length( L );
		attenuation = atten * pow( cosangle, beamdistribution) /
									( atten + length(L));
		attenuation *= smoothstep( cosoutside, cosinside, cosangle);
		
		if (shadowname != "") {
			if ( shadowbias != -1) {
				/* Have light override global shadow-bias settings */
				attenuation *= 1 - shadow( shadowname, Ps, "samples",
						shadowsamples, "blur", shadowblur,
						"width", shadowwidth, "filter", shadowfilter,
						"bias", shadowbias );
			} else {
				/* Use global shadow-bias settings */
				attenuation *= 1 - shadow( shadowname, Ps, "samples",
						shadowsamples, "blur", shadowblur,
						"width", shadowwidth, "filter", shadowfilter );
			}
		}
		C = attenuation * lightcolor;
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Slide projector light shader, from The RenderMan Repository /////////////////
// http://www.renderman.org ////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/* slightly tweaked to fit shrimp's structure and needs */

/* Copyrighted Pixar 1989 */
/* From the RenderMan Companion p.373 */
/* Listing.16.28 Slide-projector light shader */

/*
 * slideprojector(): Cast a texture map into a scene as a light source
 */

color
slideprojector(
				uniform float fieldofview;
				point from, to, up;
				uniform string slidename, shadowname, shadowfilter;
				float shadowblur, shadowsamples, shadowwidth, shadowbias;
		)
{
	varying vector reIT, /* normalized direction vector */
				   reIU, /* "vertical" perspective of surface point */
				   reIV; /* "horizontal perspective of surface point */

	uniform float spread = 1 / tan( fieldofview/2); /* spread of "beam" */

	float Pt, /* projection of Ps on reIT (distance of surface point along
				 light direction) */
		  Pu, /* projection of Ps on reIU */
		  Pv; /* projection of Ps on reIV */
	
	float sloc, tloc; /* perspected surface point */

	/* initialize uniform variables for perspective */
	reIT = normalize( to - from );
	reIU = reIT ^ vector( up ) ;
	reIV = normalize( reIT ^ reIU );
	reIU = reIV ^ reIT;

	color C = color(0);
	illuminate( from, vector( reIT), atan( 1.414213562 / spread)) /* sqrt(2) */
	{
		extern vector L;
		extern point Ps;
		L = Ps - from; /* direction of light soruce from surface point */
		Pt = L.reIT;   /* direction of Ps along reIT, reIU, reIV */
		Pu = L.reIU;
		Pv = L.reIV;
		sloc = spread * Pu / Pt; /* perspective divide */
		tloc = spread * Pv / Pt;
		sloc = sloc * .5 + .5; /* correction from [-1,1] to [0,1] */
		tloc = tloc * .5 + .5;
		C = color texture( slidename, sloc, tloc);
		if (shadowname != "") {
			C *= 1 - color shadow( shadowname, Ps, "samples", shadowsamples,
							"blur", shadowblur, "width", shadowwidth,
							"filter", shadowfilter, "bias", shadowbias );
		}
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Distant light shader, with shadows //////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

color
sdistantlight(
				point from, to;
				uniform string shadowname, shadowfilter;
				float shadowsamples, shadowwidth, shadowblur, shadowbias;
				float intensity;
				color lightcolor;
		)
{

	extern point Ps;

	color C = color(0);
	solar( to - from, 0) {
		C = intensity * lightcolor;
		if (shadowname != "") {
			C *= 1 - color shadow( shadowname, Ps, "samples", shadowsamples,
							"blur", shadowblur, "width", shadowwidth,
							"filter", shadowfilter,	"bias", shadowbias );
		}
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////
// Point light shader, with shadows ////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

color
spointlight(
				point from;
				float intensity, decay, blur, width, samples, bias;
				uniform string shadowmap, filter;
				color lightcolor;
		)
{

	color C = color(0);

	illuminate( from ) {
	
		extern vector L;
		extern point Ps;
		
		float l2 = L . L;
		if (decay == 1.0) {
			C = intensity * ( lightcolor / l2 );
		} else {
			C = intensity * ( lightcolor / pow( l2, .5 * decay));
		}

		if (shadowmap != "") {
			C *= 1 - color shadow( shadowmap, Ps, "samples", samples, "blur",
									blur, "width", width, "bias", bias,
									"filter", filter );
		}
	}
	return C;
}

////////////////////////////////////////////////////////////////////////////////


