#include "pch.h"
#include "CGLMaterial.h"

CGLMaterial::CGLMaterial()
	:m_ambient{ 0.2, 0.2, 0.2, 1 },
	m_diffuse{ .8, .8, .8, 1 },
	m_specular{ 0, 0, 0, 1 },
	m_emission{ 0, 0, 0, 1 },
	m_shininess(0)
{

}

CGLMaterial::~CGLMaterial()
{

}

void CGLMaterial::SetAmbient(double R, double G, double B, double A)
{
	m_ambient[0] = R;
	m_ambient[1] = G;
	m_ambient[2] = B;
	m_ambient[3] = A;
}

void CGLMaterial::SetDiffuse(double R, double G, double B, double A)
{
	m_diffuse[0] = R;
	m_diffuse[1] = G;
	m_diffuse[2] = B;
	m_diffuse[3] = A;
}

void CGLMaterial::SetSpecular(double R, double G, double B, double A)
{
	m_specular[0] = R;
	m_specular[1] = G;
	m_specular[2] = B;
	m_specular[3] = A;
}

void CGLMaterial::SetEmission(double R, double G, double B, double A)
{
	m_emission[0] = R;
	m_emission[1] = G;
	m_emission[2] = B;
	m_emission[3] = A;
}

void CGLMaterial::SetShininess(double amount)
{
	m_shininess = amount;
}

void CGLMaterial::SetMaterial(GLenum face)
{
	glMaterialfv(face, GL_AMBIENT, m_ambient);
	glMaterialfv(face, GL_DIFFUSE, m_diffuse);
	glMaterialfv(face, GL_SPECULAR, m_specular);
	glMaterialfv(face, GL_EMISSION, m_emission);
	glMaterialf(face, GL_SHININESS, m_shininess);
}