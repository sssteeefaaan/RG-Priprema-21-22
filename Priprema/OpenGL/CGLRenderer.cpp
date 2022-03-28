#include "pch.h"
#include "CGLRenderer.h"

CGLRenderer::CGLRenderer()
	:lookingAt{ 0, 16, 0 }, upVector{ 0, 1, 0 }
{
	this->viewR = 100;

	this->viewAngleXY = 20;
	this->viewAngleXZ = 90;

	this->showAxes = true;

	this->CalculatePosition();
}

CGLRenderer::~CGLRenderer()
{

}

bool CGLRenderer::CreateGLContext(CDC* pDC)
{
	PIXELFORMATDESCRIPTOR pfd;
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
	//--------------------------------

	glClearColor(1, 1, 1, 1);
	glEnable(GL_DEPTH_TEST);

	//--------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//--------------------------------

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (double)w / (double)h, 1, 200);

	//--------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//--------------------------------
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	gluLookAt(viewPosition[0], viewPosition[1], viewPosition[2],
		lookingAt[0], lookingAt[1], lookingAt[2],
		upVector[0], upVector[1], upVector[2]);

	if (this->showAxes)
		DrawAxes(50);

	glTranslatef(0, 8, 0);

	glColor4f(1, 1, 0, .75);
	DrawCuboid(32, 16, 32);

	glTranslatef(0, 16, 0);

	glColor4f(1, 0, 0, .75);
	DrawTorus(10, 8);

	glColor4f(0, 0, 1, .75);
	DrawCylinder(16, 16, 0);

	glTranslatef(0, 13, 0);
	
	glColor4f(1, 0, 1, .75);
	DrawSphere(5);

	//--------------------------------
	glFlush();
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRenderer::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, m_hrc);
	//--------------------------------
	// 
	// 
	// 
	//--------------------------------
	wglMakeCurrent(NULL, NULL);

	if (m_hrc) {
		wglDeleteContext(m_hrc);
		m_hrc = NULL;
	}
}

void CGLRenderer::DrawSide(double dx, double dy, int nStep)
{
	double dX = dx / nStep,
		dY = dy / nStep,
		xHalf = dx / 2,
		yHalf = dy / 2;

	glNormal3f(0, 0, 1);
	for (double j = yHalf; j > -yHalf; j -= dY)
	{
		glBegin(GL_QUAD_STRIP);
		for (double i = -xHalf; i < xHalf + dX; i += dX)
		{
			glVertex3f(i, j, 0);
			glVertex3f(i, j - dY, 0);
		}
		glEnd();
	}
}

void CGLRenderer::DrawCuboid(double dx, double dy, double dz, int nStep)
{
	double xHalf = dx / 2,
		yHalf = dy / 2,
		zHalf = dz / 2;

	glPushMatrix();
	{
		glTranslatef(0, 0, zHalf);
		DrawSide(dx, dy, nStep);

		glTranslatef(0, 0, -dz);
		glRotatef(180, 0, 1, 0);
		DrawSide(dx, dy, nStep);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glRotatef(90, 0, 1, 0);
		glTranslatef(0, 0, xHalf);
		DrawSide(dz, dy, nStep);

		glTranslatef(0, 0, -dx);
		glRotatef(180, 0, 1, 0);
		DrawSide(dz, dy, nStep);
	}
	glPopMatrix();

	glPushMatrix();
	{
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 0, yHalf);
		DrawSide(dx, dz, nStep);

		glTranslatef(0, 0, -dy);
		glRotatef(180, 0, 1, 0);
		DrawSide(dx, dz, nStep);
	}
	glPopMatrix();
}
void CGLRenderer::DrawCylinder(double h, double r1, double r2, int nStep)
{
	/*
	____________
				|\
				| \
				|  \
				|bt \
				|    \                   /|
			  h |     \ L              /  |
				|      \		|n|  / al |
				|       \          /      | ny
				|        \       /        |
				|90    al \ 90 / bt    90 |
	____________|__________\ /_ __ __ _ __|
					 r           nr
	*/
	double hHalf = h / 2.0,
		r = r1 - r2,
		L = sqrt(h * h + r * r),
		ny = r / L,
		nr = h / L,
		dAlpha = 2 * M_PI / nStep;

	glNormal3f(0, -1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, -hHalf, 0);
	for (double i = 0; i < (2 * M_PI + dAlpha); i += dAlpha)
		glVertex3f(r1 * cos(i), -hHalf, r1 * sin(i));
	glEnd();

	glBegin(GL_QUAD_STRIP);
	for (double i = 0; i > -(2 * M_PI + dAlpha); i -= dAlpha)
	{
		double cosi = cos(i),
			sini = sin(i);

		glNormal3f(nr * cosi, ny, nr * sini);
		glVertex3f(r2 * cosi, hHalf, r2 * sini);
		glVertex3f(r1 * cosi, -hHalf, r1 * sini);
	}
	glEnd();


	glNormal3f(0, 1, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex3f(0, hHalf, 0);
	for (double i = 0; i > -(2 * M_PI + dAlpha); i -= dAlpha)
		glVertex3f(r2 * cos(i), hHalf, r2 * sin(i));
	glEnd();

}
void CGLRenderer::DrawSphere(double r, int nStep1, int nStep2)
{
	double dAlpha = M_PI / nStep1,
		dBeta = 2 * M_PI / nStep2;

	for (double i = M_PI; i > -M_PI; i -= dAlpha)
	{
		double cos_i0 = cos(i),
			sin_i0 = sin(i),
			cos_i1 = cos(i - dAlpha),
			sin_i1 = sin(i - dAlpha);

		glBegin(GL_QUAD_STRIP);
		for (double j = 0; j > -(2 * M_PI + dBeta); j -= dBeta)
		{
			double cos_j = cos(j),
				sin_j = sin(j);

			glNormal3f(cos_i0 * cos_j, sin_i0, cos_i0 * sin_j);
			glVertex3f(r * cos_i0 * cos_j, r * sin_i0, r * cos_i0 * sin_j);

			glNormal3f(cos_i1 * cos_j, sin_i1, cos_i1 * sin_j);
			glVertex3f(r * cos_i1 * cos_j, r * sin_i1, r * cos_i1 * sin_j);
		}
		glEnd();
	}
}

void CGLRenderer::DrawTorus(double r1, double r2, int segNoAlpha, int segNoBeta)
{
	double r = (r1 - r2) / 2,
		rMid = r2 + 2,
		dAlpha = 2 * M_PI / segNoAlpha,
		dBeta = 2 * M_PI / segNoBeta;

	for (double i = 0; i > -2 * M_PI; i -= dAlpha)
	{
		double cos_i0 = cos(i),
			sin_i0 = sin(i),
			cos_i1 = cos(i - dAlpha),
			sin_i1 = sin(i - dAlpha);

		glBegin(GL_QUAD_STRIP);
		for (double j = 0; j > -(2 * M_PI + dBeta); j -= dBeta)
		{
			double cos_j = cos(j),
				sin_j = sin(j);

			glVertex3f(cos_i0 * (rMid + cos_j * r), r * sin_j, sin_i0 * (rMid + cos_j * r));
			glVertex3f(cos_i1 * (rMid + cos_j * r), r * sin_j, sin_i1 * (rMid + cos_j * r));
		}
		glEnd();
	}
}


void CGLRenderer::DrawAxes(double len)
{
	glLineWidth(2);
	glBegin(GL_LINES);
	{
		glColor3f(1, 0, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(len, 0, 0);

		glColor3f(0, 1, 0);
		glVertex3f(0, 0, 0);
		glVertex3f(0, len, 0);

		glColor3f(0, 0, 1);
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, len);
	}
	glEnd();
}

void CGLRenderer::CalculatePosition()
{
	double dWXY = this->viewAngleXY * M_PI / 180,
		dWXZ = this->viewAngleXZ * M_PI / 180;

	this->viewPosition[0] = this->viewR * cos(dWXY) * cos(dWXZ);
	this->viewPosition[1] = this->viewR * sin(dWXY);
	this->viewPosition[2] = this->viewR * cos(dWXY) * sin(dWXZ);

	this->upVector[1] = signbit(cos(dWXY)) ? -1 : 1;
}

void CGLRenderer::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	this->viewR += zDelta < 0 ? 1 : -1;
	this->CalculatePosition();
}

void CGLRenderer::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	double step = 5;
	switch (nChar)
	{
	case('W'):
		this->viewAngleXY += step;
		this->CalculatePosition();
		break;
	case('S'):
		this->viewAngleXY -= step;
		this->CalculatePosition();
		break;
	case('D'):
		this->viewAngleXZ -= step;
		this->CalculatePosition();
		break;
	case('A'):
		this->viewAngleXZ += step;
		this->CalculatePosition();
		break;
	case('Q'):
		this->viewR -= step;
		this->CalculatePosition();
		break;
	case('E'):
		this->viewR += step;
		this->CalculatePosition();
		break;
	case('C'):
		this->showAxes = !this->showAxes;
		break;
	case('R'):
		this->lookingAt[1] += step;
		this->CalculatePosition();
		break;
	case('T'):
		this->lookingAt[1] -= step;
		break;
	default:
		break;
	}
}