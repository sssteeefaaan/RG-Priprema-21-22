
// GDIView.cpp : implementation of the CGDIView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "GDI.h"
#endif

#include "GDIDoc.h"
#include "GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define M_PI (double)3.14159265359


// CGDIView

IMPLEMENT_DYNCREATE(CGDIView, CView)

BEGIN_MESSAGE_MAP(CGDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CGDIView construction/destruction

CGDIView::CGDIView() noexcept
{
	// TODO: add construction code here

}

CGDIView::~CGDIView()
{
}

BOOL CGDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CGDIView drawing

void CGDIView::OnDraw(CDC* pDC)
{
	CRect c;
	GetClientRect(&c);

	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM t{};
	pDC->GetWorldTransform(&t);

	pDC->SetMapMode(MM_ISOTROPIC);
	pDC->SetWindowExt(100, -100);
	pDC->SetViewportExt(c.Width(), c.Height());
	pDC->SetViewportOrg(c.Width() / 2.0 + .5, c.Height() / 2.0 + .5);

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 3, RGB(255, 0, 0)));
	pDC->MoveTo(-(c.Width() / 2.0 + .5), - (c.Height() / 2.0 + .5));
	pDC->LineTo(c.Width() / 2.0 + .5, c.Height() / 2.0 + .5);

	pDC->Ellipse(10, 10, 11, 11);
	pDC->Ellipse(50, 50, 51, 51);
	pDC->Ellipse(-20, -30, -21, -31);

	//Translate(pDC, -(c.Width() / 2.0 + .5), -(c.Height() / 2.0 + .5), true);
	Rotate(pDC, -M_PI / 4.0, true);
	Scale(pDC, 1, -1, true);
	//Rotate(pDC, M_PI / 4.0, true);
	//Translate(pDC, c.Width() / 2.0 + .5, (c.Height() / 2.0 + .5), true);

	XFORM t2{};
	pDC->GetWorldTransform(&t2);

	CString sss;
	sss.Format(L"|\t%f\t%f\t%f\t|\n|\t%f\t%f\t%f\t|\n|\t%f\t%f\t%f\t|\n", t2.eM11, t2.eM12, 0.0, t2.eM21, t2.eM22, 0, t2.eDx, t2.eDy, 1.0);
	//MessageBox(sss, L"", NULL);

	pDC->Ellipse(10, 10, 11, 11);
	pDC->Ellipse(50, 50, 51, 51);
	pDC->Ellipse(-20, -30, -21, -31);

	delete(pDC->SelectObject(oldPen));

	pDC->SetWorldTransform(&t);
	pDC->SetGraphicsMode(oldGM);
}

void CGDIView::NagibniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{
	double dx = x1 - x0,
		dy = y1 - y0,
		m = dy / dx,
		b = y0 - m * x0;

	for (int x = x0; x <= x1; x++)
		WritePixel(pDC, x, m * x + b + .5, value);
}

void CGDIView::NagibniAlgoritamFULL(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{
	double dx = x1 - x0,
		dy = y1 - y0,
		m = dy / dx,
		b = y0 - m * x0;

	if (abs(m) <= 1)
		for (int x = min(x0, x1); x <= max(x0, x1); x++)
			WritePixel(pDC, x, m * x + b + .5, value);
	else
		for (int y = min(y0, y1); y <= max(y0, y1); y++)
			WritePixel(pDC, (y - b) / m + .5, y, value);
}

void CGDIView::InkrementalniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{
	double dx = x0 - x1,
		dy = y0 - y1,
		m = dy / dx,
		y = y0;

	for (int x = x0; x <= x1; x++, y += m)
		WritePixel(pDC, x, y + .5, value);
}
void CGDIView::InkrementalniAlgoritamFULL(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{
	double dx = x0 - x1,
		dy = y0 - y1,
		m = dy / dx,
		b = y0 - m * x0;

	if (abs(m) <= 1)
	{
		int x = min(x0, x1);
		double y = b + x * m;

		for (; x <= max(x0, x1); x++, y += m)
			WritePixel(pDC, x, y + .5, value);
	}
	else
	{
		int y = min(y0, y1);
		double x = (y - b) / m;

		for (; y <= max(y0, y1); x += 1.0 / m, y++)
			WritePixel(pDC, x + .5, y, value);
	}
}

void CGDIView::Bresenham(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{
	int dy = abs(y1 - y0),
		dx = abs(x1 - x0),
		incr1 = 2 * dy,
		incr2 = 2 * (dy - dx),
		d = 2 * dy - dx;

	int x = min(x0, x1),
		end = max(x0, x1),
		y = x == x0 ? y0 : y1,
		yincr = min(y0, y1) == y ? 1 : -1;

	WritePixel(pDC, x, y, value);
	for (; x <= end; x++)
	{
		if (d < 0)
			d += incr1;
		else {
			y += yincr;
			d += incr2;
		}
		WritePixel(pDC, x, y, value);
	}
}

void CGDIView::BresenhamFULL(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{
	// Maybeeee idk man.... this ish is confusing af

	int dy = abs(y1 - y0),
		dx = abs(x1 - x0);
	
	if (dy <= dx) {
		int incr1 = 2 * dy,
			incr2 = 2 * (dy - dx),
			d = 2 * dy - dx,
			x = min(x0, x1),
			end = max(x0, x1),
			y = x == x0 ? y0 : y1,
			yincr = min(y0, y1) == y ? 1 : -1;

		WritePixel(pDC, x, y, value);
		for (; x <= end; x++)
		{
			if (d < 0)
				d += incr1;
			else {
				y += yincr;
				d += incr2;
			}
			WritePixel(pDC, x, y, value);
		}
	}
	else
	{
		int y = min(y0, y1),
			end = max(y0, y1),
			x = y == y0 ? x0 : x1,
			xincr = min(x0, x1) == x ? 1 : -1,
			incr1 = -2 * dx,
			incr2 = 2 * (dy - dx),
			d = 2 * dx - dy;

		WritePixel(pDC, x, y, value);
		for (; y <= end; y++)
		{
			if (d > 0)
				d += incr1;
			else {
				x += xincr;
				d += incr2;
			}
			WritePixel(pDC, x, y, value);
		}
	}
}

#pragma region Krug

// Trigonometrijski algoritam
void CGDIView::TrigCircle(CDC* pDC, int R, COLORREF value)
{
	double step = 3.14 * 2 / (7 * R) / 8,
		angle = 0;

	for (; angle > -(3.14 / 4 + step); angle -= step)
		WritePixel8(pDC, R * cos(angle) + .5, R * sin(angle) + .5, value);
}

// Polinomni algoritam
void CGDIView::PolinomialCircle(CDC* pDC, int R, COLORREF value)
{
	int x = R, y = 0;
	while (x >= y)
		WritePixel8(pDC, x = sqrt(R * R - y * y) + .5, y++, value);
}

// Bresenhemov algoritam
void CGDIView::BresenhamCircle(CDC* pDC, int R, COLORREF value)
{
	int x = R, y = 0,
		d = 3 - 2 * R;
	while (x >= y)
	{
		WritePixel8(pDC, x, y, value);
		if (d < 0)
			d += 4 * y + 6;
		else
			d += 4 * (y - x--) + 10;
		y++;
	}
}

#pragma endregion

#pragma region Elipsa

// Trigonometrijski algoritam
void CGDIView::TrigEllipse(CDC* pDC, int a, int b, COLORREF value)
{
	double step = ((2 * 3.14) / 4) / (7 * max(a, b)),
		angle = 0;

	for (; angle > -(3.14 / 2 + step); angle -= step)
		WritePixel4(pDC, a * sin(angle), b * cos(angle), value);
}

// Polinomni algoritam
void CGDIView::PolinomialElipse(CDC* pDC, int a, int b, COLORREF value)
{
	int x = 0, y = b, dy = y;
	
	while(dy - y <= 1)
	{
		dy = y;
		y = b * sqrt(1 - pow((double)x / a, 2)) + .5;
		WritePixel4(pDC, x, y, value);
		x++;
	}
	
	y = dy;
	while(y >= 0)
	{
		x = a * sqrt(1 - pow((double)y / b, 2)) + .5;
		WritePixel4(pDC, x, y, value);
		y--;
	};
}

// Diferencijalni prvog i drugog reda
void CGDIView::I_DifferentialEllipse(CDC* pDC, int a, int b, COLORREF value)
{
	int k = 1;

	double xi1, yi1,
		xi0 = a,
		yi0 = 0,
		dPhi = 3.14 / (180 * k),
		dx = (double)a / b * dPhi,
		dy = (double)b / a * dPhi;

	for (int i = 0; i < 90 * k; i++)
	{
		xi1 = xi0 - yi0 * dx;
		yi1 = yi0 + xi0 * dy;

		BresenhamFULL(pDC, xi0 + .5, yi0 + .5, xi1 + .5, yi1 + .5, value);
		BresenhamFULL(pDC, -(xi0 + .5), yi0 + .5, -(xi1 + .5), yi1 + .5, value);
		BresenhamFULL(pDC, xi0 + .5, -(yi0 + .5), xi1 + .5, -(yi1 + .5), value);
		BresenhamFULL(pDC, -(xi0 + .5), -(yi0 + .5), -(xi1 + .5), -(yi1 + .5), value);

		xi0 = xi1;
		yi0 = yi1;
	}
}

void CGDIView::II_DifferentialEllipse(CDC* pDC, int a, int b, COLORREF value)
{
	double dPhi = 3.14 / 180,
		c = 2 - dPhi * dPhi,
		x0 = a,
		y0 = 0,
		x1 = a * cos(dPhi),
		y1 = b * sin(dPhi),
		x2,
		y2;

	for (int i = 0; i < 90; i++)
	{
		x2 = c * x1 - x0;
		y2 = c * y1 - y0;

		BresenhamFULL(pDC, x0 + .5, y0 + .5, x1 + .5, y1 + .5, value);
		BresenhamFULL(pDC, -(x0 + .5), y0 + .5, -(x1 + .5), y1 + .5, value);
		BresenhamFULL(pDC, x0 + .5, -(y0 + .5), x1 + .5, -(y1 + .5), value);
		BresenhamFULL(pDC, -(x0 + .5), -(y0 + .5), -(x1 + .5), -(y1 + .5), value);

		x0 = x1;
		x1 = x2;
		y0 = y1;
		y1 = y2;
	}
}

void CGDIView::Ellipse(CDC* pDC, int left, int top, int right, int bottom)
{
	int a = right - left,
		b = bottom - top,
		x = 0,
		y0 = b,
		y1 = y0;

	while (y1 - y0 <= 1)
	{
		WritePixel4(pDC, x, y0, 0);
		x++;
		y1 = y0;
		y0 = b * sqrt(1 - pow((double)x / a, 2)) + .5;
	}

	y0 = y1;
	while (y0 >= 0)
	{
		y0--;
		x = a * sqrt(1 - pow((double)y0 / b, 2)) + .5;
		WritePixel4(pDC, x, y0, 0);
	}
}

#pragma endregion

void CGDIView::WritePixel4(CDC* pDC, int x, int y, COLORREF value)
{
	WritePixel(pDC, x, y, value);
	WritePixel(pDC, -x, y, value);
	WritePixel(pDC, -x, -y, value);
	WritePixel(pDC, x, -y, value);
}

void CGDIView::WritePixel8(CDC* pDC, int x, int y, COLORREF value)
{
	WritePixel4(pDC, x, y, value);
	WritePixel4(pDC, y, x, value);
}

void CGDIView::WritePixel(CDC* pDC, int x, int y, COLORREF value)
{
	pDC->SetPixel(x, y, value);
}

void CGDIView::Translate(CDC* pDC, float dX, float dY, bool rM)
{
	XFORM t = { 1, 0, 0, 1, dX, dY };
	pDC->ModifyWorldTransform(&t, rM ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CGDIView::Rotate(CDC* pDC, float angle, bool rM)
{
	XFORM t{};
	t.eM11 = t.eM22 = cos(angle);
	t.eM21 = -(t.eM12 = sin(angle));
	pDC->ModifyWorldTransform(&t, rM ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CGDIView::Scale(CDC* pDC, float sX, float sY, bool rM)
{
	XFORM t = { sX, 0, 0, sY, 0, 0 };
	pDC->ModifyWorldTransform(&t, rM ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

// CGDIView printing

BOOL CGDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CGDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CGDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CGDIView diagnostics

#ifdef _DEBUG
void CGDIView::AssertValid() const
{
	CView::AssertValid();
}

void CGDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGDIDoc* CGDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGDIDoc)));
	return (CGDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CGDIView message handlers
