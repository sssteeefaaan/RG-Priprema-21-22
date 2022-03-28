#include "pch.h"
#include "Vezba_Primitive.h"

Vezba_Primitive::Vezba_Primitive()
	:CGLRenderer()
{
	lookingAt[1] = 0;

	viewR = 5;
	CalculatePosition();
}

Vezba_Primitive::~Vezba_Primitive()
{

}

void Vezba_Primitive::Draw()
{
	if (showAxes)
		DrawAxes(10);
	glColor3f(1, 0, 1);
	DrawGrid(5, 20);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	
	glLineWidth(2);

	glColor3f(0, .75, 1);
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	DrawCube(1);

	glColor3f(1, 1, 0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	DrawCube(1);
}

void Vezba_Primitive::DrawCube(double dSize)
{
	double aHalf = dSize / 2;

	glBegin(GL_QUAD_STRIP);
		//glColor3f(1, 0, 0);
		glVertex3f(-aHalf, aHalf, aHalf);
		glVertex3f(-aHalf, -aHalf, aHalf);

		//glColor3f(1, 1, 0);
		glVertex3f(aHalf, aHalf, aHalf);
		glVertex3f(aHalf, -aHalf, aHalf);

		//glColor3f(1, 0, 1);
		glVertex3f(aHalf, aHalf, -aHalf);
		glVertex3f(aHalf, -aHalf, -aHalf);

		//glColor3f(0, 1, 0);
		glVertex3f(-aHalf, aHalf, -aHalf);
		glVertex3f(-aHalf, -aHalf, -aHalf);
	glEnd();

	glBegin(GL_QUAD_STRIP);
		//glColor3f(0, 0, 1);
		glVertex3f(aHalf, aHalf, aHalf);
		glVertex3f(aHalf, aHalf, -aHalf);

		//glColor3f(0, 1, 1);
		glVertex3f(-aHalf, aHalf, aHalf);
		glVertex3f(-aHalf, aHalf, -aHalf);

		//glColor3f(1, .5, 0);
		glVertex3f(-aHalf, -aHalf, aHalf);
		glVertex3f(-aHalf, -aHalf, -aHalf);

		//glColor3f(1, .5, .4);
		glVertex3f(aHalf, -aHalf, aHalf);
		glVertex3f(aHalf, -aHalf, -aHalf);
	glEnd();
}

void Vezba_Primitive::DrawGrid(double dSize, double nSteps)
{
	double dStep = dSize / nSteps;

	glBegin(GL_LINES);
	for (double i = -dSize / 2; i < (dSize / 2 + dStep); i += dStep)
	{
		glVertex3f(i, 0, -dSize / 2);
		glVertex3f(i, 0, dSize / 2);
		glVertex3f(-dSize / 2, 0, i);
		glVertex3f(dSize / 2, 0, i);
	}
	glEnd();
}

void Vezba_Primitive::DrawAxes(double len)
{
	glLineWidth(3);

	glBegin(GL_LINES);
	glColor3f(1, 0, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(len, 0, 0);

	glColor3f(0, 1, 0);
	glVertex3f(0, 0, 0);
	glVertex3f(0, len, 0);

	glColor3f(0, 0, 1);
	glVertex3f(0, 0, 0);
	glVertex3f(0, 0, len);
	glEnd();
}

void Vezba_Primitive::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CGLRenderer::OnKeyDown(nChar, nRepCnt, nFlags);
}

