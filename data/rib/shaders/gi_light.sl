

class gi_light(
    float samples = 16;
    float maxdist = 1.0e+19;
    string envmap = "";
    string envspace = "world";
    color env_intensity = 1.0;
    )
{
    varying float cached = 0;
    public varying color giColor = color(0);
        
    void cacheGI(
        varying point Pp;
        varying normal Nn;
        varying vector In;
        varying float roughness;
        varying color weight;)
    {
        if (weight != 0)
        {
            color gi = trace(
                Pp, Nn, "samples", samples, "bsdf", "oren-nayar",
                "wo", -In, "roughness", roughness,
                "raytype", "diffuse", "maxdist", maxdist,
                "weight", weight,
                "environment:tint", env_intensity,
                "environment:space", envspace,
                "environment:map", envmap);
        }
    }

    public color computeGI(
        varying point Pp;
        varying normal Nn;
        varying vector In;
        varying float roughness;
        varying color weight;)
    {
        if (cached == 0)
        {
            cacheGI(Pp, Nn, In, roughness, weight);
            cached = 1;
        }
        return giColor;
    }
}

/*

light gi_light(
    float samples = 16;
    float maxdist = 1.0e+19;
    string envmap = "";
    string envspace = "";
    color env_intensity = 1.0;)
{
    point Pp;
    normal Nn;
    vector In;
    float roughness;
    color weight;

    surface("Pp", Pp);
    surface("Nn", Nn);
    surface("In", In);
    surface("roughness", roughness);
    surface("weight", weight);
}

*/

