#ifndef SHRIMP_LAYERING_H
#define SHRIMP_LAYERING_H 1

/* Utility functions to blend between layers */
////////////////////////////////////////////////////////////////////////////////
//Base on multiple reference
//http://www.pegtop.net/delphi/articles/blendmodes/index.htm
//http://dunnbypaul.net/blends/
////////////////////////////////////////////////////////////////////////////////

#include "rsl_shrimp_helpers.h"

//Clamp Color Function
color clampcolors(color inputColor; float minRValue; float minGValue; float minBValue; float maxRValue; float maxGValue; float maxBValue){
	color outColor;
	outColor = inputColor;
	if(comp(inputColor,0) < minRValue)
		setcomp(outColor,0,minRValue);
	if(comp(inputColor,1) < minGValue)
		setcomp(outColor,1,minGValue);
	if(comp(inputColor,2) < minBValue)
		setcomp(outColor,1,minBValue);
	if(comp(inputColor,0) > maxRValue)
		setcomp(outColor,0,maxRValue);
	if(comp(inputColor,1) > maxGValue)
		setcomp(outColor,1,maxGValue);
	if(comp(inputColor,2) > maxBValue)
		setcomp(outColor,2,maxBValue);
	return outColor;
}

//Blending Mode Functions

//over
color over(color C1; color C2; float pct){
	color outColor;
	outColor = C1*(1-pct)+C2*pct;
	return outColor;
}

//average
color average(color C1; color C2; float pct){
	color outColor;
	//outColor = mix(C1,(C1*pct)/2,pct);
	outColor = (C1*(C2*pct+(1-pct)))/(2*(0.5+(0.5*pct)));
	return outColor;
}

//add
color add(color C1; color C2; float pct){
	color outColor;
	outColor = C1+(C2*pct);
	return outColor;
}

//substract
color substract(color C1; color C2; float pct){
	color outColor;
	outColor = C1-(C2*pct);
	return outColor;
}

//screen
color screen(color C1; color C2; float pct){
	color outColor;
	outColor = 1-((1-C2*pct)*(1-C1));
	return outColor;
}

//multiply
color multiply(color C1; color C2; float pct){
	color outColor;
	outColor = C1*(C2*pct+(1-pct));
	return outColor;
}

//lighten
color lighten(color C1; color C2; float pct){
	color outColor;
	outColor = max(C2*pct,C1)*pct+C1*(1-pct);
	return outColor;
}

//darken
color darken(color C1; color C2; float pct){
	color outColor;
	outColor = min(C2*pct,C1)*pct+C1*(1-pct);
	return outColor;
}

//overlay
color overlay(color C1; color C2; float pct; ){
	float compareColor;
	color outColor;
	compareColor = luminance(pct);
	if(compareColor > 0.5){
		outColor = (2*(0.5+(0.5*pct)))*((C1+(C2*pct))-(C1*(C2*pct)))-(1*pct);
	}
	else{
	outColor = (2*(0.5+(0.5*pct)))*C1*(C2*pct+(1-pct));
	}
	return outColor;
}

//hardlight
color hardlight(color C1; color C2; float pct){
	float compareColor;
	color outColor;
	compareColor = luminance(C1);
	if(compareColor > 0.5){
		outColor = (2*(0.5+(0.5*pct)))*((C1+(C2*pct))-(C1*(C2*pct)))-(1*pct);
	}
	else{
	outColor = (2*(0.5+(0.5*pct)))*C1*(C2*pct+(1-pct));
	}
	return outColor;
}

//Color Dodge
color colordodge(color C1; color C2; float pct){
	color outColor;
	outColor = C1/(1-C2*pct);
	return outColor;
}

//Color Burn
color colorburn(color C1; color C2; float pct){
	color outColor;
	outColor = 1-(1-C1)/(C2*pct+(1-pct));
	return outColor;
}

//reflect
color reflect(color C1; color C2; float pct){
	color outColor;
	outColor = (C1*(C1*pct+1-pct))/(1-(C2*pct));
	return outColor;
}

//difference
color colordifference(color C1; color C2; float pct){
	color outColor;
	outColor = (C2*pct-C1)*pct+C1*(1-pct);
	return outColor;
}

//exclusion
color exclusion(color C1; color C2; float pct){
	color outColor;
	outColor = C1+C2*pct-2*(C1*C2*pct);
	return outColor;
}

//saturate
color saturate(color C1; color C2; float pct){
	color outColor;
	outColor = C1*(1+C2*pct);
	return outColor;
}

//desaturate
color desaturate(color C1; color C2; float pct){
	color outColor;
	outColor = C1*(1-C2*pct);
	return outColor;
}

//illuminate
color colorilluminate(color C1; color C2; float pct){
	color outColor;
	outColor = C1*(2*C2*pct+1-pct);
	return outColor;
}

color blendcolor (color C1;color C2;float bld; float pct;float msk;float imask){
	float mask;
	color value;

	if(imask==1){
					mask=msk;
				}
				else{
					mask=1-msk;
				}
	if (bld == 1){ //over
		value = mix( over(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 2){ //average
		value = mix(average(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 3){ //add
		value = mix(add(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 4){	//substract
		value = mix(substract(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 5){	//screen
		value = mix(screen(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 6){	//multiply
		value = mix(multiply(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 7){	//lighten
		value = mix(lighten(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 8){	//darken
		value = mix(darken(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 9){	//overlay
		value = mix(overlay(C1,C2,pct),C1,mask);
	}
	if (bld == 10){ //pegtop soft light
		value = mix(((1-C1) * multiply(C1,C2,pct) + C1*screen(C1,C2,pct)),C1,mask);
	}
	if (bld == 11){ //hard light
		value = mix(hardlight(C1,C2,pct),C1,mask);
	}
	if (bld == 12){ //Color Dodge
		value = mix(colordodge(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 13){ //Color Burn
		value = mix(colorburn(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 14){ //reflect
		value = mix(reflect(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 15){ //difference
		value = mix(colordifference(C1,C2,pct),C1,mask);
	}
	if (bld == 16){ //exclusion
		value = mix(exclusion(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 17){ //saturate
		value = mix(saturate(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 18){ //desaturate
		value = mix(desaturate(C1,C2,pct),C1,mask);
	}
	else
	if (bld == 19){ //illuminate
		value = mix(colorilluminate(C1,C2,pct),C1,mask);
	}
}
////////////////////////////////////////////////////////////////////////////////
#endif /* SHRIMP_LAYERING_H */
