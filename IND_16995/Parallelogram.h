#pragma once
#include "Figure.h"
class Parallelogram :
    public Figure
{
private:
    double height;
    void Parallelogram::SetAttributes(double height);

public:
    Parallelogram(DPOINT rotationPoint, double sideSize, double height, double gridSize, DWORD penColor, DWORD fillColor, double angleOfRotation = 0, int hatchStyle = -1, POINT mirrorPoint = { 1, 1 });
    Parallelogram(Parallelogram& p);
    virtual ~Parallelogram();

    virtual PolyPoints GetMyPoints();
    // virtual void Draw(CDC* pDC);
};

