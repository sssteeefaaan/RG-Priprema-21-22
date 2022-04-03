#include "pch.h"
#include "April2022.h"

April2022::April2022()
	:CGLRenderer()
{
	viewAngleXY = 0;
	viewAngleXZ = 90;

	viewR = 10;
	lookingAt[1] = 0.5;
	CalculatePosition();

	m_n = 1;
}

April2022::~April2022()
{
}

UINT April2022::PrepareTextures(CString strTex)
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	UINT ret = 0;
	glGenTextures(1, &ret);
	glBindTexture(GL_TEXTURE_2D, ret);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	DImage img;
	img.Load(strTex);
	img.Flip();
	
	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());

	return ret;
}
void April2022::DrawCone(float h, float r, int nSeg)
{
	double L = sqrt(h * h + r * r),
		ny = r / L,
		nr = h / L,
		dAlpha = 2 * 3.14 / nSeg,
		angle = 0;

	glDisable(GL_TEXTURE_2D);
	glBegin(GL_TRIANGLE_FAN);
	{
		glColor3f(.7, .7, .7);
		glNormal3f(0, -1, 0);
		glVertex3f(0, -h / 2, 0);
		for (int i = 0; i <= nSeg; i++)
		{
			glVertex3f(r * cos(angle), -h / 2, r * sin(angle));
			angle += dAlpha;
		}
		glEnd();
	}
	glEnable(GL_TEXTURE_2D);

	angle = 0;
	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3f(0, 1, 0);
		glTexCoord2f(1, 1);
		glVertex3f(0, h / 2, 0);
		for (int i = 0; i <= nSeg; i++)
		{
			double cosi = cos(angle),
				sini = sin(angle);

			glNormal3f(nr * cosi, ny, nr * sini);
			glTexCoord2f(1 + cos(3.14 - angle / 4), 1 + sin(3.14 - angle / 4));
			glVertex3f(r * cosi, -h / 2, r * sini);

			angle -= dAlpha;
		}
	}
	glEnd();
}

void April2022::DrawFigure(double h, int n, int nSeg)
{
	double a = 2 * h * sqrt(3) / 3;
	if (n == 1)
		DrawCone(h, a / 2, nSeg);
	else {
		glTranslated(0, h / 4, 0);
		DrawFigure(h / 2, n - 1, nSeg);
		glTranslated(-a / 4, -h / 2, 0);
		DrawFigure(h / 2, n - 1, nSeg);
		glTranslated(a / 2, 0, 0);
		DrawFigure(h / 2, n - 1, nSeg);
		glTranslated(-a / 4, h / 4, 0);
	}
}

void April2022::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	gluLookAt(viewPosition[0], viewPosition[1], viewPosition[2],
		lookingAt[0], lookingAt[1], lookingAt[2],
		upVector[0], upVector[1], upVector[2]);

	if (showAxes)
		DrawAxes();

	PrepareTextures(L"tex.jpg");
	glEnable(GL_TEXTURE_2D);

	glTranslatef(0, .5, 0);
	DrawFigure(1, m_n, 8);

	glDisable(GL_TEXTURE_2D);

	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void April2022::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar) {
	case('P'):
		m_n++;
		break;
	case('M'):
		m_n = max(1, m_n - 1);
		break;
	default:
		break;
	}

	CGLRenderer::OnKeyDown(nChar, nRepCnt, nFlags);
}