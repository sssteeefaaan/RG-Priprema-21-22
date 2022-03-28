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
	void CalculatePosition();

	void DrawCube(double a);
	void DrawSphere(double r, int segNoAlpha, int segNoBeta, double* color1, double* color2);
	void DrawCylinder(double r, double h, int segNoAlpha);
	void DrawCylinderX(double r1, double r2, double h, int segNoAlpha);
	void DrawCone(double r, double h, int segNoAlpha);
	void DrawTorus(double r1, double r2, int segNoAlpha, int segNoBeta);

	void DrawAxis(double size);

protected:
	HGLRC m_hrc;
	double viewAngleXY;
	double viewAngleXZ;
	double viewR;
	double viewPosition[3];
	double upVector[3];
	double lookingAt[3];
};

