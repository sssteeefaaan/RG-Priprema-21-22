#include "pch.h"
#include "RightTriangle.h"

RightTriangle::RightTriangle(DPOINT rotationPoint, double sideSize, double gridSize, int inscribedPolygonPointNumber, DWORD lineColor, DWORD fillColor, double angleOfRotation, int hatchStyle, POINT mirrorPoint)
	:Figure(3, rotationPoint, sideSize, gridSize, lineColor, fillColor, angleOfRotation, hatchStyle, mirrorPoint)
{
	this->SetAttributes(inscribedPolygonPointNumber);
}

RightTriangle::RightTriangle(RightTriangle& rt)
	:Figure(3, rt.rotationPoint, rt.sideSize, 1, rt.lineColor, rt.fillColor, rt.angleOfRotation, rt.hatchStyle, rt.mirrorPoint)
{
	this->SetAttributes(rt.inscribedPolygon.n);
}

RightTriangle::~RightTriangle()
{
	if (this->inscribedPolygon.points != nullptr)
		delete[] this->inscribedPolygon.points;
	this->inscribedPolygon.points = nullptr;
}

void RightTriangle::SetAttributes(int inscribedPolygonPointNumber)
{
	this->inscribedPolygon = { nullptr, inscribedPolygonPointNumber };

	if (this->myPoints.points != nullptr)
		delete[] this->myPoints.points;

	this->myPoints = this->GetMyPoints();

	int a = Figure::GetDistance(this->myPoints.points[0], this->myPoints.points[1]),
		b = Figure::GetDistance(this->myPoints.points[1], this->myPoints.points[2]),
		c = Figure::GetDistance(this->myPoints.points[2], this->myPoints.points[0]),
		sum = a + b + c;

	POINT incenter = 
	{ 
		(a * this->myPoints.points[2].x + b * this->myPoints.points[0].x + c * this->myPoints.points[1].x) / sum,
		(a * this->myPoints.points[2].y + b * this->myPoints.points[0].y + c * this->myPoints.points[1].y) / sum
	};
	double length = max(a, b, c) / 6;

	this->inscribedPolygon = Figure::GetPolyPoints(this->inscribedPolygon.n, incenter.x, incenter.y, length);
}

PolyPoints RightTriangle::GetMyPoints()
{
	if (this->myPoints.points == nullptr)
	{
		myPoints = { new POINT[4], 3 };
		double dw = M_PI_2,
			fi = this->angleOfRotation * M_PI / 180,
			r = this->sideSize * M_SQRT2 / 2;

		for (int i = 0; i < 3; i++)
		{
			myPoints.points[i].x = int(this->rotationPoint.x + r * cos(i * dw + fi) + 0.5);
			myPoints.points[i].y = int(this->rotationPoint.y + r * sin(i * dw + fi) + 0.5);
		}
		myPoints.points[3] = myPoints.points[0];
	}

	return myPoints;
}
void RightTriangle::Draw(CDC* pDC)
{
	Figure::Draw(pDC);

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID | PS_JOIN_ROUND | PS_ENDCAP_ROUND, 3, this->lineColor));

	if (this->inscribedPolygon.points == nullptr)
		this->SetAttributes(this->inscribedPolygon.n);

	pDC->Polyline(this->inscribedPolygon.points, this->inscribedPolygon.n + 1);

	delete pDC->SelectObject(oldPen);
}