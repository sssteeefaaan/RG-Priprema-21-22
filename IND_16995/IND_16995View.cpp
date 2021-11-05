
// IND_16995View.cpp : implementation of the CIND16995View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IND_16995.h"
#endif

#include "IND_16995Doc.h"
#include "IND_16995View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIND16995View

IMPLEMENT_DYNCREATE(CIND16995View, CView)

BEGIN_MESSAGE_MAP(CIND16995View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CIND16995View construction/destruction

CIND16995View::CIND16995View() noexcept
{
	this->grid = false;
	this->windowSize.SetRect({ 0,0 }, { 500, 500 });
	this->gridCount = 20;
	this->gridSize = 500 / 20;
	this->backgroundColor = RGB(200, 200, 200);
	this->penColor = RGB(0, 0, 255);
}

CIND16995View::~CIND16995View()
{
}

BOOL CIND16995View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIND16995View drawing

POINT* CIND16995View::GetRegularPoligonPoints(int cx, int cy, int r, int n = -1, int rot = 0)
{
	POINT* polygon = nullptr;
	double angle, fi;

	// Ukoliko je rec o pravouglom trouglu, to se svodi na kvadrat bez x = cx + 0, y = cy - r komponente
	// To ce biti default figura ukoliko se prosledi n < 3
	if (n > 2)
		angle = 2 * M_PI / n;
	else
	{
		angle = M_PI_2;
		n = 3;
	}

	fi = rot * M_PI / 180;

	polygon = new POINT[n + 1];

	for (int i = 0; i < n; i++)
	{
		polygon[i].x = cx + (double)r * cos(i * angle + fi);
		polygon[i].y = cy + (double)r * sin(i * angle + fi);
	}
	polygon[n] = polygon[0];

	return polygon;
}

POINT* CIND16995View::GetParalelogramPoints(DPOINT v, int a, int h, int rot = 0, bool mirrorX = false)
{
	POINT* points = new POINT[5];

	double angle1 = rot * M_PI / 180,
		angle2 = (rot - 26.5) * M_PI / 180,
		angle3 = (rot - 45) * M_PI / 180,
		sqrt1 = sqrt(h * h + 4 * a * a),
		sqrt2 = sqrt(h * h + a * a);

	int mirror = mirrorX ? -1 : 1;

	points[0].x = points[4].x = v.x;
	points[0].y = points[4].y = v.y;
	points[1].x = v.x + mirror * a * cos(angle1);
	points[1].y = v.y - a * sin(angle1);
	points[2].x = v.x + mirror * sqrt1 * cos(angle2);
	points[2].y = v.y - sqrt1 * sin(angle2);
	points[3].x = v.x + mirror * sqrt2 * cos(angle3);
	points[3].y = v.y - sqrt2 * sin(angle3);

	return points;
}

double CIND16995View::GetDistance(POINT a, POINT b)
{
	return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

void CIND16995View::DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n = 3, int rot = 0)
{
	POINT* polygon = GetRegularPoligonPoints(cx, cy, r, n, rot);

	pDC->Polygon(polygon, n + 1);

	delete[] polygon;
}

void CIND16995View::DrawBackground(CDC* pDC)
{
	CPen* oldPen = (CPen*) pDC->SelectStockObject(NULL_PEN);
	CBrush* newBrush = new CBrush(RGB(200, 200, 200)),
		* oldBrush = pDC->SelectObject(newBrush);

	pDC->Rectangle(0, 0, windowSize.Width(), windowSize.Height());

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	delete newBrush;
}

void CIND16995View::DrawTriangleWithInscribedPolygon(CDC* pDC, struct triangle t)
{
	CBrush* newBrush = nullptr;

	if (t.HB != -1)
		newBrush = new CBrush(t.HB, t.color);
	else
		newBrush = new CBrush(t.color);

	CBrush* oldBrush = pDC->SelectObject(newBrush);

	POINT* triangle = GetRegularPoligonPoints(t.center.x * this->gridSize, t.center.y * this->gridSize, t.a * this->gridSize * M_SQRT1_2, -1, t.rot);

	pDC->Polygon(triangle, 4);

	int a = this->GetDistance(triangle[0], triangle[1]),
		b = this->GetDistance(triangle[1], triangle[2]),
		c = this->GetDistance(triangle[2], triangle[0]),
		sum = a + b + c;

	POINT incenter = { (a * triangle[2].x + b * triangle[0].x + c * triangle[1].x) / sum, (a * triangle[2].y + b * triangle[0].y + c * triangle[1].y) / sum };
	double length = max(a, b, c) / 7;

	DrawRegularPolygon(pDC, incenter.x, incenter.y, length, t.inscribedPolygonPoints);

	pDC->SelectObject(oldBrush);
	delete[] triangle;
	pDC->SelectObject(oldBrush);
	delete newBrush;
}

void CIND16995View::DrawSquare(CDC* pDC, struct square s)
{
	CBrush* newBrush = nullptr;

	if (s.HB != -1)
		newBrush = new CBrush(s.HB, s.color);
	else
		newBrush = new CBrush(s.color);

	CBrush * oldBrush = pDC->SelectObject(newBrush);

	POINT* sPoints = this->GetRegularPoligonPoints(s.center.x * this->gridSize, s.center.y * this->gridSize, s.a * M_SQRT1_2 * this->gridSize, 4, 45);
	pDC->Polygon(sPoints, 5);
	delete[] sPoints;

	pDC->SelectObject(oldBrush);
	delete newBrush;
}

void CIND16995View::DrawParallelogram(CDC* pDC, struct parallelogram p)
{
	CBrush* newBrush = nullptr;

	if (p.HB != -1)
		newBrush = new CBrush(p.HB, p.color);
	else
		newBrush = new CBrush(p.color);

	CBrush* oldBrush = pDC->SelectObject(newBrush);

	p.vertex.x *= this->gridSize;
	p.vertex.y *= this->gridSize;

	POINT* pPoints = this->GetParalelogramPoints(p.vertex, p.a * this->gridSize, p.h * this->gridSize, p.rot, p.mirrorX);
	pDC->Polygon(pPoints, 5);
	delete[] pPoints;

	pDC->SelectObject(oldBrush);
	delete newBrush;
}

void CIND16995View::DrawGrid(CDC* pDC)
{
	if (this->grid)
	{
		CPen* newPen = new CPen(PS_SOLID, 1, RGB(255, 255, 255)),
			*oldPen = pDC->SelectObject(newPen);

		POINT* points = new POINT[(this->gridCount + 1) << 2];
		DWORD* lengths = new DWORD[(this->gridCount + 1) << 1];

		int endW = windowSize.Width(),
			endH = windowSize.Height(),
			step = this->gridSize,
			i = 0,
			j = 0;

		for (int par = 0; par <= endH; par += step)
		{
			points[i++] = { 0, par };
			points[i++] = { endW, par };
			lengths[j++] = 2;
		}

		for (int par = 0; par <= endW; par += step)
		{
			points[i++] = { par, 0 };
			points[i++] = { par, endH };
			lengths[j++] = 2;
		}

		pDC->PolyPolyline(points, lengths, (this->gridCount + 1) << 1);

		delete[] lengths;
		delete[] points;

		pDC->SelectObject(oldPen);
		delete newPen;
	}
}

void CIND16995View::OnDraw(CDC* pDC)
{
	CIND16995Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	this->DrawBackground(pDC);

	LOGBRUSH logbrush;
	logbrush.lbColor = this->penColor;
	logbrush.lbStyle = BS_SOLID;

	CPen* newPen = new CPen(PS_GEOMETRIC | PS_SOLID | PS_JOIN_ROUND | PS_ENDCAP_ROUND, 2, &logbrush),
		*oldPen = pDC->SelectObject(newPen);

	
	// House
	triangle t1 = {{7, 13}, 12, 135, 6, RGB(180, 0, 220), -1},
		t2 = { { 7, 13 }, 12, -45, 4, RGB(255, 255, 0), -1 },
		t3 = { { 7, 7 }, 6 * M_SQRT2, 180, 8, RGB(255, 0, 0), -1 },
		t4 = { { 16, 4 }, 6, -135, 5, RGB(255, 150, 0), -1 },
		t5 = { { 16, 16 }, 6, 135, 7, RGB(0, 200, 0), -1 };
	square s = { { 16, 10}, 6, 90, RGB(0, 0, 255), HS_FDIAGONAL };
	parallelogram p = { {7, 1}, 6, 6, 0, false, RGB(255, 185, 200), -1 };
	

	//
	//// Mariposa
	//triangle t1 = { { 4, 10 }, 6, -135, 5, RGB(255, 255, 0), -1 },
	//	t2 = { { 16, 10 }, 6, 135, 8, RGB(255, 150, 0), -1 },
	//	t3 = { { 13, 10 }, 3 * M_SQRT2, 90, 4, RGB(255, 185, 200), -1 },
	//	t4 = { { 8.5, 8.5 }, 3, 45, 6, RGB(255, 0, 0), -1 },
	//	t5 = { { 8.5, 14.5 }, 3, 135, 7, RGB(0, 0, 255), HS_FDIAGONAL };
	//square s = { { 8.5, 11.5}, 3, 90, RGB(0, 255, 0), -1 };
	//parallelogram p = { {10, 10}, 3, 3, -90, true, RGB(180, 0, 220), -1 };
	//

	this->DrawTriangleWithInscribedPolygon(pDC, t1);
	this->DrawTriangleWithInscribedPolygon(pDC, t2);
	this->DrawTriangleWithInscribedPolygon(pDC, t3);
	this->DrawTriangleWithInscribedPolygon(pDC, t4);
	this->DrawTriangleWithInscribedPolygon(pDC, t5);
	this->DrawSquare(pDC, s);
	this->DrawParallelogram(pDC, p);

	this->DrawGrid(pDC);

	delete pDC->SelectObject(oldPen);
}

// CIND16995View printing

BOOL CIND16995View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIND16995View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIND16995View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CIND16995View diagnostics

#ifdef _DEBUG
void CIND16995View::AssertValid() const
{
	CView::AssertValid();
}

void CIND16995View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIND16995Doc* CIND16995View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIND16995Doc)));
	return (CIND16995Doc*)m_pDocument;
}
#endif //_DEBUG


// CIND16995View message handlers


void CIND16995View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_SPACE)
	{
		Invalidate();
		this->grid = !this->grid;
		this->OnDraw(GetDC());
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
