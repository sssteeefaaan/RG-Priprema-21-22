
// Januar2020View.cpp : implementation of the CJanuar2020View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Januar2020.h"
#endif

#include "Januar2020Doc.h"
#include "Januar2020View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJanuar2020View

IMPLEMENT_DYNCREATE(CJanuar2020View, CView)

BEGIN_MESSAGE_MAP(CJanuar2020View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CJanuar2020View construction/destruction

CJanuar2020View::CJanuar2020View() noexcept
{
	// TODO: add construction code here

}

CJanuar2020View::~CJanuar2020View()
{
}

BOOL CJanuar2020View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CJanuar2020View drawing

void CJanuar2020View::OnDraw(CDC* pDC)
{
	CRect window;
	GetClientRect(&window);

	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM state{};
	pDC->GetWorldTransform(&state);

	Translate(pDC, window.Width() / 2.0 + .5, window.Height() / 2.0 + .5, false);
	CPoint endBike = DrawBicycle(pDC, 200, 20, 10, 45, -60);

	Translate(pDC, endBike.x, endBike.y, false);
	Draw_Text(pDC, 50, CString("Penny - Farthing"), RGB(0, 60, 225));

	pDC->SetWorldTransform(&state);
	pDC->SetGraphicsMode(oldGM);

	SaveDC(pDC, window, window);
}

void CJanuar2020View::DrawCycle(CDC* pDC, int r, int n, int d)
{
	CPoint* points = new CPoint[n << 1];
	DWORD* segments = new DWORD[n];
	double dAngle = 2.0 * 3.14 / n,
		angle = 0,
		dr = d / 2.0 + .5;

	for (int i = 0; i < n << 1; i++)
	{
		segments[i >> 1] = 2;
		points[i++] = CPoint(0, 0);
		points[i] = CPoint(r * cos(angle) + .5, r * sin(angle) + .5);
		angle += dAngle;
	}

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 2, RGB(0, 60, 225)));

	pDC->PolyPolyline(points, segments, n);

	delete(pDC->SelectObject(new CPen(PS_SOLID, d, RGB(0, 50, 200))));
	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(0, 50, 200)));

	pDC->Ellipse(-d, -d, d, d);

	delete((CBrush*)pDC->SelectStockObject(NULL_BRUSH));

	pDC->Ellipse(-r, -r, r, r);

	pDC->SelectObject(oldBrush);
	delete(pDC->SelectObject(oldPen));
}
CPoint CJanuar2020View::DrawBicycle(CDC* pDC, int r, int n, int d, int alpha, int beta)
{
	XFORM state{};
	pDC->GetWorldTransform(&state);

	double rSmall = (double)r / 4.0,
		frontShaft = 1.4 * r,
		gear = .2 * r,
		peddalShaft = .4 * r,
		alphaRad = alpha * 3.14 / 180.0,
		peddals = .2 * r,
		rArcBig = 1.2 * r,
		rArcSmall = 3.0 / 4.0 * r,
		stepLadder = .2 * r,
		saddleShaft = .2 * r,
		betaRad = beta * 3.14 / 180.0,
		saddle = .3 * r;

	DrawCycle(pDC, r, n, d);

	int oldAD = pDC->SetArcDirection(AD_CLOCKWISE);

	CPoint endPoint(0, 0);

	pDC->BeginPath();
	{
		CPoint peddalShaftBegin(peddalShaft * cos(alphaRad) + .5, peddalShaft * sin(alphaRad) + .5),
			peddalShaftEnd(-peddalShaftBegin.x, -peddalShaftBegin.y);

		pDC->MoveTo(peddalShaftBegin);
		pDC->LineTo(peddalShaftEnd);

		pDC->MoveTo(peddalShaftBegin.x - peddals / 2.0 + .5, peddalShaftBegin.y);
		pDC->LineTo(peddalShaftBegin.x + peddals / 2.0 + .5, peddalShaftBegin.y);
		
		pDC->MoveTo(peddalShaftEnd.x - peddals / 2.0 + .5, peddalShaftEnd.y);
		pDC->LineTo(peddalShaftEnd.x + peddals / 2.0 + .5, peddalShaftEnd.y);

		pDC->MoveTo(0, 0);
		pDC->LineTo(0, -frontShaft - .5);
		pDC->LineTo(gear, -frontShaft - .5);

		CPoint startShaft(0, -rArcBig - .5),
			endShaft(rArcBig + .5, 0);

		pDC->MoveTo(startShaft);
		pDC->ArcTo(CRect(-rArcBig - .5, -rArcBig - .5, rArcBig + .5, rArcBig + .5), startShaft, endShaft);

		pDC->LineTo(endShaft.x + stepLadder + .5, endShaft.y);
		pDC->MoveTo(endShaft);

		pDC->SetArcDirection(AD_COUNTERCLOCKWISE);
		endPoint.x = endShaft.x + rArcSmall + .5;
		endPoint.y = endShaft.y + rArcSmall + .5;

		pDC->ArcTo(CRect(endShaft.x, endShaft.y - rArcSmall - .5, endShaft.x + rArcSmall * 2 + .5, endShaft.y + rArcSmall + .5), endShaft, endPoint);

		CPoint saddleStart(rArcBig * cos(betaRad) + .5, rArcBig * sin(betaRad) + .5),
			saddleEnd(saddleStart.x + saddleShaft * cos(betaRad) + .5, saddleStart.y + saddleShaft * sin(betaRad) + .5);

		pDC->MoveTo(saddleStart);
		pDC->LineTo(saddleEnd);
		pDC->MoveTo(saddleEnd.x - saddle / 2.0 - .5, saddleEnd.y);
		pDC->LineTo(saddleEnd.x + saddle / 2.0 + .5, saddleEnd.y);
	}
	pDC->EndPath();
	pDC->SetArcDirection(oldAD);

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, d, RGB(0, 60, 225)));

	pDC->StrokePath();

	Translate(pDC, endPoint.x, endPoint.y, false);
	DrawCycle(pDC, rSmall, n, d);

	delete(pDC->SelectObject(oldPen));
	pDC->SetWorldTransform(&state);

	endPoint.x += rSmall + .5;
	endPoint.y += rSmall + .5;

	return endPoint;
}
void CJanuar2020View::Draw_Text(CDC* pDC, int size, CString strText, COLORREF clrText)
{
	LOGFONT lFont{};
	lFont.lfHeight = size;
	lFont.lfEscapement = 900;
	lFont.lfOrientation = 900;
	wcscpy_s(lFont.lfFaceName, CString("Arial"));

	CFont* cFont = new CFont();
	cFont->CreateFontIndirectW(&lFont);

	int oldTA = pDC->SetTextAlign(TA_TOP | TA_LEFT);
	int oldBkMode = pDC->SetBkMode(TRANSPARENT);
	COLORREF oldTC = pDC->SetTextColor(clrText);

	cFont = pDC->SelectObject(cFont);

	pDC->TextOutW(0, 0, strText);

	delete(pDC->SelectObject(cFont));
	pDC->SetTextColor(oldTC);
	pDC->SetBkMode(oldBkMode);
	pDC->SetTextAlign(oldTA);
}
void CJanuar2020View::SaveDC(CDC* pDC, CRect rcDC, CRect rcBmp)
{
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, rcBmp.Width(), rcBmp.Height());

	bm = memDC->SelectObject(bm);

	memDC->StretchBlt(rcBmp.left, rcBmp.top, rcBmp.Width(), rcBmp.Height(), pDC, rcDC.left, rcDC.top, rcDC.Width(), rcDC.Height(), SRCCOPY);

	DImage img(*memDC->GetCurrentBitmap());
	img.Save(CString("Januar_2020.png"));

	delete(memDC->SelectObject(bm));
	delete(memDC);
}
void CJanuar2020View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM transformation = { 1, 0, 0, 1, dX, dY };

	pDC->ModifyWorldTransform(&transformation, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CJanuar2020View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM transformation{};
	transformation.eM11 = transformation.eM22 = cos(angle);
	transformation.eM21 = -(transformation.eM12 = sin(angle));

	pDC->ModifyWorldTransform(&transformation, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}


// CJanuar2020View printing

BOOL CJanuar2020View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJanuar2020View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJanuar2020View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CJanuar2020View diagnostics

#ifdef _DEBUG
void CJanuar2020View::AssertValid() const
{
	CView::AssertValid();
}

void CJanuar2020View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJanuar2020Doc* CJanuar2020View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJanuar2020Doc)));
	return (CJanuar2020Doc*)m_pDocument;
}
#endif //_DEBUG


// CJanuar2020View message handlers
