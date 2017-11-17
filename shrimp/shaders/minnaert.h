
#define RIPI	3.14159265359f

color cminnaertfun ( point P; float k;
			color cminnaert; normal Nn, Nf)
{
	float ndotl;

	illuminance( P, Nf, RIPI/2)
	{
		ndotl = max(0, (normalize(L)).Nf);
		cminnaert += Cl*pow(ndotl, k);
	}
	vector V = -normalize(I);
	float ndotv = max(0, Nf.V);
	float outfact = pow(ndotv, k-1);
	cminnaert *= outfact;
	return cminnaert;
}


