
// Oktobar2021View.cpp : implementation of the COktobar2021View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Oktobar2021.h"
#endif

#include "Oktobar2021Doc.h"
#include "Oktobar2021View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COktobar2021View

IMPLEMENT_DYNCREATE(COktobar2021View, CView)

BEGIN_MESSAGE_MAP(COktobar2021View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// COktobar2021View construction/destruction

COktobar2021View::COktobar2021View() noexcept
{
	// TODO: add construction code here

}

COktobar2021View::~COktobar2021View()
{
}

BOOL COktobar2021View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COktobar2021View drawing

void COktobar2021View::OnDraw(CDC* pDC)
{
	CRect window;
	GetClientRect(&window);

	XFORM state{};
	pDC->GetWorldTransform(&state);
	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);

	LoadIdentity(pDC);

	Translate(pDC, 200, window.Height() / 2.0 + .5, false);
	DrawTail(pDC, 25, 6, 0);

	Translate(pDC, 400, 0, false);
	DrawTail(pDC, 25, 6, -3.14 / 8.0);

	Translate(pDC, 400, 0, false);
	DrawTail(pDC, 25, 6, -3.14 / 4);

	pDC->SetGraphicsMode(oldGM);
	pDC->SetWorldTransform(&state);
}

void COktobar2021View::DrawTop(CDC* pDC, int size)
{
	int halfSize = size / 2.0 + .5,
		quarterSize = size / 4.0 + .5;

	CPoint start1(halfSize, 0), start2(0, halfSize), start3(0, size);

	int oldAD = pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
	pDC->BeginPath();
	{
		pDC->MoveTo(start1);
		pDC->ArcTo(CRect(-halfSize, -halfSize, halfSize, halfSize), start1, start2);
		pDC->SetArcDirection(AD_CLOCKWISE);
		pDC->ArcTo(CRect(-quarterSize, halfSize, quarterSize, size), start2, start3);
		pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
		pDC->ArcTo(CRect(-halfSize, -size, halfSize, size), start3, start1);
	}
	pDC->EndPath();
	pDC->SetArcDirection(oldAD);

	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(255, 100, 0)));
	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 2, RGB(0, 0, 0)));

	pDC->StrokeAndFillPath();

	delete(pDC->SelectObject(oldPen));
	delete(pDC->SelectObject(oldBrush));
}
void COktobar2021View::LoadIdentity(CDC* pDC)
{
	pDC->ModifyWorldTransform(NULL, MWT_IDENTITY);
}
void COktobar2021View::Mirror(CDC* pDC, bool x, bool y, bool rightMultiply)
{
	XFORM transform{};
	transform.eM11 = x ? -1 : 1;
	transform.eM22 = y ? -1 : 1;

	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void COktobar2021View::Translate(CDC* pDC, double x, double y, bool rightMultiply)
{
	XFORM transform = { 1, 0, 0, 1, x, y };

	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void COktobar2021View::Rotate(CDC* pDC, double alpha, bool rightMultiply)
{
	XFORM transform{};
	transform.eM11 = transform.eM22 = cos(alpha);
	transform.eM21 = -(transform.eM12 = sin(alpha));

	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void COktobar2021View::DrawTop2(CDC* pDC, int size)
{
	XFORM state{};
	pDC->GetWorldTransform(&state);

	Mirror(pDC, false, true, false);
	// Objekar je reflektovan oko Y-ose

	Rotate(pDC, -90 * 3.14 / 180, false);
	DrawTop(pDC, size);

	pDC->SetWorldTransform(&state);
}
void COktobar2021View::DrawTail(CDC* pDC, int size, int count, double alpha)
{
	XFORM state{};
	pDC->GetWorldTransform(&state);

	int halfSize = size / 2.0 + .5;

	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(255, 100, 0)));
	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 2, RGB(0, 0, 0)));

	for (int i = 0; i < count; i++)
	{
		pDC->Ellipse(-size, -halfSize, size, halfSize);
		Translate(pDC, size, 0, false);
		Rotate(pDC, alpha, false);
		Translate(pDC, size, 0, false);
	}

	delete(pDC->SelectObject(oldPen));
	delete(pDC->SelectObject(oldBrush));

	Translate(pDC, -halfSize, 0, false);
	DrawTop2(pDC, size);

	pDC->SetWorldTransform(&state);
}


// COktobar2021View printing

BOOL COktobar2021View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COktobar2021View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COktobar2021View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COktobar2021View diagnostics

#ifdef _DEBUG
void COktobar2021View::AssertValid() const
{
	CView::AssertValid();
}

void COktobar2021View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COktobar2021Doc* COktobar2021View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COktobar2021Doc)));
	return (COktobar2021Doc*)m_pDocument;
}
#endif //_DEBUG


// COktobar2021View message handlers
