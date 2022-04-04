#pragma once
#include "CGLRenderer.h"
#include "CGLMaterial.h"
#include "CGLTexture.h"

class V_04_Teksture :
    public CGLRenderer
{
protected:
    CGLMaterial m_mat_cube;
    CGLMaterial m_mat_wall;
    CGLMaterial m_mat_ground;
    CGLTexture m_tex_cube;
    CGLTexture m_tex_wall;
    CGLTexture m_tex_ground;

public:
    V_04_Teksture();
    virtual ~V_04_Teksture();

    virtual void PrepareScene(CDC* pDC);
    virtual void DestroyScene(CDC* pDC);
    virtual void Draw();
    
    virtual void DrawSide(double dSize = 1, int nStep = 10, int repX = 1, int repY = 1);
    virtual void DrawCube(double dSize, int nStep = 10);
    virtual void DrawWall(double sizeX, double sizeY, int rep, int repY);

    virtual void PrepareTextures();
    virtual void PrepareMaterials();

    virtual void ReleaseMaterials();
    virtual void ReleaseTextures();
};

