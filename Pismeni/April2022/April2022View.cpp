
// April2022View.cpp : implementation of the CApril2022View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "April2022.h"
#endif

#include "April2022Doc.h"
#include "April2022View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApril2022View

IMPLEMENT_DYNCREATE(CApril2022View, CView)

BEGIN_MESSAGE_MAP(CApril2022View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CApril2022View construction/destruction

CApril2022View::CApril2022View() noexcept
{
	m_angle = 0;
}

CApril2022View::~CApril2022View()
{
}

BOOL CApril2022View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CApril2022View drawing

void CApril2022View::OnDraw(CDC* pDC)
{
	CRect c;
	GetClientRect(&c);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, c.Width(), c.Height());
	bm = memDC->SelectObject(bm);

	int oldGM = memDC->SetGraphicsMode(GM_ADVANCED);
	XFORM t{};
	memDC->GetWorldTransform(&t);

	CString arStr[] = {
		L"1.",
		L"2.",
		L"3.",
		L"4.",
		L"5.",
		L"6."
	};
	memDC->Rectangle(c);
	DrawObservationWheel(memDC, 200, 3, 18, RGB(145, 178, 211), arStr, 16, 3, CPoint(c.Width() / 2.0 + .5, c.Height() / 2.0 + .5), m_angle * 3.14 / 180);

	memDC->SetWorldTransform(&t);
	memDC->SetGraphicsMode(oldGM);

	pDC->BitBlt(0, 0, c.Width(), c.Height(), memDC, 0, 0, SRCCOPY);
	
	delete(memDC->SelectObject(bm));
	delete(memDC);
}

void CApril2022View::DrawCybin(CDC* pDC, int w, int d, COLORREF clr, CString str, int size)
{
	pDC->BeginPath();
	pDC->MoveTo(-w / 2.0 - .5, 0);
	pDC->LineTo(-w / 2.0 - .5, w);
	pDC->LineTo(w / 2.0 + .5, w);
	pDC->LineTo(w / 2.0 + .5, 0);
	pDC->ArcTo(CRect(-w / 2.0 - .5, -w / 2.0 - .5, w / 2.0 + .5, w / 2.0 + .5), CPoint(w / 2.0 + .5, 0), CPoint(-w / 2.0 - .5, 0));
	pDC->EndPath();

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, d, clr));
	CBrush* oldBrush = pDC->SelectObject(new CBrush(min(255, clr * 1.2 + .5)));

	pDC->StrokeAndFillPath();
	pDC->MoveTo(0, -w / 2.0 - .5);
	// pDC->LineTo(0, -w / 2.0 - w * .25 - .5); Kratko, nije lepo
	pDC->LineTo(0, -w);

	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	int oldTxtColor = pDC->SetTextColor(RGB(255, 255, 255));
	
	CFont* oldFont = new CFont();
	oldFont->CreateFontW(size, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 0, 0, L"Arial");
	oldFont = pDC->SelectObject(oldFont);
	CSize c = pDC->GetTextExtent(str);

	pDC->TextOutW(-c.cx / 2.0 - .5, w / 2.0 - c.cy + .5, str);

	delete(pDC->SelectObject(oldFont));
	pDC->SetTextColor(oldTxtColor);
	pDC->SetBkMode(oldBkMode);
	delete(pDC->SelectObject(oldBrush));
	delete(pDC->SelectObject(oldPen));
}

void CApril2022View::DrawWheel(CDC* pDC, int r, int d, int n, COLORREF clr)
{
	double dAlpha = 3.14 / (n / 2.0),
		angle = 3.14 / 2.0;

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 3 * d, clr));
	CBrush* oldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);

	pDC->Ellipse(-r, -r, r, r);
	pDC->Ellipse(-.8 * r - .5, -.8 * r - .5, .8 * r + .5, .8 * r + .5);

	delete(pDC->SelectObject(new CPen(PS_SOLID, d, clr)));

	for (int i = 0; i < n / 2.0 + .5; i++)
	{
		double cosi = cos(angle),
			sini = sin(angle);

		pDC->MoveTo(r * cosi + .5, r * sini + .5);
		pDC->LineTo(-r * cosi -.5, -r * sini -.5);

		angle -= dAlpha;
	}

	pDC->SelectObject(new CBrush(clr));
	
	pDC->Ellipse(-.1 * r - .5, -.1 * r - .5, .1 * r + .5, .1 * r + .5);

	delete(pDC->SelectObject(oldBrush));
	delete(pDC->SelectObject(oldPen));
}
void CApril2022View::DrawObservationWheel(CDC* pDC, int r, int d, int n, COLORREF clr, CString arStr[], int size, int k, CPoint ptCenter, float alpha)
{
	XFORM t{};
	pDC->GetWorldTransform(&t);

	CBrush* oldBrush = (CBrush*)pDC->SelectStockObject(NULL_BRUSH);
	CPen* oldPen = (CPen*)pDC->SelectObject(new CPen(PS_SOLID, d, clr));
	CPoint v[] =
	{
		CPoint(0, 0),
		CPoint(-.8 * r - .5, 1.6 * r + .5),
		CPoint(.8 * r + .5, 1.6 * r + .5)
	};

	Translate(pDC, ptCenter.x, ptCenter.y, false);
	pDC->Polygon(v, 3);

	Rotate(pDC, alpha, false);
	DrawWheel(pDC, r, d, n, clr);

	XFORM t2{};
	pDC->GetWorldTransform(&t2);
	
	double dAlpha = 2 * 3.14 / n * k,
		angle = 0;

	for (int i = 0; i < n / k; i++)
	{
		Rotate(pDC, angle, false);
		Translate(pDC, 0, r, false);
		Rotate(pDC, -(angle + alpha), false);
		Translate(pDC, 0, (.2 * r) + .5, false);
		DrawCybin(pDC, .2 * r + .5, d, clr, arStr[i], size);

		angle -= dAlpha;
		pDC->SetWorldTransform(&t2);
	}


	delete(pDC->SelectObject(oldPen));
	pDC->SelectObject(oldBrush);
	pDC->SetWorldTransform(&t);
}
void CApril2022View::SaveDC(CDC* pDC, CRect rcDC, CRect rcBmp, CString strBmp)
{

}

void CApril2022View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM t = { 1, 0, 0, 1, dX, dY };

	pDC->ModifyWorldTransform(&t, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CApril2022View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM t{};
	t.eM11 = t.eM22 = cos(angle);
	t.eM21 = -(t.eM12 = sin(angle));

	pDC->ModifyWorldTransform(&t, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}


// CApril2022View printing

BOOL CApril2022View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CApril2022View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CApril2022View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CApril2022View diagnostics

#ifdef _DEBUG
void CApril2022View::AssertValid() const
{
	CView::AssertValid();
}

void CApril2022View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApril2022Doc* CApril2022View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApril2022Doc)));
	return (CApril2022Doc*)m_pDocument;
}
#endif //_DEBUG


// CApril2022View message handlers


void CApril2022View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case('A'):
		m_angle += 5;
		break;
	case('D'):
		m_angle -= 5;
		break;
	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	Invalidate();
}


BOOL CApril2022View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
