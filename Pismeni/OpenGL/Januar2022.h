#pragma once
#include "CGLRenderer.h"
#include "CGLTexture.h"

class Januar2022 :
    public CGLRenderer
{
protected:
    CGLTexture m_tex_side;
    CGLTexture m_tex_base;

public:
    Januar2022();
    virtual ~Januar2022();

    virtual void PrepareScene(CDC* pDC);
    virtual void DestroyScene(CDC* pDC);
    virtual void Reshape(CDC* pDC, int w, int h);

    virtual void PrepareTextures();
    virtual void PrepareLighting();

    //
    virtual void DrawScene(CDC* pDC);
    virtual void Draw();

    void DrawPrism(float x, float y, float z, int txId, int txIdBase);
    void DrawRingPart(float r, float dr, float depth, int txId, int txIdBase);
    void SetMaterial(float r, float g, float b);
    void _DrawText(float height, float width, float depth, float weight, float spacing, int txId, int txIdBase);
};

