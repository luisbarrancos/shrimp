/* Utility functions to convert between coordinate systems */

/* Cartesian to polar coordinates */
void
cartesian2polar2d(	float x, y;
					output float rho, theta;
		)
{
	rho = sqrt( x*x + y*y );
	theta = atan( y, x );
}

////////////////////////////////////////////////////////////////////////////////
/* Polar to Cartesian coordinates */
void
polar2cartesian2d(	float rho, theta;
					output float x, y;
		)
{
	float costheta = cos(theta);
	float sintheta = sqrt( max( 0, 1 - costheta*costheta) );
	x = rho * costheta;
	y = rho * sintheta;
}

////////////////////////////////////////////////////////////////////////////////
/* Cylindrical to Cartesian */
/* Normal */
normal
cylindrical2cartesian(	normal in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	float costheta = cos(theta);
	float sintheta = sqrt( max( 0, 1 - costheta*costheta) );
	return normal ( rho * costheta,
					rho * sintheta,
					phi );
}

/* Vector */
vector
cylindrical2cartesian(	vector in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	float costheta = cos(theta);
	float sintheta = sqrt( max( 0, 1 - costheta*costheta) );
	return vector ( rho * costheta,
					rho * sintheta,
					phi );
}

/* Point */
point
cylindrical2cartesian(	point in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	float costheta = cos(theta);
	float sintheta = sqrt( max( 0, 1 - costheta*costheta) );
	return point (	rho * costheta,
					rho * sintheta,
					phi );
}


////////////////////////////////////////////////////////////////////////////////
/* Cartesian to cylindrical */
/* Normal */
normal
cartesian2cylindrical(	normal in;
		)
{
	float x = xcomp( in ), y = ycomp( in ), z = zcomp( in );
	return normal ( sqrt( x*x + y*y ),
					atan( y, x ),
					z );
}

/* Vector */
vector
cartesian2cylindrical(	vector in;
		)
{
	float x = xcomp( in ), y = ycomp( in ), z = zcomp( in );
	return vector ( sqrt( x*x + y*y ),
					atan( y, x ),
					z );
}
/* Point */
point
cartesian2cylindrical(	point in;
		)
{
	float x = xcomp( in ), y = ycomp( in ), z = zcomp( in );
	return point ( sqrt( x*x + y*y ),
					atan( y, x ),
					z );
}

////////////////////////////////////////////////////////////////////////////////
/* Spherical to Cartesian */
/* Normal */
normal
spherical2cartesian(	normal in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	float costheta = cos(theta);
	float sintheta = sqrt( max( 0, 1 - costheta*costheta ) );
	float cosphi = cos(phi);
	float sinphi = sqrt( max( 0, 1 - cosphi*cosphi) );
	return normal(	rho * sinphi * costheta,
					rho * sinphi * sintheta,
					costheta );
}

/* Vector */
vector
spherical2cartesian(	vector in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	float costheta = cos(theta);
	float sintheta = sqrt( max( 0, 1 - costheta*costheta ) );
	float cosphi = cos(phi);
	float sinphi = sqrt( max( 0, 1 - cosphi * cosphi) );
	return vector(	rho * sinphi * costheta,
					rho * sinphi * sintheta,
					costheta );
}

/* Point */
point
spherical2cartesian(	point in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	float costheta = cos(theta);
	float sintheta = sqrt( max( 0, 1 - costheta*costheta ) );
	float cosphi = cos(phi);
	float sinphi = sqrt( max( 0, 1 - cosphi * cosphi) );
	return point(	rho * sinphi * costheta,
					rho * sinphi * sintheta,
					costheta );
}

////////////////////////////////////////////////////////////////////////////////
/* Cartesian to Spherical */
/* Normal */
normal
cartesian2spherical(	normal in;
		)
{
	float x = xcomp( in ), y = ycomp( in ), z = zcomp( in );
	float x2 = x*x, y2 = y*y, z2 = z*z;
	return normal ( sqrt( x2 + y2 + z2 ),
					atan( y, x ),
					atan( sqrt( x2 + y2 ), z ) );

}

/* Vector */
vector
cartesian2spherical(	vector in;
		)
{
	float x = xcomp( in ), y = ycomp( in ), z = zcomp( in );
	float x2 = x*x, y2 = y*y, z2 = z*z;
	return vector ( sqrt( x2 + y2 + z2 ),
					atan( y, x ),
					atan( sqrt( x2 + y2 ), z ) );

}

/* Point */
point
cartesian2spherical(	point in;
		)
{
	float x = xcomp( in ), y = ycomp( in ), z = zcomp( in );
	float x2 = x*x, y2 = y*y, z2 = z*z;
	return point ( sqrt( x2 + y2 + z2 ),
					atan( y, x ),
					atan( sqrt( x2 + y2 ), z ) );

}

////////////////////////////////////////////////////////////////////////////////
/* Spherical to cylindrical conversion */
/* Normal */
normal
spherical2cylindrical(	normal in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	float cosphi = cos(phi);
	float sinphi = sqrt( max( 0, 1 - cosphi*cosphi ) );
	return normal (	rho * sinphi,
					theta,
					rho * cosphi );
}

/* Vector */
vector
spherical2cylindrical(	vector in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	float cosphi = cos(phi);
	float sinphi = sqrt( max( 0, 1 - cosphi*cosphi ) );
	return vector (	rho * sinphi,
					theta,
					rho * cosphi );
}

/* Point */
point
spherical2cylindrical(	point in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	float cosphi = cos(phi);
	float sinphi = sqrt( max( 0, 1 - cosphi*cosphi ) );
	return point (	rho * sinphi,
					theta,
					rho * cosphi );
}

////////////////////////////////////////////////////////////////////////////////
/* Cylindrical to spherical */
/* Normal */
normal
cylindrical2spherical(	normal in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	return normal(	sqrt( rho*rho + phi*phi ),
					theta,
					atan( rho, phi ) );
}

/* Vector */
vector
cylindrical2spherical(	vector in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	return vector(	sqrt( rho*rho + phi*phi ),
					theta,
					atan( rho, phi ) );
}

/* Point */
point
cylindrical2spherical(	point in;
		)
{
	float rho = xcomp( in ), theta = ycomp( in ), phi = zcomp( in );
	return point(	sqrt( rho*rho + phi*phi ),
					theta,
					atan( rho, phi ) );
}

