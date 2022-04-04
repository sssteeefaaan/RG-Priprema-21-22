#pragma once
#include "CGLRenderer.h"

class Januar2021 :
    public CGLRenderer
{
protected:
    float alpha;
    float angleVer;
    float angleHor;
    float dHidden;
    float dHolder;
    float dVizor;
    UINT m_metal_tex_ID;

public:
    Januar2021();
    ~Januar2021();

    void DrawCylinder(float r, float h, float nr, float nh);
    void SetMaterial(float r, float g, float b);
    void DrawTelescope(float r, float h, float nr, float nh, float alpha, float dHolder, float angleHor, float angleVer, float dHidden, float dVizor);

    void PrepareLighting();
    void PrepareTextures();
    void Draw();
    void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

