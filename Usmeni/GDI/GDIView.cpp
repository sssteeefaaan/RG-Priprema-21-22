
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
	
	Translate(pDC, c.Width() / 2.0 + .5, c.Height() / 2.0 + .5);
	InkrementalniAlgoritam(pDC, 100, 0, -100, -300, RGB(255, 0, 0));

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
void CGDIView::InkrementalniAlgoritamFULL(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value)
{

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
