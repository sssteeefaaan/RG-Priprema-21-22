#include "pch.h"
#include "Figure.h"

Figure::Figure(int points, DPOINT rotationPoint, double sideSize, double gridSize, DWORD lineColor, DWORD fillColor, double angleOfRotation, int hatchStyle, POINT mirrorPoint)
{
	this->SetAttributes(points, rotationPoint, sideSize, gridSize, lineColor, fillColor, angleOfRotation, hatchStyle, mirrorPoint);
}

Figure::Figure(Figure& f)
{
	this->SetAttributes(f.myPoints.n, f.rotationPoint, f.sideSize, 1, f.lineColor, f.fillColor, f.angleOfRotation, f.hatchStyle, f.mirrorPoint);
	if (this->myPoints.points != nullptr)
		delete[] this->myPoints.points;

	this->myPoints.points = new POINT[f.myPoints.n + 1];

	for (int i = 0; i <= f.myPoints.n; i++)
		this->myPoints.points[i] = f.myPoints.points[i];
}

Figure::~Figure()
{
	if (myPoints.points != nullptr)
	{
		delete[] myPoints.points;
		myPoints.points = nullptr;
	}
}

void Figure::SetAttributes(int points, DPOINT rotationPoint, double sideSize, double gridSize, DWORD lineColor, DWORD fillColor, double angleOfRotation, int hatchStyle, POINT mirrorPoint)
{
	this->myPoints = { nullptr, points };
	this->rotationPoint = { rotationPoint.x * gridSize, rotationPoint.y * gridSize };
	this->sideSize = sideSize * gridSize;
	this->lineColor = lineColor;
	this->fillColor = fillColor;
	this->angleOfRotation = angleOfRotation;
	this->hatchStyle = hatchStyle;
	this->mirrorPoint = mirrorPoint;
}

PolyPoints Figure::GetPolyPoints(int n, double cx, double cy, double r, double fi0)
{
	PolyPoints ret = { new POINT[n + 1], n };
	double dw = 2 * M_PI / n,
		fi = fi0 * M_PI / 180;

	for (int i = 0; i < n; i++)
	{
		ret.points[i].x = cx + r * cos(i * dw + fi);
		ret.points[i].y = cy + r * sin(i * dw + fi);
	}
	ret.points[n] = ret.points[0];

	return ret;
}

PolyPoints Figure::GetMyPoints()
{
	if (this->myPoints.points == nullptr)
		this->myPoints = Figure::GetPolyPoints(this->myPoints.n, this->rotationPoint.x, this->rotationPoint.y, this->sideSize * M_SQRT2 / 2, this->angleOfRotation);

	return this->myPoints;
}

void Figure::Draw(CDC* pDC)
{
	CBrush* oldBrush = nullptr;
	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID | PS_JOIN_ROUND | PS_ENDCAP_ROUND, 3, this->lineColor));

	if(this->hatchStyle != -1)
		oldBrush = pDC->SelectObject(new CBrush(this->hatchStyle, this->fillColor));
	else
		oldBrush = pDC->SelectObject(new CBrush(this->fillColor));

	if (this->myPoints.points == nullptr)
		this->myPoints = this->GetMyPoints();

	pDC->Polygon(myPoints.points, myPoints.n + 1);

	delete pDC->SelectObject(oldPen);
	delete pDC->SelectObject(oldBrush);
}

double Figure::GetDistance(POINT a, POINT b) { return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2)); }