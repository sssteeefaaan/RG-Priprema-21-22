#include "pch.h"
#include "Januar2022.h"

Januar2022::Januar2022()
	:CGLRenderer()
{
	viewR = 50;
	lookingAt[1] = 0;
	CalculatePosition();
}
Januar2022::~Januar2022()
{

}

void Januar2022::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClearColor(0, 0, 0, 1);
	glEnable(GL_DEPTH_TEST);

	PrepareMaterials();
	PrepareLighting();
	PrepareTextures();

	wglMakeCurrent(NULL, NULL);
}

void Januar2022::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	wglMakeCurrent(NULL, NULL);

	m_tex_base.Release();
	m_tex_side.Release();

	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = 0;
	}
}

void Januar2022::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	// Viewport transsformacija
	glViewport(0, 0, w, h);

	// Projection transformacija
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, w / (double)h, 1, 100);

	// Model + Viewer transformacija
	glMatrixMode(GL_MODELVIEW);
	// DrawScene...

	wglMakeCurrent(NULL, NULL);
}

void Januar2022::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Viewer transformacija
	gluLookAt(viewPosition[0], viewPosition[1], viewPosition[2],
		lookingAt[0], lookingAt[1], lookingAt[2],
		upVector[0], upVector[1], upVector[2]);

	float v[4] = { 1, 1, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, v);

	// Model tranformacije
	Draw();

	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void Januar2022::Draw()
{
	glDisable(GL_LIGHTING);
	DrawAxes();
	glEnable(GL_LIGHTING);

	glEnable(GL_TEXTURE_2D);

	_DrawText(8, 8, 2, 1, 1, 0, 0);
	//DrawPrism(10, 30, 20, 0, 0);

	glDisable(GL_TEXTURE_2D);
}

void Januar2022::DrawPrism(float x, float y, float z, int txId, int txIdBase)
{
	double kao_na_slici = 4,
		dY = y / kao_na_slici,
		dT = 1 / kao_na_slici,
		t1 = 1,
		t0 = t1 - dT;

	// glBindTexture(GL_TEXTURE_2D, txId);
	m_tex_side.Select();
	for (double i = y / 2; i > -y / 2; i -= dY)
	{
		glBegin(GL_QUADS);
		{
			// Prednja
			glNormal3f(0, 0, 1);
			glTexCoord2d(0, t1);
			glVertex3d(-x / 2, i, z / 2);
			glTexCoord2d(0, t0);
			glVertex3d(-x / 2, i - dY, z / 2);
			glTexCoord2d(1, t0);
			glVertex3d(x / 2, i - dY, z / 2);
			glTexCoord2d(1, t1);
			glVertex3d(x / 2, i, z / 2);

			// Desna
			glNormal3f(1, 0, 0);
			glTexCoord2d(0, t1);
			glVertex3d(x / 2, i, z / 2);
			glTexCoord2d(0, t0);
			glVertex3d(x / 2, i - dY, z / 2);
			glTexCoord2d(1, t0);
			glVertex3d(x / 2, i - dY, -z / 2);
			glTexCoord2d(1, t1);
			glVertex3d(x / 2, i, -z / 2);

			// Pozadi
			glNormal3f(0, 0, -1);
			glTexCoord2d(0, t1);
			glVertex3d(x / 2, i, -z / 2);
			glTexCoord2d(0, t0);
			glVertex3d(x / 2, i - dY, -z / 2);
			glTexCoord2d(1, t0);
			glVertex3d(-x / 2, i - dY, -z / 2);
			glTexCoord2d(1, t1);
			glVertex3d(-x / 2, i, -z / 2);

			// Leva
			glNormal3f(-1, 0, 0);
			glTexCoord2d(0, t1);
			glVertex3d(-x / 2, i, -z / 2);
			glTexCoord2d(0, t0);
			glVertex3d(-x / 2, i - dY, -z / 2);
			glTexCoord2d(1, t0);
			glVertex3d(-x / 2, i - dY, z / 2);
			glTexCoord2d(1, t1);
			glVertex3d(-x / 2, i, z / 2);
		}
		glEnd();

		t1 = t0;
		t0 -= dT;
	}

	m_tex_base.Select();
	glBegin(GL_QUADS);
	{
		// Gornja
		glNormal3d(0, 1, 0);
		glTexCoord2d(0, 0);
		glVertex3d(-x / 2, y / 2, -z / 2);
		glTexCoord2d(1, 0);
		glVertex3d(-x / 2, y / 2, z / 2);
		glTexCoord2d(1, 1);
		glVertex3d(x / 2, y / 2, z / 2);
		glTexCoord2d(0, 1);
		glVertex3d(x / 2, y / 2, -z / 2);

		// Donja
		glNormal3d(0, -1, 0);
		glTexCoord2d(0, 1);
		glVertex3d(-x / 2, -y / 2, -z / 2);
		glTexCoord2d(0, 0);
		glVertex3d(x / 2, -y / 2, -z / 2);
		glTexCoord2d(1, 0);
		glVertex3d(x / 2, -y / 2, z / 2);
		glTexCoord2d(1, 1);
		glVertex3d(-x / 2, -y / 2, z / 2);
	}
	glEnd();
}
void Januar2022::DrawRingPart(float r, float dr, float depth, int txId, int txIdBase)
{
	double kao_na_slici = 18,
		dAlpha = M_PI / kao_na_slici,
		dS = (double)1 / kao_na_slici,
		s = 0;

	m_tex_side.Select();
	glNormal3f(0, 0, 1);
	glBegin(GL_QUAD_STRIP);
	{
		for (double i = M_PI; i > 0; i -= dAlpha)
		{
			double cosi = cos(i),
				sini = sin(i);

			glTexCoord2d(s, 1);
			glVertex3d((r + dr) * cosi, (r + dr) * sini, depth / 2);
			glTexCoord2d(s, 0);
			glVertex3d(r * cosi, r * sini, depth / 2);
			s += dS;
		}
	}
	glEnd();

	s = 0;
	glNormal3f(0, 0, -1);
	glBegin(GL_QUAD_STRIP);
	{
		for (double i = 0; i < M_PI; i += dAlpha)
		{
			double cosi = cos(i),
				sini = sin(i);

			glTexCoord2d(s, 1);
			glVertex3d((r + dr) * cosi, (r + dr) * sini, -depth / 2);
			glTexCoord2d(s, 0);
			glVertex3d(r * cosi, r * sini, -depth / 2);
			s += dS;
		}
	}
	glEnd();

	m_tex_base.Select();

	s = 0;
	glBegin(GL_QUAD_STRIP);
	{
		for (double i = M_PI; i > 0; i -= dAlpha)
		{
			double cosi = cos(i),
				sini = sin(i);

			glNormal3d(cosi, sini, 0);
			glTexCoord2d(s, 1);
			glVertex3d((r + dr) * cosi, (r + dr) * sini, -depth / 2);
			glTexCoord2d(s, 0);
			glVertex3d((r + dr) * cosi, (r + dr) * sini, depth / 2);
			s += dS;
		}
	}
	glEnd();

	s = 0;
	glBegin(GL_QUAD_STRIP);
	{
		for (double i = M_PI; i > 0; i -= dAlpha)
		{
			double cosi = cos(i),
				sini = sin(i);

			glNormal3d(cosi, -sini, 0);
			glTexCoord2d(s, 1);
			glVertex3d(r * cosi, r * sini, depth / 2);
			glTexCoord2d(s, 0);
			glVertex3d(r * cosi, r * sini,  -depth / 2);
			s += dS;
		}
	}
	glEnd();

	glNormal3f(0, -1, 0);
	glBegin(GL_QUADS);
	{
		for (int i = -1; i < 2; i += 2)
		{
			glTexCoord2d(0, 1);
			glVertex3d(i * (r + dr), 0, depth / 2);
			glTexCoord2d(0, 0);
			glVertex3d(i * (r + dr), 0, -depth / 2);
			glTexCoord2d(-i, 0);
			glVertex3d(i * r, 0, -depth / 2);
			glTexCoord2d(-i, 1);
			glVertex3d(i * r, 0, depth / 2);
		}
	}
	glEnd();
}
void Januar2022::SetMaterial(float r, float g, float b)
{
	float v[3] = { r, g, b };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, v);

	v[0] /= 2; v[1] /= 2; v[2] /= 2;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, v);

	v[0] = v[1] = v[2] = 1;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, v);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15);

	v[0] = v[1] = v[2] = 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, v);
}
void Januar2022::_DrawText(float height, float width, float depth, float weight, float spacing, int txId, int txIdBase)
{
	double size = min(width, height / 3);

	glPushMatrix();

	glRotatef(-90, 1, 0, 0);

	//C
	{
		glPushMatrix();
		{
			glTranslatef(0, size / 2, 0);
			DrawRingPart(size - weight / 2, weight, depth, txId, txIdBase);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-size, 0, 0);
			DrawPrism(weight, size, depth, txId, txIdBase);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(180, 1, 0, 0);
			glTranslatef(0, size / 2, 0);
			DrawRingPart(size - weight / 2, weight, depth, txId, txIdBase);
		}
		glPopMatrix();
	}

	glTranslatef(size + spacing + size / 2, 0, 0);

	{
		// B
		glTranslatef(weight / 2, 0, 0);
		DrawPrism(weight, size * 3, depth, txId, txIdBase);

		glPushMatrix();
		{
			glTranslatef(weight / 2, size - weight/2, 0);
			glRotatef(-90, 0, 0, 1);
			glScalef(1, 1.5, 1);
			DrawRingPart(3 * size / 4 - weight, weight, depth, txId, txIdBase);
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(weight / 2, -size + weight/2, 0);
			glRotatef(-90, 0, 0, 1);
			glScalef(1, 1.5, 1);
			DrawRingPart(3 * size / 4 - weight, weight, depth, txId, txIdBase);
		}
		glPopMatrix();
	}

	glPopMatrix();
}

void Januar2022::PrepareTextures()
{
	CGLTexture::PrepareTexturing(true);
	m_tex_base.Load(L"nzm.jpg");
	m_tex_side.Load(L"nzm.jpg");
}

void Januar2022::PrepareLighting()
{
	float v[4] = { 0.2, 0.2, 0.2, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, v);
	v[0] = v[1] = v[2] = 1;
	glLightfv(GL_LIGHT0, GL_AMBIENT, v);
	glLightfv(GL_LIGHT0, GL_SPECULAR, v);

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
}
