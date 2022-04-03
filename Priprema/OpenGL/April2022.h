#pragma once
#include "CGLRenderer.h"

class April2022 :
    public CGLRenderer
{
protected:
    int m_n;
public:
    April2022();
    virtual ~April2022();

    UINT PrepareTextures(CString strTex);
    void DrawCone(float h, float r, int nSeg);
    void DrawFigure(double h, int n, int nSeg);
    void DrawScene(CDC* pDC);

    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

