#pragma once

#include "CGLRenderer.h"
#include "CGLMaterial.h"

class V_03_Osvetljenje :
    public CGLRenderer
{
protected:
    CGLMaterial* m_mat_teapot,
        * m_mat_cube,
        * m_mat_table;

public:
    V_03_Osvetljenje();
    virtual ~V_03_Osvetljenje();
    virtual void Draw();
    virtual void PrepareScene(CDC* pDC);

    virtual void DrawSide(double dSize, int nSteps);
    virtual void DrawCube(double dSize, int nSteps);
    virtual void PrepareLighting();
    virtual void PrepareMaterials();
};

