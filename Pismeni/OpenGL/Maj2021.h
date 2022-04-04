#pragma once
#include "CGLRenderer.h"
#include "CGLTexture.h"
#include "CGLMaterial.h"

class Maj2021
	:public CGLRenderer
{
protected:
	CGLTexture m_altas;
	CGLMaterial m_thing;

public:
	Maj2021();
	virtual ~Maj2021();

	virtual void DrawBody(double r, double h1, double h2, int n);
	virtual void DrawCompoundBody();
	virtual void DrawWing();
	virtual void DrawWings();
	virtual void DrawScene(CDC* pDC);

	virtual void PrepareTextures();
	virtual void PrepareLighting();
	virtual void PrepareMaterials();
};

