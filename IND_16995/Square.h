#pragma once
#include "Figure.h"
class Square :
    public Figure
{
public:
    Square(DPOINT rotationPoint, double sideSize, double gridSize, DWORD penColor, DWORD backgroundColor, double angleOfRotation, int hatchStyle = -1, POINT mirrorPoint = { 1, 1 });
    Square(Square& s);
    virtual ~Square();

    // virtual PolyPoints GetMyPoints();
    // virtual void Draw(CDC* pDC);
};