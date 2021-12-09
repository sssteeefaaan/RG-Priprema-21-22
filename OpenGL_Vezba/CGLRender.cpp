#include "pch.h"
#include "CGLRender.h"


CGLRender::CGLRender()
{
	this->m_hrc = NULL;

	this->viewR = 4;
	this->viewAngleXY = 0;
	this->viewAngleXZ = 90;

	this->viewPosition = new GLdouble[3]
	{
		this->viewR * cos(M_PI * viewAngleXY / 180) * cos(M_PI * viewAngleXZ / 180),
		this->viewR * sin(M_PI * viewAngleXY / 180),
		this->viewR * cos(M_PI * viewAngleXY / 180) * sin(M_PI * viewAngleXZ / 180)
	};
	this->upVector = new GLdouble[3]{ 0, 1, 0 };
	this->lookingAt = new GLdouble[3]{ 0, 0, 0 };

	this->showGrid = this->showAxes = true;

	this->robotParams = { 0,0,0,0,0,0 };
}

CGLRender::~CGLRender()
{
	if (this->lookingAt)
	{
		delete[] this->lookingAt;
		this->lookingAt = nullptr;
	}

	if (this->viewPosition)
	{
		delete[] this->viewPosition;
		this->viewPosition = nullptr;
	}

	if (this->upVector)
	{
		delete[] this->upVector;
		this->upVector = nullptr;
	}
}

bool CGLRender::CreateGLContext(CDC* pDC)
{
	// Kreiramo format pixela za kontekst koji kreiramo
	PIXELFORMATDESCRIPTOR pfd;
	memset(&pfd, 0, sizeof(PIXELFORMATDESCRIPTOR));

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;

	// PFD_DOUBLEBUFFER - Koristimo dupli buffer i radimo SwapBuffer() što je brže i od BitBlit(), jer se vrši zamena reference na buffer
	// PFD_SUPPORT_OPENGL - Podrška za OpenGL
	// PFD_DRAW_TO_WINDOW - Crtamo direktno na prozor, jer je mnogo brže
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	// Koristimo RGBA kanale
	pfd.iPixelType = PFD_TYPE_RGBA;
	// Svaki od kanala ima 32/4 = 8 bita, odnosno byte
	pfd.cColorBits = 32;
	// Ovo je nemoguce, ALI ako se ne naglasi, kreira se kontekst sa 16, što je nedovoljno (treba 24)
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int nPixelFormat = ChoosePixelFormat(pDC->m_hDC, &pfd);

	if (nPixelFormat == 0) // Ukoliko je nemoguće pronaći čak ni približni pixel format onom koji smo definisali
		return false;

	BOOL bResult = SetPixelFormat(pDC->m_hDC, nPixelFormat, &pfd);

	if (bResult == FALSE) // Dešava se ukoliko nije moguće postaviti dobijeni pixel format
		return false;

	// Kreiranje OpenGL konteksta
	this->m_hrc = wglCreateContext(pDC->m_hDC);

	if (this->m_hrc == NULL) // Ukoliko je neuspešno kreiran kontekst
		return false;

	return true;
}

void CGLRender::PrepareScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	// -------------------------------------------

	glClearColor(1.0, 1.0, 1.0, 0.0);

	// -------------------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRender::DestroyScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	// -------------------------------------------
	wglMakeCurrent(NULL, NULL);

	if (this->m_hrc != NULL)
	{
		wglDeleteContext(this->m_hrc);
		this->m_hrc = NULL;
	}
}

void CGLRender::Reshape(CDC* pDC, int w, int h)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	// -------------------------------------------

	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (double)w / (double)h, 1, 100);
	glMatrixMode(GL_MODELVIEW);

	// -------------------------------------------
	wglMakeCurrent(NULL, NULL);
}

void CGLRender::DrawScene(CDC* pDC)
{
	wglMakeCurrent(pDC->m_hDC, this->m_hrc);
	// -------------------------------------------
	glClearColor(.75, .75, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	gluLookAt(this->viewPosition[0], this->viewPosition[1], this->viewPosition[2],
		this->lookingAt[0], this->lookingAt[1], this->lookingAt[2],
		this->upVector[0], this->upVector[1], this->upVector[2]);

	if(this->showAxes)
		DrawAxes();

	DrawRobot(this->robotParams.body, this->robotParams.head, this->robotParams.leftArm, this->robotParams.rightArm, this->robotParams.leftElbow, this->robotParams.rightElbow);

	if (this->showGrid)
	{
		glTranslatef(0, -3, 0);
		DrawGrid(5, 20, { 0.5,0,0.2 }, 2);
	}

	glFlush();

	// -------------------------------------------
	SwapBuffers(pDC->m_hDC);
	wglMakeCurrent(NULL, NULL);
}

void CGLRender::DrawCube(double dSize, COLOR4F figureColor, COLOR4F outlineColor, double outlineWidth)
{
	unsigned char indSize = 8,
		lineIndSize= 24,
		vertexSize = 24;

	unsigned char* indices = new unsigned char[lineIndSize];
	float* vertexes = new float[vertexSize];

	double aHalf = dSize / 2;
	// levo-gore-nazad (0)
	vertexes[0] = -aHalf; vertexes[1] = aHalf; vertexes[2] = -aHalf;
	// levo-dole-nazad (1)
	vertexes[3] = -aHalf; vertexes[4] = -aHalf; vertexes[5] = -aHalf;
	// desno-gore-nazad (2)
	vertexes[6] = aHalf; vertexes[7] = aHalf; vertexes[8] = -aHalf;
	// desno-dole-nazad (3)
	vertexes[9] = aHalf; vertexes[10] = -aHalf; vertexes[11] = -aHalf;
	// desno-gore-napred (4)
	vertexes[12] = aHalf; vertexes[13] = aHalf; vertexes[14] = aHalf;
	// desno-dole-napred (5)
	vertexes[15] = aHalf; vertexes[16] = -aHalf; vertexes[17] = aHalf;
	// levo-gore-napred (6)
	vertexes[18] = -aHalf; vertexes[19] = aHalf; vertexes[20] = aHalf;
	// levo-dole-napred (7)
	vertexes[21] = -aHalf; vertexes[22] = -aHalf; vertexes[23] = aHalf;

	// side strip
	for (int i = 0; i < indSize; i++)
		indices[i] = i;
	
	glVertexPointer(3, GL_FLOAT, 0, vertexes);

	glEnableClientState(GL_VERTEX_ARRAY);

	glColor4f(figureColor.R, figureColor.G, figureColor.B, figureColor.A);
	glDrawElements(GL_QUAD_STRIP, indSize, GL_UNSIGNED_BYTE, indices);

	indices[0] = 2;
	indices[1] = 4;
	indices[2] = 0;
	indices[3] = 6;
	indices[4] = 1;
	indices[5] = 7;
	indices[6] = 3;
	indices[7] = 5;
	glDrawElements(GL_QUAD_STRIP, indSize, GL_UNSIGNED_BYTE, indices);

	indices[0] = 0; indices[1] = 1;
	indices[2] = 0; indices[3] = 2;
	indices[4] = 0; indices[5] = 6;
	indices[6] = 3; indices[7] = 1;
	indices[8] = 3; indices[9] = 2;
	indices[10] = 3; indices[11] = 5;
	indices[12] = 4; indices[13] = 2;
	indices[14] = 4; indices[15] = 5;
	indices[16] = 4; indices[17] = 6;
	indices[18] = 7; indices[19] = 1;
	indices[20] = 7; indices[21] = 5;
	indices[22] = 7; indices[23] = 6;
	glColor3f(outlineColor.R, outlineColor.G, outlineColor.B);
	glLineWidth(outlineWidth);
	glDrawElements(GL_LINES, lineIndSize, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);

	if (vertexes)
	{
		delete[] vertexes;
		vertexes = nullptr;
	}

	if (indices)
	{
		delete[] indices;
		indices = nullptr;
	}
}

void CGLRender::DrawRobot(double bodyRot, double headRot, double leftArmRot, double rightArmRot, double leftElbowRot, double rightElbowRot)
{
	glPushMatrix();
	{
		glRotatef(bodyRot, 0, 1, 0);

		// Body
		glPushMatrix();
		{
			glScalef(1, 2, .5);
			DrawCube();
		}
		glPopMatrix();

		// Head
		glPushMatrix();
		{
			glRotatef(headRot, 0, 1, 0);

			glTranslatef(0, 1.3, 0);
			glScalef(.6, .6, .6);
			DrawCube();
		}
		glPopMatrix();

		// Left arm
		glPushMatrix();
		{
			glTranslatef(-.65, 1, 0);
			glRotatef(-leftArmRot, 1, 0, 0);

			glTranslatef(0, -.5, 0);
			glScalef(0.3, 1, 0.5);
			DrawCube();

			glTranslatef(0, -.5, 0);
			glRotatef(-leftElbowRot, 1, 0, 0);

			glTranslatef(0, -.5, 0);
			DrawCube();
		}
		glPopMatrix();

		// Right arm
		glPushMatrix();
		{
			glTranslatef(.65, 1, 0);
			glRotatef(rightArmRot, 1, 0, 0);

			glTranslatef(0, -.5, 0);
			glScalef(0.3, 1, 0.5);
			DrawCube();

			glTranslatef(0, -.5, 0);
			glRotatef(rightElbowRot, 1, 0, 0);

			glTranslatef(0, -.5, 0);
			DrawCube();
		}
		glPopMatrix();

		// Left leg
		glPushMatrix();
		{
			glTranslatef(-.35, -1, 0);
			glRotatef(-leftArmRot, 1, 0, 0);

			glTranslatef(0, -.5, 0);
			glScalef(0.3, 1, 0.5);
			DrawCube();

			glTranslatef(0, -.5, 0);
			glRotatef(-leftElbowRot, 1, 0, 0);

			glTranslatef(0, -.5, 0);
			DrawCube();
		}
		glPopMatrix();

		// Right leg
		glPushMatrix();
		{
			glTranslatef(.35, -1, 0);
			glRotatef(rightArmRot, 1, 0, 0);

			glTranslatef(0, -.5, 0);
			glScalef(0.3, 1, 0.5);
			DrawCube();

			glTranslatef(0, -.5, 0);
			glRotatef(rightElbowRot, 1, 0, 0);

			glTranslatef(0, -.5, 0);
			DrawCube();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void CGLRender::DrawAxes(double lenght, double lineWidth, COLOR4F xColor, COLOR4F yColor, COLOR4F zColor)
{
	int vertexNumb = 12;
	int indicesNumb = 6;

	float* vertexes = new float[vertexNumb];
	float* colors = new float[vertexNumb];
	char* indices = new char[indicesNumb];


	indices[0] = indices[2] = indices[4] = 0;
	indices[1] = 1;
	indices[3] = 2;
	indices[5] = 3;

	for (int i = 0; i < vertexNumb; i++)
		vertexes[i] = 0;
	vertexes[3] = vertexes[7] = vertexes[11] = lenght;

	colors[0] = colors[1] = colors[2] = 1;
	colors[3] = xColor.R; colors[4] = xColor.G; colors[5] = xColor.B;
	colors[6] = yColor.R; colors[7] = yColor.G; colors[8] = yColor.B;
	colors[9] = zColor.R; colors[10] = zColor.G; colors[11] = zColor.B;


	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, vertexes);
	glColorPointer(3, GL_FLOAT, 0, colors);

	glShadeModel(GL_FLAT);
	glLineWidth(lineWidth);
	glDrawElements(GL_LINES, indicesNumb, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
}

void CGLRender::DrawGrid(double dSize, int nSteps, COLOR4F color, double lineWidth)
{
	long base = (nSteps + 1) * 3,
		size = base << 2,
		halfSize = base << 1;
	float* vertexes = new float[size];

	double start = -dSize / 2;
	for (int i = 0; i < halfSize; i +=6)
	{
		vertexes[i + 0] = dSize/2; vertexes[i + 1] = 0;  vertexes[i + 2] = start;
		vertexes[i + 3] = -dSize / 2;  vertexes[i + 4] = 0;  vertexes[i + 5] = start;
		vertexes[i + halfSize + 0] = start; vertexes[i + halfSize + 1] = 0; vertexes[i + halfSize + 2] = dSize / 2;
		vertexes[i + halfSize + 3] = start; vertexes[i + halfSize + 4] = 0; vertexes[i + halfSize + 5] = -dSize / 2;

		start += dSize / nSteps;
	}

	glLineWidth(lineWidth);
	glColor3f(color.R, color.G, color.B);
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vertexes);
	glDrawArrays(GL_LINES, 0, size/3);
	glDisableClientState(GL_VERTEX_ARRAY);

	if (vertexes)
	{
		delete[] vertexes;
		vertexes = nullptr;
	}
}


void CGLRender::RotateView(double dXY, double dXZ)
{
	this->viewAngleXY += dXY;
	this->viewAngleXZ += dXZ;

	double dwXY = M_PI * this->viewAngleXY / 180,
		dwXZ = M_PI * this->viewAngleXZ / 180;

	if(dXY)
		this->upVector[1] = signbit(this->viewR * sin(dwXY) - this->viewPosition[1]) ? (signbit(dXY) ? 1 : -1) : (signbit(dXY) ? -1 : 1);

	this->viewPosition[0] = this->viewR * cos(dwXY) * cos(dwXZ);
	this->viewPosition[1] = this->viewR * sin(dwXY);
	this->viewPosition[2] = this->viewR * cos(dwXY) * sin(dwXZ);
}

void CGLRender::LookAt(float x, float y, float z)
{
	this->lookingAt[0] = x,
		this->lookingAt[1] = y,
		this->lookingAt[2] = z;
}

void CGLRender::Zoom(bool out)
{
	this->viewR += out ? 1 : -1;

	double dwXY = M_PI * this->viewAngleXY / 180,
		dwXZ = M_PI * this->viewAngleXZ / 180;

	this->viewPosition[0] = this->viewR * cos(dwXY) * cos(dwXZ);
	this->viewPosition[1] = this->viewR * sin(dwXY);
	this->viewPosition[2] = this->viewR * cos(dwXY) * sin(dwXZ);
}