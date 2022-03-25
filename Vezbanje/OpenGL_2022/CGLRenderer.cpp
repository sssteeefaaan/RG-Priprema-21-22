#include "pch.h"
#include "CGLRenderer.h"

CGLRenderer::CGLRenderer(void)
{
	m_hrc = NULL;
	this->viewR = 20;
	this->viewAngleXY = 45;
	this->viewAngleXZ = 90;

	this->viewPosition[0] = this->viewR * cos(M_PI * viewAngleXY / 180) * cos(M_PI * viewAngleXZ / 180);
	this->viewPosition[1] = this->viewR * sin(M_PI * viewAngleXY / 180);
	this->viewPosition[2] = this->viewR * cos(M_PI * viewAngleXY / 180) * sin(M_PI * viewAngleXZ / 180);
		
	this->upVector[0] = 0;
	this->upVector[1] = 1;
	this->upVector[2] = 0;

	this->lookingAt[0] = 0;
	this->lookingAt[1] = 0;
	this->lookingAt[2] = 0;
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

	double a = 1;
	glEnable(GL_CULL_FACE);
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

	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
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

	double dwXY = M_PI * this->viewAngleXY / 180,
		dwXZ = M_PI * this->viewAngleXZ / 180;

	if (dXY)
		this->upVector[1] = signbit(this->viewR * sin(dwXY) - this->viewPosition[1]) ? (signbit(dXY) ? 1 : -1) : (signbit(dXY) ? -1 : 1);

	this->viewPosition[0] = this->viewR * cos(dwXY) * cos(dwXZ);
	this->viewPosition[1] = this->viewR * sin(dwXY);
	this->viewPosition[2] = this->viewR * cos(dwXY) * sin(dwXZ);
}

void CGLRenderer::LookAt(float x, float y, float z)
{
	this->lookingAt[0] = x,
		this->lookingAt[1] = y,
		this->lookingAt[2] = z;
}

void CGLRenderer::Zoom(bool out)
{
	this->viewR += out ? 1 : -1;

	double dwXY = M_PI * this->viewAngleXY / 180,
		dwXZ = M_PI * this->viewAngleXZ / 180;

	this->viewPosition[0] = this->viewR * cos(dwXY) * cos(dwXZ);
	this->viewPosition[1] = this->viewR * sin(dwXY);
	this->viewPosition[2] = this->viewR * cos(dwXY) * sin(dwXZ);
}