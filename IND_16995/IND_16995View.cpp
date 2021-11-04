
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
	// TODO: add construction code here
	this->grid = false;
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
#define _USE_MATH_DEFINES
#include <math.h>

struct triangle {
	POINT center;
	int h;
	int rot;
	int inscribedPolygonPoints;
	COLORREF color;
};

POINT* GetRegularPoligonPoints(int cx, int cy, int r, int n = -1, int rot = 0)
{
	POINT* polygon = nullptr;
	double angle, fi;

	// Ukoliko je rec o pravouglom trouglu, to se svodi na kvadrat bez x = cx + 0, y = cy - r komponente
	// To ce biti default figura ukoliko se prosledi n < 3
	if (n > 2)
		angle = 2 * M_PI / n;
	else
	{
		angle = M_PI / 2;
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

void DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n = 3, int rot = 0)
{
	POINT* polygon = GetRegularPoligonPoints(cx, cy, r, n, rot);

	pDC->Polygon(polygon, n + 1);
	delete[] polygon;
}

void DrawTriangleWithInscribedPolygon(CDC* pDC, struct triangle t)
{
	CBrush* newBrush = new CBrush(t.color),
		*oldBrush = pDC->SelectObject(newBrush);
	POINT* triangle = GetRegularPoligonPoints(t.center.x, t.center.y, t.h, -1, t.rot);
	pDC->Polygon(triangle, 4);

	int a = sqrt(pow(triangle[0].x - triangle[1].x, 2) + pow(triangle[0].y - triangle[1].y, 2)),
		b = sqrt(pow(triangle[1].x - triangle[2].x, 2) + pow(triangle[1].y - triangle[2].y, 2)),
		c = sqrt(pow(triangle[2].x - triangle[0].x, 2) + pow(triangle[2].y - triangle[0].y, 2)),
		sum = a + b + c;

	POINT vertex = { (a * triangle[2].x + b * triangle[0].x + c * triangle[1].x) / sum, (a * triangle[2].y + b * triangle[0].y + c * triangle[1].y) / sum };
	double length = max(a, b, c) / 7;

	DrawRegularPolygon(pDC, vertex.x, vertex.y, length, t.inscribedPolygonPoints);

	pDC->SelectObject(oldBrush);
	delete[] triangle;
	delete newBrush;
}

void CIND16995View::OnDraw(CDC* pDC)
{
	CIND16995Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect clientRect;
	GetClientRect(&clientRect);

	/*int mapMode = pDC->SetMapMode(MM_ISOTROPIC);
	CSize windowExt = pDC->SetWindowExt(500, 500),
	viewportExt = pDC->SetViewportExt(clientRect.Width(), clientRect.Height());
	CPoint windowOrg = pDC->SetWindowOrg(0, 0);*/

	CPen* newPen = new CPen(PS_NULL, 0, RGB(255, 255, 255)),
		* oldPen = pDC->SelectObject(newPen);
	CBrush* newBrush = new CBrush(RGB(200, 200, 200)),
		*oldBrush = pDC->SelectObject(newBrush);

	pDC->Rectangle(0, 0, 500, 500);
	delete newBrush;
	delete newPen;

	LOGBRUSH brush;
	brush.lbColor = RGB(0, 0, 255);
	brush.lbStyle = BS_SOLID;

	newPen = new CPen(PS_GEOMETRIC | PS_SOLID | PS_JOIN_ROUND, 2, &brush);
	pDC->SelectObject(newPen);

	triangle purple = { { 175, 325 }, 212, 135, 6, RGB(180, 0, 220) },
		yellow = { { 175, 325 }, 212, -45, 4, RGB(255, 255, 0) },
		red = { { 175, 175 }, 150, 180, 8, RGB(255, 0, 0) },
		orange = { { 400, 100 }, 106, -135, 5, RGB(255, 150, 0) },
		green = { { 400, 400 }, 106, 135, 7, RGB(0, 200, 0) };

	/*
	* Mariposa
	* 
	triangle purple = { { 400, 250 }, 106, 135, 6, RGB(180, 0, 220) },
		yellow = { { 101, 250 }, 106, -135, 4, RGB(255, 255, 0) },
		red = { { 325, 250 }, 75, 90, 8, RGB(255, 0, 0) },
		orange = { { 213, 213 }, 53, 45, 5, RGB(255, 150, 0) },
		green = { { 213, 362 }, 53, 135, 7, RGB(0, 200, 0) };

	pDC->Rectangle(175, 250, 250, 325);
	POINT rPink[] = { {250, 250}, {325, 325}, {325, 400}, {250, 325}, {250, 250} };

	*/

	DrawTriangleWithInscribedPolygon(pDC, purple);
	DrawTriangleWithInscribedPolygon(pDC, yellow);
	DrawTriangleWithInscribedPolygon(pDC, red);
	DrawTriangleWithInscribedPolygon(pDC, orange);
	DrawTriangleWithInscribedPolygon(pDC, green);

	newBrush = new CBrush(HS_FDIAGONAL, RGB(0, 0, 255));
	pDC->SelectObject(newBrush);
	pDC->Rectangle(325, 175, 475, 325);
	delete newBrush;

	newBrush = new CBrush(RGB(255, 150, 220));
	pDC->SelectObject(newBrush);
	POINT rPink[] = { {175, 25}, {325, 25}, {475, 175}, {325, 175}, {175, 25} };
	pDC->Polygon(rPink, 5);
	delete newBrush;

	this->Grid(pDC);

	pDC->SelectObject(oldPen);
	delete newPen;

	/*pDC->SetWindowOrg(windowOrg);
	pDC->SetViewportExt(viewportExt);
	pDC->SetWindowExt(windowExt);
	pDC->SetMapMode(mapMode);*/
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
		this->grid = !this->grid;
		this->OnDraw(GetDC());
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CIND16995View::Grid(CDC* pDC)
{
	if (this->grid)
	{
		CPen* newPen = new CPen(PS_SOLID, 1, RGB(255, 255, 255)),
			*oldPen = pDC->SelectObject(newPen);

		for (int par = 0; par <= 500; par += 25)
		{
			pDC->MoveTo(0, par);
			pDC->LineTo(500, par);
			pDC->MoveTo(par, 0);
			pDC->LineTo(par, 500);
		}

		pDC->SelectObject(oldPen);
		delete newPen;
	}
}
