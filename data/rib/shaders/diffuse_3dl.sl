
surface diffuse_3dl(
    float Kd = 1.0;
    color Cd = color(0.5);
    float roughness = 0.0;
    )
{
    vector In = normalize(I);
    normal Nn = normalize(N);
    normal Nf = faceforward(Nn, In);

    float nondiff = 0.0;
    color C = color(0);

    illuminance("", P, Nf, PI/2,
                "light:__nondiffuse", nondiff)
    {
        if (Cl != 0 && nondiff < 1.0)
        {
            C += (1.0 - nondiff) * PI *
                bsdf(   normalize(L), Nf,
                        "wo", -In, "roughness", roughness,
                        "bsdf", "oren-nayar");
        }
    }

    float lightsamples = 0;
    attribute("user:lightsamples", lightsamples);

    color areaLightC = color(0);
    
    trace(  P, Nf, "wo", -In, "bsdf", "oren-nayar",
            "roughness", roughness, "type", "transmission",
            "hitsides", "reversed", "samplearealights", 1,
            "samples", lightsamples,
            "arealightcontribution", areaLightC);

    C += areaLightC;

    shader gi_light = getshader("gi_light");

    if (gi_light != null)
    {
        color gi = gi_light->computeGI(P, Nf, In, roughness, Cd);
        C += gi;
    }

    Ci = Kd * Cd * C;
}

