#include "pch.h"
#include "Square.h"

Square::Square(DPOINT rotationPoint, double sideSize, double gridSize, DWORD penColor, DWORD backgroundColor, double angleOfRotation, int hatchStyle, POINT mirrorPoint)
	:Figure(4, rotationPoint, sideSize, gridSize, penColor, backgroundColor, angleOfRotation, hatchStyle, mirrorPoint)
{}

Square::Square(Square& s)
	:Figure(4, s.rotationPoint, s.sideSize, 1, s.lineColor, s.fillColor, s.angleOfRotation, s.hatchStyle, s.mirrorPoint)
{}

Square::~Square()
{}