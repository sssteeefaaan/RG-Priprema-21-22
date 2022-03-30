#include "pch.h"
#include "V_02_Transformacije.h"

V_02_Transformacije::V_02_Transformacije()
	:V_01_Primitive()
{
	m_body_rot =
		m_head_rot =
		m_left_underarm_rot =
		m_right_underarm_rot = 0;
	m_left_arm_rot = m_right_arm_rot = 180;
	m_step = 5;
}
V_02_Transformacije::~V_02_Transformacije()
{

}

void V_02_Transformacije::Draw()
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	DrawRobot();
}

void V_02_Transformacije::DrawRobot()
{
	glPushMatrix();
	{
		glRotatef(m_body_rot, 0, 1, 0);

		glPushMatrix();
		{
			glScalef(1, 2, .5);
			DrawCube();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0, 1.3, 0);
			glRotatef(m_head_rot, 0, 1, 0);
			glScalef(.6, .6, .6);
			DrawCube();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(-0.65, 1, 0);
			glRotatef(m_left_arm_rot, 1, 0, 0);
			glTranslatef(0, .5, 0);
			glPushMatrix();
			glScalef(.3, 1, .5);
			DrawCube();
			glPopMatrix();

			glTranslatef(0, .5, 0);
			glRotatef(m_left_underarm_rot, 1, 0, 0);
			glTranslatef(0, .5, 0);
			glPushMatrix();
			glScalef(.3, 1, .5);
			DrawCube();
			glPopMatrix();
		}
		glPopMatrix();

		glPushMatrix();
		{
			glTranslatef(0.65, 1, 0);
			glRotatef(m_right_arm_rot, 1, 0, 0);
			glTranslatef(0, .5, 0);
			glPushMatrix();
			glScalef(.3, 1, .5);
			DrawCube();
			glPopMatrix();

			glTranslatef(0, .5, 0);
			glRotatef(m_right_underarm_rot, 1, 0, 0);
			glTranslatef(0, .5, 0);
			glPushMatrix();
			glScalef(.3, 1, .5);
			DrawCube();
			glPopMatrix();
		}
		glPopMatrix();
	}
	glPopMatrix();
}

void V_02_Transformacije::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case('U'):
		m_body_rot -= m_step;
		break;
	case('I'):
		m_body_rot += m_step;
		break;
	case('O'):
		m_head_rot -= m_step;
		break;
	case('P'):
		m_head_rot += m_step;
		break;
	case('H'):
		m_left_arm_rot -= m_step;
		break;
	case('J'):
		m_left_arm_rot += m_step;
		break;
	case('K'):
		m_right_arm_rot -= m_step;
		break;
	case('L'):
		m_right_arm_rot += m_step;
		break;
	case('V'):
		m_left_underarm_rot -= m_step;
		break;
	case('B'):
		m_left_underarm_rot += m_step;
		break;
	case('N'):
		m_right_underarm_rot -= m_step;
		break;
	case('M'):
		m_right_underarm_rot += m_step;
		break;
	default:
		break;
	}

	V_01_Primitive::OnKeyDown(nChar, nRepCnt, nFlags);
}
