#include "pch.h"
#include "Januar2021.h"

Januar2021::Januar2021()
	:CGLRenderer()
{
	lookingAt[1] = 20;
	viewR = 80;

	alpha = 15;
	angleVer = 
		angleHor = 60;

	dHidden =
		dVizor =
		dHolder =
		m_metal_tex_ID = 0;
	CalculatePosition();
}

Januar2021::~Januar2021()
{
	if (m_metal_tex_ID)
	{
		glDeleteTextures(1, &m_metal_tex_ID);
		m_metal_tex_ID = 0;
	}
}

void Januar2021::DrawCylinder(float r, float h, float nr, float nh)
{
	double dAlpha = 2 * 3.14 / nr,
		hStep = h / nh,
		dT = 1 / nh,
		dS = 1 / nr,
		s = 0,
		t = 1;

	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3f(0, 1, 0);

		glTexCoord2f(.5, .5);
		glVertex3d(0, h / 2, 0);
		for (double i = 0; i > -(2 * M_PI + dAlpha); i -= dAlpha)
		{
			double cosi = cos(i),
				sini = sin(i);

			glTexCoord2d((1 + cosi) / 2, 1 - (1 + sini) / 2);
			glVertex3d(r * cosi, h / 2, r * sini);
		}
	}
	glEnd();

	for (double j = h / 2; j > -h / 2; j -= hStep)
	{
		glBegin(GL_QUAD_STRIP);
		{
			s = 0;
			for (double i = 0; i > -2 * M_PI; i -= dAlpha)
			{
				double cosi = cos(i),
					sini = sin(i);

				glNormal3d(cosi, 0, sini);

				glTexCoord2d(s, t);
				glVertex3d(r * cosi, j, r * sini);

				glTexCoord2d(s, t - dT);
				glVertex3d(r * cosi, j - hStep, r * sini);

				s += dS;
			}
		}
		glEnd();

		t -= dT;
	}

	glBegin(GL_TRIANGLE_FAN);
	{
		glNormal3f(0, -1, 0);

		glTexCoord2f(.5, .5);
		glVertex3d(0, -h / 2, 0);
		for (double i = 0; i < (2 * M_PI + dAlpha); i += dAlpha)
		{
			double cosi = cos(i),
				sini = sin(i);

			glTexCoord2d((1 + cosi) / 2, (1 + sini) / 2);
			glVertex3d(r * cosi, -h / 2, r * sini);
		}
	}
	glEnd();
}

void Januar2021::SetMaterial(float r, float g, float b)
{
	float v[] = { r, g, b, 1 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, v);

	v[0] /= 2; v[1] /= 2; v[2] /= 2;
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, v);

	v[0] = v[1] = v[2] = 1;
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, v);

	v[0] = v[1] = v[2] = 0;
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, v);

	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 15);
}

void Januar2021::DrawTelescope(float r, float h, float nr, float nh, float alpha, float dHolder, float angleHor, float angleVer, float dHidden, float dVizor)
{
	glPushMatrix();
	{
		glTranslatef(0, 1.2 * h, 0);
		glPushMatrix();
		glTranslatef(0, -.6 * h, 0);
		for (int i = 0; i < 3; i++)
		{
			glRotatef(120, 0, 1, 0);
			glPushMatrix();
			{
				glTranslatef(0, .6 * h, 0);
				glRotatef(alpha, 1, 0, 0);
				glTranslatef(0, -.6 * h, 0);
				DrawCylinder(.1 * r, 1.2 * h, nr, nh);
			}
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glRotatef(angleHor, 0, 1, 0);
			glRotatef(angleVer, 1, 0, 0);
			glTranslatef(0, min(h, dHolder) - h / 2, 0);
			DrawCylinder(r, h, nr, nh);

			glPushMatrix();
			{
				glTranslatef(0, h / 2 + .8 * h / 2 - min(.8 * h, dHidden), 0);
				DrawCylinder(.8 * r, .8 * h, nr, nh);
			}
			glPopMatrix();

			glTranslatef(0, min(h, dVizor) - h / 2, 0);
			glRotatef(90, -1, 0, 0);
			glTranslatef(0, r + .025 * h, 0);
			DrawCylinder(.1 * r, .05 * h, nr, nh);

			glTranslatef(0, 0.025 * h + .1 * r, 0);
			glRotatef(90, 1, 0, 0);
			DrawCylinder(.1 * r, .3 * h, nr, nh);
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void Januar2021::Draw()
{
	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);

	if (showAxes)
		DrawAxes();

	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	float v[] = { 1, 1, 1, 0 };
	glLightfv(GL_LIGHT0, GL_POSITION, v);

	SetMaterial(.4, .2, 1);
	glBindTexture(GL_TEXTURE_2D, m_metal_tex_ID);
	DrawTelescope(5, 20, 10, 10, alpha, dHolder, angleHor, angleVer, dHidden, dVizor);
}

void Januar2021::PrepareLighting()
{
	float v[] = { .2, .2, .2, 1 };
	glLightfv(GL_LIGHT0, GL_AMBIENT, v);

	v[0] = v[1] = v[2] = 1;
	glLightfv(GL_LIGHT0, GL_DIFFUSE, v);
	glLightfv(GL_LIGHT0, GL_SPECULAR, v);

	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
}

void Januar2021::PrepareTextures()
{
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	
	if (m_metal_tex_ID) {
		glDeleteTextures(1, &m_metal_tex_ID);
		m_metal_tex_ID = 0;
	}

	glGenTextures(1, &m_metal_tex_ID);
	glBindTexture(GL_TEXTURE_2D, m_metal_tex_ID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	DImage img;
	img.Load(L"Metal.jpg");
	img.Flip();

	gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, img.Width(), img.Height(), GL_BGRA_EXT, GL_UNSIGNED_BYTE, img.GetDIBBits());
}

void Januar2021::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	float step = ((GetKeyState(VK_SHIFT) & 0x8000) != 0) ? -1 : 1;
	switch (nChar)
	{
	case(VK_UP):
		alpha = min(45, max(15, alpha + step * 5));
		break;
	case(VK_DOWN):
		dVizor = max(0, dVizor - step);
		break;
	case(VK_LEFT):
		dHolder = max(0, dHolder - step);
		break;
	case(VK_RIGHT):
		dHidden = max(0, dHidden - step);
		break;
	case('V'):
		angleVer = min(80, max(15, angleVer + step * 5));
		break;
	case('H'):
		angleHor += step * 5;
		break;
	default:
		break;
	}
	
	CGLRenderer::OnKeyDown(nChar, nRepCnt, nFlags);
}