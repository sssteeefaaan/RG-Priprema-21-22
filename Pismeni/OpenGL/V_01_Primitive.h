#pragma once

#include "CGLRenderer.h"

class V_01_Primitive :
    public CGLRenderer
{
public:
    V_01_Primitive();
    virtual ~V_01_Primitive();
    virtual void Draw();

    virtual void DrawCube(double dSize = 1);
    virtual void DrawGrid(double dSize, double nSteps);
    virtual void DrawAxes(double len);

    virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

