#pragma once

#pragma comment(lib, "OpenGL32.lib")
#pragma comment(lib, "glu32.lib")

#include <GL\gl.h>
#include <GL\glu.h>

#define _USE_MATH_DEFINES
#include <math.h>

struct COLOR4F {
	float R;
	float G;
	float B;
	float A;
};

class CGLRender
{
private:
	HGLRC m_hrc;

	GLdouble *lookingAt;
	GLdouble *viewPosition;
	GLdouble *upVector;

	double viewR;
	double viewAngleXY;
	double viewAngleXZ;

	bool showGrid;
	bool showAxes;

public:
	CGLRender();
	~CGLRender();

	bool CreateGLContext(CDC* pDC);
	void PrepareScene(CDC* pDC);
	void DestroyScene(CDC* pDC);
	void Reshape(CDC* pDC, int w, int h);
	void DrawScene(CDC* pDC);

	void DrawCube(double dSize = 1, COLOR4F figureColor = { 1, 1, 1, 0 }, COLOR4F outlineColor = { 0, 0, 0, 0 }, double outlineWidth = 2);
	void DrawRobot(double bodyRot = 0, double headRot = 0, double leftArmRot = 0, double rightArmRot = 0, double leftElbowRot = 0, double rightElbowRot = 0);

	void DrawAxes(double lenght = 10, double lineWidth = 2, COLOR4F xColor = { 1, 0, 0, 0 }, COLOR4F yColor = { 0, 1, 0, 0 }, COLOR4F zColor = { 0, 0, 1, 0 });
	void DrawGrid(double dSize, int nSteps, COLOR4F color = { 1, 1, 1, 0 }, double lineWidth = 2);

	void RotateView(double dXY, double dXZ);
	void Zoom(bool out);
	void LookAt(float x, float y, float z);

	inline void ToggleGrid() { this->showGrid = !this->showGrid; }
	inline void ToggleAxes() { this->showAxes = !this->showAxes; }
};

