
// Januar2022View.cpp : implementation of the CJanuar2022View class
//

#include "pch.h"
#include "framework.h"
#include <strstream>
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Januar2022.h"
#endif

#include "Januar2022Doc.h"
#include "Januar2022View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CJanuar2022View

IMPLEMENT_DYNCREATE(CJanuar2022View, CView)

BEGIN_MESSAGE_MAP(CJanuar2022View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CJanuar2022View construction/destruction

CJanuar2022View::CJanuar2022View() noexcept
{
	// TODO: add construction code here

}

CJanuar2022View::~CJanuar2022View()
{
}

BOOL CJanuar2022View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CJanuar2022View drawing

void CJanuar2022View::OnDraw(CDC* pDC)
{
	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);

	DrawMagnifiedBitmap(pDC, 2, CString("Januar_2022.dib"));

	pDC->SetGraphicsMode(oldGM);
}

void CJanuar2022View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM transform{};
	transform.eM11 = transform.eM22 = 1;
	transform.eDx = dX;
	transform.eDy = dY;

	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CJanuar2022View::Rotate(CDC* pDC, float alpha, bool rightMultiply)
{
	XFORM transform {};
	transform.eM21 = - (transform.eM12 = sin(alpha));
	transform.eM11 = transform.eM22 = cos(alpha);

	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CJanuar2022View::Part1(CDC* pDC, int size)
{
	CPoint points[4] = { { -size, -size }, { -size, size }, { size, size }, { size, -size } };

	pDC->BeginPath();
	{
		pDC->MoveTo(-size, -size);
		pDC->PolylineTo(points, 4);
		pDC->ArcTo(CRect(-size, -2 * size, size, 0), points[3], points[0]);
	}
	pDC->EndPath();

	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(255, 255, 0)));
	pDC->StrokeAndFillPath();
	delete(pDC->SelectObject(oldBrush));
}

void CJanuar2022View::Part2(CDC* pDC, int size)
{
	CPoint points[4] = { { size, size }, { -size, size }, { -size, -size }, { size, -size } };

	pDC->BeginPath();
	{
		pDC->MoveTo(size, size);
		pDC->PolylineTo(points, 4);
		pDC->ArcTo(CRect(0, -size, 2 * size, size), points[3], points[0]);
	}
	pDC->EndPath();

	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(0, 255, 0)));
	pDC->StrokeAndFillPath();
	delete(pDC->SelectObject(oldBrush));
}

void CJanuar2022View::Part3(CDC* pDC, int size)
{
	CPoint points[5] = { { -size, size }, { -size, -size }, { size, -size }, { size, size }, { 0, 0 } };
	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(255, 0, 0)));
	pDC->Polygon(points, 5);
	delete(pDC->SelectObject(oldBrush));
}

void CJanuar2022View::Part4(CDC* pDC, int size)
{
	CPoint points[5] = { { -size, size }, { -2 * size, 0 }, { -size, -size }, { size, -size }, { size, size } };
	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(0, 0, 255)));
	pDC->Polygon(points, 5);
	delete(pDC->SelectObject(oldBrush));
}

void CJanuar2022View::DrawPuzzle(CDC* pDC, int size, float angle, int x, int y)
{
	XFORM state{};
	pDC->GetWorldTransform(&state);

	Translate(pDC, x, y, false);
	Rotate(pDC, angle, false);
	Part1(pDC, size);

	XFORM temp{};
	pDC->GetWorldTransform(&temp);
	{
		Translate(pDC, 0, -2 * size, false);
		Rotate(pDC, 3.14 / 2, false);
		Part2(pDC, size);

		Translate(pDC, -2 * size, 0, false);
		Rotate(pDC, -3.14 / 2, false);
		Part1(pDC, size);
	}
	pDC->SetWorldTransform(&temp);

	Translate(pDC, -2 * size, 0, false);
	Rotate(pDC, 3.14 / 2.0, false);
	Part3(pDC, size);
	
	Translate(pDC, 0, 2 * size, false);
	Rotate(pDC, 3.14 / 2, false);
	Part4(pDC, size);

	pDC->SetWorldTransform(&state);
}

void CJanuar2022View::DrawMagnifiedBitmap(CDC* pDC, int mag, const CString& name)
{
	CRect window;
	GetClientRect(&window);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* newBitmap = new CBitmap();
	newBitmap->CreateCompatibleBitmap(pDC, window.Width(), window.Height());
	CBitmap* current = memDC->SelectObject(newBitmap);

	memDC->SetGraphicsMode(GM_ADVANCED);
	memDC->SetMapMode(MM_ANISOTROPIC);
	memDC->SetWindowExt(window.Width() / (double)mag + .5, window.Height() / (double)mag + .5);
	memDC->SetViewportExt(window.Width(), window.Height());
	memDC->SetViewportOrg(0, 0);

	memDC->Rectangle(window);
	DrawPuzzle(memDC, 25, 3.14 / 4, window.Width() / (mag * 2.0) + .5, window.Height() / (mag * 2.0) + .5);

	DImage img(*newBitmap);
	img.Save(name);

	//pDC->BitBlt(0, 0, window.Width(), window.Height(), memDC, 0, 0, SRCCOPY);

	delete(memDC->SelectObject(current));
	delete(memDC);
}


// CJanuar2022View printing

BOOL CJanuar2022View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJanuar2022View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJanuar2022View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CJanuar2022View diagnostics

#ifdef _DEBUG
void CJanuar2022View::AssertValid() const
{
	CView::AssertValid();
}

void CJanuar2022View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJanuar2022Doc* CJanuar2022View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJanuar2022Doc)));
	return (CJanuar2022Doc*)m_pDocument;
}
#endif //_DEBUG


// CJanuar2022View message handlers
