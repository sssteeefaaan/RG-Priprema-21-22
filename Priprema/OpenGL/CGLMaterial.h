#pragma once
#include <gl/GL.h>
class CGLMaterial
{
protected:
	float m_ambient[4];
	float m_diffuse[4];
	float m_specular[4];
	float m_emission[4];
	float m_shininess;

public:
	CGLMaterial();
	virtual ~CGLMaterial();

	virtual void SetAmbient(double R, double G, double B, double A);
	virtual void SetDiffuse(double R, double G, double B, double A);
	virtual void SetSpecular(double R, double G, double B, double A);
	virtual void SetEmission(double R, double G, double B, double A);
	virtual void SetShininess(double amount);

	virtual void SetMaterial(GLenum face);
};

