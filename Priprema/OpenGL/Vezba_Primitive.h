#pragma once
#include "CGLRenderer.h"
class Vezba_Primitive :
    public CGLRenderer
{
public:
    Vezba_Primitive();
    virtual ~Vezba_Primitive();
    virtual void Draw();

    virtual void DrawCube(double dSize = 1);
    virtual void DrawGrid(double dSize, double nSteps);
    virtual void DrawAxes(double len);

    virtual void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

