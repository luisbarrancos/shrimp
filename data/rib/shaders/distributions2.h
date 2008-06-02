/* Probability distribution functions */

////////////////////////////////////////////////////////////////////////////////
/* Beckmann distribution */
float beckmann(
				float cosalpha, roughness;
		)
{
	float tanalpha_over_m = max( 0.0, sqrt( 1.0 -
				(cosalpha * cosalpha)) / cosalpha ) / roughness;

	float expv = exp( -( tanalpha_over_m * tanalpha_over_m ) );
	return expv / (roughness * roughness * pow( cosalpha, 4) );
}

////////////////////////////////////////////////////////////////////////////////
/* Ward distribution */

float ward(
			float cosalpha, roughness;
		)
{
	float tanalpha = max( 0.0, sqrt( 1.0 - (cosalpha * cosalpha)) / cosalpha );
	float m2 = roughness * roughness;
	
	float out = 1 / (m2 * PI * pow( cosalpha, 3) );
	out *= exp( -( (tanalpha * tanalpha) / m2 ) );
	return out;
}

////////////////////////////////////////////////////////////////////////////////
/* Trowbridge-Reitz distribution */
/* Note: seems this function, like the gaussian distribution, needs an
 * normalization term. How do we get the normalization term? Empirically?
 * To make matters worse, the original paper, by Trowbridge and Reitz,
 * "Average irregularity representations of a roughened surface", is hard
 * to find, to put it mildly. So we'll just set this normalization term to be
 * a constant, until i can find more information on this term. */

float
trowbridge_reitz(
					float cosalpha, roughness;
					)
{
	float NORMALIZATION = PI*2;
	float cosalpha2 = cosalpha * cosalpha;
	float m2 = roughness * roughness;
	float d2 = m2 / (1 + (m2 -1) * cosalpha2);
	return NORMALIZATION * d2 * d2;
}

////////////////////////////////////////////////////////////////////////////////
/* Heidrich-Seidel anisotropic distribution, meant to be coupled with an 
 * isotropic specular term */
float
heidrich_seidel(
					normal Nf;
					vector Vf, Ln;
					vector xdir; // normalized anisotropy direction
					float roughness;
					)
{
	vector dir = normalize( Nf ^ xdir );
	float beta = Ln.dir;
	float theta = Vf.dir;
	float sinbeta = sqrt( max( 0.0, 1.0 - beta * beta) );
	float sintheta = sqrt( max( 0.0, 1.0 - theta * theta) );
	return pow( sinbeta * sintheta - (beta * theta), 1/roughness);
}

////////////////////////////////////////////////////////////////////////////////
/* Geometric attenuation */

/* Torrance-Sparrow */
float
torrance_sparrow(
					float costheta, cosalpha, cospsi, cospsi2;
					)
{	
	float shadowing = (cosalpha * costheta) / cospsi2;
	float masking = (cosalpha * cospsi) / cospsi2;

	return min( 1, 2 * min( shadowing, masking) );
}

////////////////////////////////////////////////////////////////////////////////
/* Smith geometric selfshadowing/masking */
/* Product of 2 attenuation terms, between incident vector and microstructure
 * normal, and viewer and microstructure normal. */

float smith(
				float cospsi, costheta, roughness;
				)
{
	float g1 = cospsi / (roughness + (1 - roughness) * cospsi);
	float g2 = costheta / (roughness + (1 - roughness) * costheta);
	return g1 * g2;
}

////////////////////////////////////////////////////////////////////////////////
/* He-Torrance geometric selfshadowing/masking */
/* (uses glibc erfc for point types, erfcf for float types, via shadeop) */

float he_torrance(
					float costheta, cosalpha, roughness;
					)
{
	float cosalpha2 = cosalpha * cosalpha;
	float costheta2 = costheta * costheta;
	float m2 = roughness * roughness;

	float hnl = cosalpha2 / (2 * m2 * (1 - cosalpha2) );
	float hnv = costheta2 / (2 * m2 * (1 - costheta2) );

	float gnl = sqrt( PI * hnl * (2 - erfc( sqrt( hnl ))));
	float gnv = sqrt( PI * hnv * (2 - erfc( sqrt( hnv ))));

	return (gnl / (gnl +1) ) * (gnv / (gnv + 1) );
}

