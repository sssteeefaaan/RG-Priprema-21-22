#pragma once
#include "Figure.h"

class RightTriangle :
    public Figure
{
private:
    PolyPoints inscribedPolygon;
    void SetAttributes(int inscribedPolygonPointNumber);

public:
    RightTriangle(DPOINT rotationPoint, double sideSize, double gridSize, int inscribedPolygonPointNumber, DWORD lineColor, DWORD fillColor, double angleOfRotation, int hatchStyle = -1, POINT mirrorPoint = { 1, 1 });
    RightTriangle(RightTriangle& rt);
    virtual ~RightTriangle();

    virtual PolyPoints GetMyPoints();
    virtual void Draw(CDC* pDC);
};