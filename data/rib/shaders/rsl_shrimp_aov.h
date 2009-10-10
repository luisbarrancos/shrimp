#ifndef SHRIMP_AOV_H
#define SHRIMP_AOV_H 1

#define	DECLARE_AOV_PARAMETERS		\
	aov_surfacecolor,				\
	aov_ambient,					\
	aov_diffuse,					\
	aov_indirectdiffuse,			\
	aov_specular,					\
	aov_specularcolor,				\
	aov_reflection,					\
	aov_refraction,					\
	aov_rimlighting,				\
	aov_scattering,					\
	aov_translucence,				\
	aov_shadows,					\
	aov_occlusion,					\
	aov_caustics,					\
	aov_opacity

#define INIT_AOV_PARAMETERS			\
	aov_surfacecolor	= color(0);	\
	aov_ambient			= color(0);	\
	aov_diffuse			= color(0);	\
	aov_indirectdiffuse	= color(0);	\
	aov_specular		= color(0);	\
	aov_specularcolor	= color(0);	\
	aov_reflection		= color(0);	\
	aov_refraction		= color(0);	\
	aov_rimlighting		= color(0);	\
	aov_scattering		= color(0);	\
	aov_translucence	= color(0);	\
	aov_shadows			= color(0);	\
	aov_occlusion		= 0;		\
	aov_caustics		= color(0);	\
	aov_opacity			= color(0);

#define	DECLARE_AOV_OUTPUT_PARAMETERS			\
	output varying color aov_surfacecolor;		\
	output varying color aov_ambient;			\
	output varying color aov_diffuse;			\
	output varying color aov_indirectdiffuse;	\
	output varying color aov_specular;			\
	output varying color aov_specularcolor;		\
	output varying color aov_reflection;		\
	output varying color aov_refraction;		\
	output varying color aov_rimlighting;		\
	output varying color aov_scattering;		\
	output varying color aov_translucence;		\
	output varying color aov_shadows;			\
	output varying float aov_occlusion;			\
	output varying color aov_caustics;			\
	output varying color aov_opacity;

#define DEFAULT_AOV_OUTPUT_PARAMETERS						\
	output varying color aov_surfacecolor		= color(0);	\
	output varying color aov_ambient			= color(0);	\
	output varying color aov_diffuse			= color(0);	\
	output varying color aov_indirectdiffuse	= color(0);	\
	output varying color aov_specular			= color(0);	\
	output varying color aov_specularcolor		= color(0);	\
	output varying color aov_reflection			= color(0);	\
	output varying color aov_refraction			= color(0);	\
	output varying color aov_rimlighting		= color(0);	\
	output varying color aov_scattering			= color(0);	\
	output varying color aov_translucence		= color(0);	\
	output varying color aov_shadows			= color(0);	\
	output varying float aov_occlusion			= 0;		\
	output varying color aov_caustics			= color(0);	\
	output varying color aov_opacity			= color(0);

#define getshadows(PARAMS) \
	color inshadowcolor = color(0); \
	illuminance(PARAMS) { \
		if (1 == lightsource("__inShadowC", inshadowcolor)) { \
			aov_shadows += (1 - inshadowcolor); } }

////////////////////////////////////////////////////////////////////////////////
#endif /* SHRIMP_AOV_H */

