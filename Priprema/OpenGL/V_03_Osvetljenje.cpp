#include "pch.h"
#include "V_03_Osvetljenje.h"
#include <gl/GLU.h>


V_03_Osvetljenje::V_03_Osvetljenje()
    :CGLRenderer()
{
    lookingAt[1] = 0;
    viewR = 10;
    CalculatePosition();

    m_mat_teapot = new CGLMaterial();
    m_mat_cube = new CGLMaterial();
    m_mat_table = new CGLMaterial();
}

V_03_Osvetljenje::~V_03_Osvetljenje()
{
    if (m_mat_teapot)
    {
        delete(m_mat_teapot);
        m_mat_teapot = nullptr;
    }

    if (m_mat_cube)
    {
        delete(m_mat_cube);
        m_mat_cube = nullptr;
    }

    if (m_mat_table)
    {
        delete(m_mat_table);
        m_mat_table = nullptr;
    }
}

void V_03_Osvetljenje::PrepareScene(CDC* pDC)
{
    wglMakeCurrent(pDC->m_hDC, m_hrc);

    glClearColor(1, 1, 1, 0);
    glEnable(GL_DEPTH_TEST);
    PrepareLighting();
    PrepareMaterials();

    wglMakeCurrent(NULL, NULL);
}

void V_03_Osvetljenje::Draw()
{
    glPushMatrix();

    float temp[4] = { 5, 5, 0, 1 };
    glLightfv(GL_LIGHT1, GL_POSITION, temp);

    temp[0] = temp[1] = -1;
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, temp);

    m_mat_table->SetMaterial(GL_FRONT);
    DrawSide(8, 60);

    glTranslatef(2, .76, 0);
    m_mat_cube->SetMaterial(GL_FRONT);
    DrawCube(1.5, 10);
    
    glTranslatef(-4, .25, 0);
    m_mat_teapot->SetMaterial(GL_FRONT);
    DrawSphere(1);
    DrawTorus(1.5, 1);

    glPopMatrix();
}

void V_03_Osvetljenje::DrawSide(double dSize, int nSteps)
{
    double dStep = dSize / nSteps;

    glNormal3f(0, 1, 0);
    for (double i = -dSize / 2; i < dSize / 2; i += dStep)
    {
        glBegin(GL_QUAD_STRIP);
        for (double j = -dSize / 2; j < (dSize / 2 + dStep); j += dStep)
        {
            glVertex3f(j, 0, i);
            glVertex3f(j, 0, i + dStep);
        }
        glEnd();
    }
}

void V_03_Osvetljenje::DrawCube(double dSize, int nSteps)
{
    double aHalf = dSize / 2;

    glPushMatrix();
    {
        for (int i = 0; i < 4; i++)
        {
            glRotatef(90, 1, 0, 0);
            glPushMatrix();
            {
                glTranslatef(0, aHalf, 0);
                DrawSide(dSize, nSteps);
            }
            glPopMatrix();
        }

        for (int i = -1; i < 2; i+=2)
        {
            glPushMatrix();
            {
                glRotatef(90, 0, 0, i);
                glTranslatef(0, aHalf, 0);
                DrawSide(dSize, nSteps);
            }
            glPopMatrix();
        }
    }
    glPopMatrix();
}

void V_03_Osvetljenje::PrepareLighting()
{
    float temp[4]{ .2, .2 , .2, 1 };
    glLightModelfv(GL_LIGHT_MODEL_AMBIENT, temp);
    glLightfv(GL_LIGHT1, GL_AMBIENT, temp);

    temp[0] = temp[1] = temp[2] = 1;
    glLightfv(GL_LIGHT1, GL_SPECULAR, temp);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, temp);

    glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1);

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 40);
    glLightf(GL_LIGHT1, GL_SPOT_EXPONENT, 7);

    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHTING);
}
    
void V_03_Osvetljenje::PrepareMaterials()
{
    m_mat_teapot->SetDiffuse(1, .7, .2, 1);
    m_mat_teapot->SetSpecular(1, .7, .2, 1);
    m_mat_teapot->SetShininess(64);

    m_mat_cube->SetDiffuse(0, 0, .8, 1);
    m_mat_cube->SetSpecular(0, 0, .8, 1);
    m_mat_cube->SetShininess(86);

    m_mat_table->SetDiffuse(.5, .3, .1, 1);
    m_mat_table->SetSpecular(.5, .3, .1, 1);
    m_mat_table->SetShininess(100);
}
