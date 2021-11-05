#include "pch.h"
#include "Parallelogram.h"

Parallelogram::Parallelogram(DPOINT rotationPoint, double sideSize, double height, double gridSize, DWORD lineColor, DWORD fillColor, double angleOfRotation, int hatchStyle, POINT mirrorPoint)
	:Figure(4, rotationPoint, sideSize, gridSize, lineColor, fillColor, angleOfRotation, hatchStyle, mirrorPoint)
{
	this->SetAttributes(height * gridSize);
}

Parallelogram::Parallelogram(Parallelogram& p)
	:Figure(4, p.rotationPoint, p.sideSize, 1, p.lineColor, p.fillColor, p.angleOfRotation, p.hatchStyle, p.mirrorPoint)
{
	this->SetAttributes(p.height);
}

Parallelogram::~Parallelogram()
{
}

void Parallelogram::SetAttributes(double height)
{
	this->height = height;
}

PolyPoints Parallelogram::GetMyPoints()
{
	if (this->myPoints.points == nullptr)
	{
		this->myPoints = { new POINT[5], 4 };

		double angle1 = this->angleOfRotation * M_PI / 180,
			angle2 = (this->angleOfRotation - 26.6) * M_PI / 180,
			angle3 = (this->angleOfRotation - 45) * M_PI / 180,
			sqrt1 = sqrt(this->height * this->height + 4 * this->sideSize * this->sideSize),
			sqrt2 = sqrt(this->height * this->height + this->sideSize * this->sideSize);

		this->myPoints.points[0].x = this->rotationPoint.x;
		this->myPoints.points[0].y = this->rotationPoint.y;
		this->myPoints.points[1].x = this->rotationPoint.x + this->mirrorPoint.x * this->sideSize * cos(angle1);
		this->myPoints.points[1].y = this->rotationPoint.y - this->mirrorPoint.y * this->sideSize * sin(angle1);
		this->myPoints.points[2].x = this->rotationPoint.x + this->mirrorPoint.x * sqrt1 * cos(angle2);
		this->myPoints.points[2].y = this->rotationPoint.y - this->mirrorPoint.y * sqrt1 * sin(angle2);
		this->myPoints.points[3].x = this->rotationPoint.x + this->mirrorPoint.x * sqrt2 * cos(angle3);
		this->myPoints.points[3].y = this->rotationPoint.y - this->mirrorPoint.y * sqrt2 * sin(angle3);
		this->myPoints.points[4] = this->myPoints.points[0];
	}

	return this->myPoints;
}