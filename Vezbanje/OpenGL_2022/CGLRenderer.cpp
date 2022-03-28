#include "pch.h"
#include "CGLRenderer.h"

CGLRenderer::CGLRenderer(void)
{
	m_hrc = NULL;
	this->viewR = 10;

	this->viewAngleXY = 0;
	this->viewAngleXZ = 0;

	this->lookingAt[0] = 0;
	this->lookingAt[1] = 0;
	this->lookingAt[2] = 0;

	this->upVector[0] = 0;
	this->upVector[1] = 1;
	this->upVector[2] = 0;

	this->CalculatePosition();
}

CGLRenderer::~CGLRenderer(void)
{

}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd{};
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);
	if (nPixelFormat == 0) return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);
	if (!bResult) return false;

	m_hrc = wglCreateContext(pDC->m_hDC);
	if (!m_hrc) return false;

	return true;
}

void CGLRenderer::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClearColor(1, 1, 1, 0);

	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(40, (double)w / h, 0, 100);

	glMatrixMode(GL_MODELVIEW);

	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	glClear(GL_COLOR_BUFFER_BIT);// | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(this->viewPosition[0], this->viewPosition[1], this->viewPosition[2],
		this->lookingAt[0], this->lookingAt[1], this->lookingAt[2],
		this->upVector[0], this->upVector[1], this->upVector[2]);

	DrawAxis(10);
	glEnable(GL_CULL_FACE);

	glColor3f(0, 0, 1);
	DrawTorus(5, 4, 16, 16);

	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawAxis(double size)
{
	glLineWidth(2);
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(size, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, size, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, size);
	}
	glEnd();
}
void CGLRenderer::DrawCylinder(double r, double h, int segNoAlpha)
{
	double dAlpha = 2 * 3.14 / segNoAlpha,
		halfH = h / 2.0;

	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3f(0, -1, 0);
		glVertex3f(0, -halfH, 0);
		for (double i = 0; i < 3.14 * 2 + dAlpha; i += dAlpha)
			glVertex3f(r * cos(i), -halfH, r * sin(i));
	}
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3f(0, 1, 0);
		glVertex3f(0, halfH, 0);
		for (double i = 0; i > -3.14 * 2 - dAlpha; i -= dAlpha)
			glVertex3f(r * cos(i), halfH, r * sin(i));
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	{
		for (double i = 0; i > -3.14 * 2 - dAlpha; i -= dAlpha)
		{
			glNormal3f(cos(i), 0, sin(i));
			glVertex3f(r * cos(i), halfH, r * sin(i));
			glVertex3f(r * cos(i), -halfH, r * sin(i));
		}
	}
	glEnd();
}

void CGLRenderer::DrawCylinderX(double r1, double r2, double h, int segNoAlpha)
{
	double b = r1 - r2,
		c = sqrt(h * h + b * b),
		nr = h / c,
		ny = b / c,
		dAlpha = 2 * 3.14 / segNoAlpha,
		halfH = h / 2;

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, -1, 0);
	for (double i = 0; i < 2 * 3.14 + dAlpha; i += dAlpha)
		glVertex3f(r1 * cos(i), -halfH, r1 * sin(i));
	glEnd();

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0, 1, 0);
	for (double i = 0; i > -(2 * 3.14 + dAlpha); i -= dAlpha)
		glVertex3f(r2 * cos(i), halfH, r2 * sin(i));
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (double i = 0; i > -(2 * 3.14 + dAlpha); i -= dAlpha)
	{
		double cos_i = cos(i),
			sin_i = sin(i);

		glNormal3f(nr * cos_i, ny, nr * sin_i);

		glVertex3f(r2 * cos_i, halfH, r2 * sin_i);
		glVertex3f(r1 * cos_i, -halfH, r1 * sin_i);
	}
	glEnd();
}
void CGLRenderer::DrawCone(double r, double h, int segNoAlpha)
{

}
void CGLRenderer::DrawTorus(double r1, double r2, int segNoAlpha, int segNoBeta)
{
	double r = (r1 - r2) / 2,
		mid = r2 + r,
		dAlpha = 2 * 3.14 / segNoAlpha,
		dBeta = 2 * 3.14 / segNoBeta;

	for (double i = 0; i > -(2 * 3.14 + dAlpha); i -= dAlpha)
	{
		double cos_i0 = cos(i),
			sin_i0 = sin(i),
			cos_i1 = cos(i - dAlpha),
			sin_i1 = sin(i - dAlpha);

		glBegin(GL_QUAD_STRIP);
		for (double j = 0; j > -(2 * 3.14 + dBeta); j -= dBeta)
		{
			double cos_j = cos(j),
				sin_j = sin(j);

			glNormal3f(cos_i0 * cos_j, sin_j, sin_i0 * cos_j);
			glVertex3f(cos_i0 * (mid  + r * cos_j), r * sin_j, sin_i0 * (mid + r * cos_j));

			glNormal3f(cos_i1 * cos_j, sin_j, sin_i1 * cos_j);
			glVertex3f(cos_i1 * (mid + r * cos_j), r * sin_j, sin_i1 * (mid + r * cos_j));
		}
		glEnd();
	}
}

void CGLRenderer::DrawSphere(double r, int segNoAlpha, int segNoBeta, double* color1, double* color2)
{
	double dAlpha = 3.14 / segNoAlpha,
		dBeta = 2 * 3.14 / segNoBeta;

	for (double i = 3.14 / 2.0; i > -3.14 / 2.0 -dAlpha; i -= dAlpha)
	{
		double cosA1 = cos(i),
			sinA1 = sin(i),
			cosA2 = cos(i - dAlpha),
			sinA2 = sin(i - dAlpha);

		glBegin(GL_QUAD_STRIP);
		{
			for (double j = 0; j > - 2 * 3.14 - dBeta; j -= dBeta)
			{
				double cosB = cos(j),
					sinB = sin(j);

				glColor3dv(color1);

				glNormal3f(cosA1 * cosB, sinA1, cosA1 * sinB);
				glVertex3f(r * cosA1 * cosB, r * sinA1, r * cosA1 * sinB);

				glColor3dv(color2);

				glNormal3f(cosA2 * cosB, sinA2, cosA2 * sinB);
				glVertex3f(r * cosA2 * cosB, r * sinA2, r * cosA2 * sinB);
			}
		}
		glEnd();
	}
}

void CGLRenderer::DrawCube(double a)
{
	glBegin(GL_QUAD_STRIP);
	{
		// prednja leva
		glColor3f(.5, 0, 0);
		glVertex3f(-a, a, a);

		glColor3f(.5, 0, 0);
		glVertex3f(-a, -a, a);

		// prednja desna - desna leva
		glColor3f(0, .5, 0);
		glVertex3f(a, a, a);

		glColor3f(0, .5, 0);
		glVertex3f(a, -a, a);

		// desna desna - zadnja leva
		glColor3f(0, 0, .5);
		glVertex3f(a, a, -a);

		glColor3f(0, 0, .5);
		glVertex3f(a, -a, -a);

		// zadnja desna
		glColor3f(.5, 0, .5);
		glVertex3f(-a, a, -a);

		glColor3f(.5, 0, .5);
		glVertex3f(-a, -a, -a);
	}
	glEnd();

	glBegin(GL_QUAD_STRIP);
	{
		glColor3f(.5, .5, 0);
		glVertex3f(a, a, a);

		glColor3f(.5, .5, 0);
		glVertex3f(a, a, -a);

		glColor3f(.5, .5, 0);
		glVertex3f(-a, a, a);

		glColor3f(.5, .5, 0);
		glVertex3f(-a, a, -a);

		glColor3f(.5, .5, 0);
		glVertex3f(-a, -a, a);

		glColor3f(.5, .5, 0);
		glVertex3f(-a, -a, -a);

		glColor3f(.5, .5, 0);
		glVertex3f(a, -a, a);

		glColor3f(.5, .5, 0);
		glVertex3f(a, -a, -a);
	}
	glEnd();
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);

	wglMakeCurrent(NULL, NULL);

	if (m_hrc)
	{
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::RotateView(double dXY, double dXZ)
{
	this->viewAngleXY += dXY;
	this->viewAngleXZ += dXZ;
	this->CalculatePosition();
}

void CGLRenderer::LookAt(float x, float y, float z)
{
	this->lookingAt[0] = x,
		this->lookingAt[1] = y,
		this->lookingAt[2] = z;
	this->CalculatePosition();
}

void CGLRenderer::Zoom(bool out)
{
	this->viewR += out ? 2 : -2;
	this->CalculatePosition();
}

void CGLRenderer::CalculatePosition()
{
	double dWXY = this->viewAngleXY * M_PI / 180,
		dWXZ = this->viewAngleXZ * M_PI / 180;

	this->viewPosition[0] = this->viewR * cos(dWXY) * cos(dWXZ);
	this->viewPosition[1] = 0 + this->viewR * sin(dWXY);
	this->viewPosition[2] = this->viewR * cos(dWXY) * sin(dWXZ);

	this->upVector[1] = signbit(cos(dWXY)) ? -1 : 1;
}