#include "pch.h"
#include "Maj2021.h"

Maj2021::Maj2021()
	:CGLRenderer()
{
	lookingAt[1] = 0;
	viewAngleXZ =
		viewAngleXY = 50;
	viewR = 10;
	CalculatePosition();
}

Maj2021::~Maj2021()
{

}

void Maj2021::DrawBody(double r, double h1, double h2, int n)
{
	double H = (h1 - h2) / 2,
		L = sqrt(H * H + r * r),
		ny = r / L,
		nr = H / L,
		dAlpha = 2 * M_PI / n,
		s0 = .625,
		t0 = .25,
		dSR = .125,
		dTR = .25,
		dS = .25 / n;

	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3d(0, 1, 0);
		glTexCoord2d(.5 + .5 / 4, .25);
		glVertex3d(0, h1 / 2, 0);
		for (double i = 0; i > -(2 * M_PI + dAlpha); i -= dAlpha)
		{
			double cosi = cos(i), sini = sin(i);

			glNormal3d(nr * cosi, ny, nr * sini);
			glTexCoord2d(s0 + cosi * dSR, t0 + sini * dTR);
			glVertex3d(r * cosi, h2 / 2, r * sini);
		}
	}
	glEnd();

	s0 = .5;
	t0 = 0;
	glBegin(GL_QUAD_STRIP);
	{
		for (double i = 0; i > -(2 * M_PI + dAlpha); i -= dAlpha)
		{
			double cosi = cos(i), sini = sin(i);

			glNormal3d(cosi, 0, sini);

			glTexCoord2d(s0, .5);
			glVertex3d(r * cosi, h2 / 2, r * sini);

			glTexCoord2d(s0, 0);
			glVertex3d(r * cosi, -h2 / 2, r * sini);

			s0 += dS;
		}
	}
	glEnd();

	s0 = .625;
	t0 = .25;
	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3d(0, -1, 0);
		glTexCoord2d(.5 + .5 / 4, .25);
		glVertex3d(0, -h1 / 2, 0);
		for (double i = 0; i < (2 * M_PI + dAlpha); i += dAlpha)
		{
			double cosi = cos(i), sini = sin(i);

			glNormal3d(nr * cosi, -ny, nr * sini);
			glTexCoord2d(s0 + cosi * dSR, t0 + sini * dTR);
			glVertex3d(r * cosi, -h2 / 2, r * sini);
		}
	}
	glEnd();
}

void Maj2021::DrawCompoundBody()
{
	m_altas.Select();
	m_thing.SetMaterial(GL_FRONT);

	DrawBody(1, 2.5, 2.0, 8);

	glDisable(GL_TEXTURE_2D);

	glPushMatrix();
	{
		glRotatef(90, 0, 0, 1);
		DrawBody(.5, 3.5, 3, 8);
		DrawBody(.25, 4.9, 4.8, 8);
	}
	glPopMatrix();

	glEnable(GL_TEXTURE_2D);
}

void Maj2021::DrawWing()
{
	m_altas.Select();
	glPushMatrix();

	glNormal3f(0, 0, 1);

	glTranslatef(0, .75, 0);
	glRotatef(20, -1, 0, 0);

	glBegin(GL_TRIANGLES);
	{
		glTexCoord2d(.5, 1);
		glVertex3f(0, 2, 0);

		glTexCoord2d(0, .5);
		glVertex3f(-4, 0, 0);

		glTexCoord2d(.75, .5);
		glVertex3f(0, 0, 0);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glTexCoord2d(.5, .5);
		glVertex3f(0, 0, 0);

		glTexCoord2d(.75, .5);
		glVertex3f(2, 0, 0);

		glTexCoord2d(.75, 1);
		glVertex3f(2, 2, 0);

		glTexCoord2d(.5, 1);
		glVertex3f(0, 2, 0);
	}
	glEnd();

	glPopMatrix();


	glBegin(GL_QUADS);
	{
		glTexCoord2f(.5, .5);
		glVertex3f(0, .75, 0);

		glTexCoord2f(.5, 0);
		glVertex3f(0, 0, 0);

		glTexCoord2f(.75, 0);
		glVertex3f(2, 0, 0);

		glTexCoord2f(.75, .5);
		glVertex3f(2, .75, 0);
	}
	glEnd();

	glPushMatrix();

	glRotatef(20, 1, 0, 0);
	glBegin(GL_TRIANGLES);
	{
		glTexCoord2d(0, .5);
		glVertex3f(-4, 0, 0);

		glTexCoord2d(.5, 1);
		glVertex3f(0, -2, 0);

		glTexCoord2d(.5, .5);
		glVertex3f(0, 0, 0);
	}
	glEnd();

	glBegin(GL_QUADS);
	{
		glTexCoord2d(.5, .5);
		glVertex3f(0, 0, 0);

		glTexCoord2d(.5, 1);
		glVertex3f(0, -2, 0);

		glTexCoord2d(.75, 1);
		glVertex3f(2, -2, 0);

		glTexCoord2d(.75, .5);
		glVertex3f(2, 0, 0);
	}
	glEnd();

	glPopMatrix();
}

void Maj2021::DrawWings()
{
	glPushMatrix();

	glTranslatef(-1, -.375, 2.5);
	DrawWing();

	glPopMatrix();
	glPushMatrix();

	glRotatef(180, 1, 0, 0);
	glTranslatef(-1, -.375, 2.5);
	DrawWing();

	glPopMatrix();
}

void Maj2021::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	float v[4] = { 0 , 0, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, v);

	gluLookAt(
		viewPosition[0], viewPosition[1], viewPosition[2], 
		lookingAt[0], lookingAt[1], lookingAt[2],
		upVector[0], upVector[1], upVector[2]
	);

	if (showAxes) {
		glDisable(GL_TEXTURE_2D);
		glDisable(GL_LIGHTING);
		DrawAxes();
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_LIGHTING);
	}

	glRotatef(90, 0, 0, 1);
	DrawWings();
	glRotatef(90, 0, 1, 0);
	glRotatef(90, 1, 0, 0);
	DrawCompoundBody();

	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void Maj2021::PrepareTextures()
{
	CGLTexture::PrepareTexturing(true);
	m_altas.Load(L"Texture_Maj_2021.jpg");
}

void Maj2021::PrepareLighting()
{
	float v[4] = { .2, .2, .2, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, v);

	v[0] = v[1] = v[2] = v[3];
	glLightfv(GL_LIGHT0, GL_DIFFUSE, v);
	glLightfv(GL_LIGHT0, GL_SPECULAR, v);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void Maj2021::PrepareMaterials()
{
	m_thing.SetAmbient(.2, .2, .2, 1);
	m_thing.SetDiffuse(.8, .8, .8, 1);
	m_thing.SetSpecular(1, 1, 1, 1);
	m_thing.SetEmission(0, 0, 0, 1);
	m_thing.SetShininess(96);
}