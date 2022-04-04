#include "pch.h"
#include "V_04_Teksture.h"

V_04_Teksture::V_04_Teksture()
	:CGLRenderer()
{
	lookingAt[1] = 0;
	viewR = 30;
	viewAngleXY = 20;
	viewAngleXZ = 45;

	CalculatePosition();
}

V_04_Teksture::~V_04_Teksture()
{
	ReleaseMaterials();
	ReleaseTextures();
}

void V_04_Teksture::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);
	PrepareMaterials();
	PrepareTextures();

	wglMakeCurrent(NULL, NULL);
}

void V_04_Teksture::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	ReleaseMaterials();
	ReleaseTextures();

	wglMakeCurrent(NULL, NULL);
}

void V_04_Teksture::Draw()
{
	glPushMatrix();

	glEnable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glTranslatef(10, 0, 10);
		glRotatef(90, -1, 0, 0);
		
		m_tex_ground.Select();
		DrawSide(20, 10, 5, 5);
	}
	glPopMatrix();

	glTranslatef(2.5, 2.5, 2.5);
	DrawCube(5);

	glTranslatef(7.5, 5, -2.5);
	DrawWall(20, 15, 5, 5);

	glTranslatef(-7.5, 0, 2.5);
	glRotated(-90, 0, 1, 0);

	glTranslatef(7.5, 0, 2.5);
	DrawWall(20, 15, 5, 5);

	glPopMatrix();
}

void V_04_Teksture::DrawSide(double dSize, int nStep, int repX, int repY)
{
	double dStep = dSize / nStep;

	glNormal3f(0, 0, 1);
	for (double i = dSize / 2; i > -dSize / 2; i -= dStep)
	{
		glBegin(GL_QUAD_STRIP);
		for (double j = -dSize / 2; j < dSize / 2 + dStep; j += dStep)
		{
			glTexCoord2d(repX * (dSize / 2 + j) / dSize, repY * (dSize / 2 + i) / dSize);
			glVertex3d(j, i, 0);

			glTexCoord2d(repX * (dSize / 2 + j) / dSize, repY * (dSize / 2 + i - dStep) / dSize);
			glVertex3d(j, i - dStep, 0);
		}
		glEnd();
	}
}

void V_04_Teksture::DrawCube(double dSize, int nStep)
{
	m_tex_cube.Select();

	glPushMatrix();
	{
		for (int i = 0; i < 4; i++)
		{
			glRotatef(90, 0, 1, 0);
			glPushMatrix();
			glTranslatef(0, 0, dSize / 2);
			DrawSide(dSize, nStep);
			glPopMatrix();
		}

		for (int i = -1; i < 2; i += 2)
		{
			glPushMatrix();
			glRotatef(90, i, 0, 0);
			glTranslatef(0, 0, dSize / 2);
			DrawSide(dSize, nStep);
			glPopMatrix();
		}
	}
	glPopMatrix();
}

void V_04_Teksture::DrawWall(double sizeX, double sizeY, int repX, int repY)
{
	m_tex_wall.Select();

	glNormal3f(0, 0, 1);
	glBegin(GL_QUADS);
	{
		glTexCoord2d(0, repY);
		glVertex3d(-sizeX / 2, sizeY / 2, 0);

		glTexCoord2d(0, 0);
		glVertex3d(-sizeX / 2, -sizeY / 2, 0);

		glTexCoord2d(repX, 0);
		glVertex3d(sizeX / 2, -sizeY / 2, 0);

		glTexCoord2d(repX, repY);
		glVertex3d(sizeX / 2, sizeY / 2, 0);
	}
	glEnd();
}

void V_04_Teksture::PrepareMaterials()
{

}

void V_04_Teksture::PrepareTextures()
{
	CGLTexture::PrepareTexturing(false);

	m_tex_cube.Load(L"box.jpg");
	m_tex_wall.Load(L"wall.jpg");
	m_tex_ground.Load(L"ground.jpg");
}

void V_04_Teksture::ReleaseMaterials()
{

}

void V_04_Teksture::ReleaseTextures()
{
	m_tex_cube.Release();
	m_tex_wall.Release();
	m_tex_ground.Release();
}