#ifndef IM_VIEW_DEFINITIONS
#define IM_VIEW_DEFINITIONS

#pragma once
#include <gl\gl.h>
#include <gl\glu.h>
#include <gl\glaux.h>

#ifndef	M_PI
#define	M_PI	3.1415926535897932384626433832795
#endif

struct LIGHTSETTING
{
	LIGHTSETTING() :
m_bLightEnabled(0),
m_fLightSpotExponent(0),	
m_fLightSpotCutoff(180.0f),
m_fLightConstantAttenuation(1.0f),
m_fLightLinearAttenuation(0),
m_fLightQuadraticAttenuation(0)
{
	m_f4LightPosition[0] = 0.0f;
	m_f4LightPosition[1] = 0.0f;
	m_f4LightPosition[2] = 1.0f;
	m_f4LightPosition[3] = 0.0f;
	m_f4LightAmbient[0] = 0.4f;
	m_f4LightAmbient[1] = 0.4f;
	m_f4LightAmbient[2] = 0.4f;
	m_f4LightAmbient[3] = 1.0f;
	m_f4LightDiffuse[0] = 1.0f;
	m_f4LightDiffuse[1] = 1.0f;
	m_f4LightDiffuse[2] = 1.0f;
	m_f4LightDiffuse[3] = 1.0f;
	m_f4LightSpecular[0] = 1.0f;
	m_f4LightSpecular[1] = 1.0f;
	m_f4LightSpecular[2] = 1.0f;
	m_f4LightSpecular[3] = 1.0f;
	m_f3LightSpotDirection[0] =  0.0f;
	m_f3LightSpotDirection[1] =  0.0f;
	m_f3LightSpotDirection[2] = -1.0f;
}
bool			m_bLightEnabled;
GLfloat			m_f4LightPosition[4];
GLfloat			m_f4LightAmbient[4];
GLfloat			m_f4LightDiffuse[4];
GLfloat			m_f4LightSpecular[4];
GLfloat			m_f3LightSpotDirection[3];
GLfloat			m_fLightSpotExponent;
GLfloat			m_fLightSpotCutoff;	
GLfloat			m_fLightConstantAttenuation;
GLfloat			m_fLightLinearAttenuation;
GLfloat			m_fLightQuadraticAttenuation;
};

enum ETRACKINGMODE
{
	TM_NONE = 0,
	TM_SPIN,
	TM_PAN,
	TM_ZOOM,

};



#endif