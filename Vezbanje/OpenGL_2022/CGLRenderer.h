#pragma once

#include <gl/GL.h>
#include <gl/GLU.h>
#define M_PI 3.14

class CGLRenderer
{
public:
	CGLRenderer(void);
	virtual ~CGLRenderer(void);

	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	void DrawScene(CDC* pDC);
	void DestroyScene(CDC* pDC);

	void RotateView(double dXY, double dXZ);
	void LookAt(float, float, float);
	void Zoom(bool out);

protected:
	HGLRC m_hrc;
	double viewAngleXY;
	double viewAngleXZ;
	double viewR;
	double viewPosition[3];
	double upVector[3];
	double lookingAt[3];
};

