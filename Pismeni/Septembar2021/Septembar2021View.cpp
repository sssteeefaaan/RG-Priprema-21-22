
// Septembar2021View.cpp : implementation of the CSeptembar2021View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Septembar2021.h"
#endif

#include "Septembar2021Doc.h"
#include "Septembar2021View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSeptembar2021View

IMPLEMENT_DYNCREATE(CSeptembar2021View, CView)

BEGIN_MESSAGE_MAP(CSeptembar2021View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CSeptembar2021View construction/destruction

CSeptembar2021View::CSeptembar2021View() noexcept
{
	// TODO: add construction code here

}

CSeptembar2021View::~CSeptembar2021View()
{
}

BOOL CSeptembar2021View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CSeptembar2021View drawing

void CSeptembar2021View::OnDraw(CDC* pDC)
{
	CRect window;
	GetClientRect(&window);

	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);

	COLORREF fills[6] = { RGB(255, 0, 0), RGB(100, 200, 50), RGB(20, 20, 200), RGB(100, 150, 200), RGB(220, 220, 0), RGB(50, 50, 200) };
	bool** arcs = new bool* [4];
	for (int i = 0; i < 4; i++)
	{
		arcs[i] = new bool[4];
		for (int j = 0; j < 4; j++)
			arcs[i][j] = ((i + j) % 2);
	}

	DrawSunbeds(pDC, 100, 6, fills, RGB(255, 200, 0), arcs, 4, CPoint(window.Width() / 3.0 + .5, 100));

	for (int i = 0; i < 4; i++)
		delete(arcs[i]);
	delete[](arcs);

	SaveDC(pDC, window, window, CString("Septembar_2021.png"));

	pDC->SetGraphicsMode(oldGM);
}

void CSeptembar2021View::DrawTriangle(CDC* pDC, int side, int alpha, COLORREF clrFill, COLORREF clrLine)
{
	double alphaRad = (90 - alpha) * 3.14 / 180;
	int x = side * cos(alphaRad) + .5,
		y = -(side * sin(alphaRad) + .5);

	CPoint points[3] = { { -x, y }, { 0, 0 },  { x, y } };

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 1, clrLine));
	CBrush* oldBrush = pDC->SelectObject(new CBrush(clrFill));

	pDC->Polygon(points, 3);

	delete(pDC->SelectObject(oldBrush));
	delete(pDC->SelectObject(oldPen));
}
void CSeptembar2021View::DrawPart(CDC* pDC, int side, int alpha, COLORREF clrFill, COLORREF clrLine)
{
	double alphaRad = (90 - alpha) * 3.14 / 180;
	int x = side * cos(alphaRad) + .5,
		y = -(side * sin(alphaRad) + .5);

	CPoint points[3] = { { -x, y }, { 0, 0 },  { x, y } };

	pDC->BeginPath();
	{
		pDC->MoveTo(points[0]);
		pDC->PolylineTo(points, 3);
		pDC->ArcTo(CRect(-x, y - x / 2.0 + .5, x, y + x / 2.0 + .5), points[2], points[0]);
	}
	pDC->EndPath();

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 1, clrLine));
	CBrush* oldBrush = pDC->SelectObject(new CBrush(clrFill));

	pDC->StrokeAndFillPath();

	delete(pDC->SelectObject(oldBrush));
	delete(pDC->SelectObject(oldPen));
}
void CSeptembar2021View::DrawParasol(CDC* pDC, int side, int nElement, bool bArc, COLORREF* aclrFill, COLORREF clrLine)
{
	XFORM state;
	pDC->GetWorldTransform(&state);

	double dAlpha = 2 * 3.14 / nElement;
	int angle = 180.0 / nElement + .5;

	if (bArc)
	{
		for(int i = 0; i < nElement; i++)
		{
			DrawPart(pDC, side, angle, aclrFill[i], clrLine);
			Rotate(pDC, dAlpha, false);
		}
	}
	else
	{
		for (int i = 0; i < nElement; i++)
		{
			DrawTriangle(pDC, side, angle, aclrFill[i], clrLine);
			Rotate(pDC, dAlpha, false);
		}
	}

	pDC->SetWorldTransform(&state);
}
void CSeptembar2021View::DrawSunbed(CDC* pDC, int size, int nElement, bool bArc, COLORREF* aclrFill, COLORREF clrLine)
{
	int a = .45 * size + .5,
		r = .3 * size + .5,
		dY = - (.1 * size + .5),
		halfSize = size / 2.0 + .5;

	CPoint beds[8] = { 
		{ -halfSize, -halfSize }, { -halfSize + a, -halfSize }, { -halfSize + a, halfSize }, { -halfSize, halfSize }, 
		{ halfSize - a, -halfSize }, { halfSize, -halfSize }, { halfSize, halfSize }, { halfSize - a, halfSize }
	};
	int points[2] = { 4, 4 };

	pDC->PolyPolygon(beds, points, 2);

	XFORM state{};
	pDC->GetWorldTransform(&state);

	Translate(pDC, 0, dY, false);
	DrawParasol(pDC, r, nElement, bArc, aclrFill, clrLine);

	pDC->SetWorldTransform(&state);
}
void CSeptembar2021View::DrawSunbeds(CDC* pDC, int size, int nElement, COLORREF* aClrFill, COLORREF clrLine, bool** arArc, int n, CPoint start)
{
	XFORM state{};
	pDC->GetWorldTransform(&state);

	Translate(pDC, start.x, start.y, false);
	double shift = .45 * size + size;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			DrawSunbed(pDC, size, nElement, arArc[i][j], aClrFill, clrLine);
			Translate(pDC, shift, 0, false);
		}
		Translate(pDC, -shift * n, shift, false);
	}

	pDC->SetWorldTransform(&state);
}

void CSeptembar2021View::SaveDC(CDC* pDC, CRect rcDC, CRect rcBmp, CString sFile)
{
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, rcBmp.Width(), rcBmp.Height());

	bm = memDC->SelectObject(bm);
	memDC->StretchBlt(rcBmp.left, rcBmp.top, rcBmp.Width(), rcBmp.Height(), pDC, rcDC.left, rcDC.top, rcDC.Width(), rcDC.Height(), SRCCOPY);

	DImage img(*memDC->GetCurrentBitmap());
	img.Save(sFile);

	delete(memDC->SelectObject(bm));
	delete(memDC);
}


void CSeptembar2021View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM transform = { 1, 0, 0, 1, dX, dY };

	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY: MWT_LEFTMULTIPLY);
}
void CSeptembar2021View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM transform{};
	transform.eM11 = transform.eM22 = cos(angle);
	transform.eM21 = -(transform.eM12 = sin(angle));
	
	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

// CSeptembar2021View printing

BOOL CSeptembar2021View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CSeptembar2021View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CSeptembar2021View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CSeptembar2021View diagnostics

#ifdef _DEBUG
void CSeptembar2021View::AssertValid() const
{
	CView::AssertValid();
}

void CSeptembar2021View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CSeptembar2021Doc* CSeptembar2021View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CSeptembar2021Doc)));
	return (CSeptembar2021Doc*)m_pDocument;
}
#endif //_DEBUG


// CSeptembar2021View message handlers
