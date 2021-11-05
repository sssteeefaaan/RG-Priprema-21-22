#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

struct DPOINT {
	double x;
	double y;
};

struct PolyDPoints {
	DPOINT* points;
	int n;
};

struct PolyPoints {
	POINT* points;
	int n;
};

class Figure
{
protected:
	PolyPoints myPoints;
	DPOINT rotationPoint;
	double angleOfRotation;
	double sideSize;
	POINT mirrorPoint;
	DWORD lineColor;
	DWORD fillColor;
	int hatchStyle;

protected:
	void SetAttributes(int points, DPOINT rotationPoint, double sideSize, double gridSize, DWORD lineColor, DWORD fillColor, double angleOfRotation, int hatchStyle = -1, POINT mirrorPoint = { 1, 1 });

public:
	Figure(int points, DPOINT rotationPoint, double sideSize, double gridSize, DWORD lineColor, DWORD fillColor, double angleOfRotation, int hatchStyle = -1, POINT mirrorPoint = { 1, 1 });
	Figure(Figure&);
	virtual ~Figure();

	inline DPOINT GetRotationPoint() { return this->rotationPoint; }
	inline double GetAngleOfRotation() { return this->angleOfRotation; }
	inline double GetSideSize() { return this->sideSize; }
	inline POINT GetMirrorPoint() { return this->mirrorPoint; }
	inline DWORD GetLineColor() { return this->lineColor; }
	inline DWORD FillColor() { return this->fillColor; }
	inline int GetHatchStyle() { return this->hatchStyle; }

	virtual PolyPoints GetMyPoints();
	virtual void Draw(CDC* pDC);

	static PolyPoints GetPolyPoints(int n, double cx, double cy, double r, double fi = 0);
	static double GetDistance(POINT a, POINT b);
};

