
// Termin2View.cpp : implementation of the CTermin2View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Termin2.h"
#endif

#include "Termin2Doc.h"
#include "Termin2View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTermin2View

IMPLEMENT_DYNCREATE(CTermin2View, CView)

BEGIN_MESSAGE_MAP(CTermin2View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CTermin2View construction/destruction

CTermin2View::CTermin2View() noexcept
{
	// TODO: add construction code here

}

CTermin2View::~CTermin2View()
{
}

BOOL CTermin2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTermin2View drawing

void CTermin2View::OnDraw(CDC* pDC)
{
	CTermin2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect window;
	GetClientRect(&window);

	int mapMode = pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(500, -500);
	pDC->SetViewportExt(window.Width(), window.Height());
	pDC->SetViewportOrg(window.Width() / 2, window.Height() / 2);

	// pDC->SetBkColor(RGB(255, 255, 0));

	LOGBRUSH logBrush;
	logBrush.lbStyle = PS_SOLID;
	logBrush.lbColor = RGB(255, 0, 0);

	CPen* newPen = new CPen(PS_GEOMETRIC | PS_DASHDOT | PS_ENDCAP_ROUND, 1, &logBrush),
		* oldPen = pDC->SelectObject(newPen);

	//pDC->MoveTo(0, 0);
	pDC->LineTo(250, 250);

	logBrush.lbColor = RGB(0, 255, 0);
	newPen = new CPen(PS_GEOMETRIC | PS_DASH | PS_ENDCAP_SQUARE, 2, &logBrush);
	pDC->SelectObject(newPen);

	pDC->MoveTo(0, 0);
	pDC->LineTo(250, -250);

	logBrush.lbColor = RGB(0, 0, 255);
	newPen = new CPen(PS_GEOMETRIC | PS_DOT | PS_ENDCAP_ROUND, 5, &logBrush);
	pDC->SelectObject(newPen);

	pDC->MoveTo(0, 0);
	pDC->LineTo(-250, -250);

	// User style
	DWORD lpStyle[] = { 20, 10, 25, 15, 10, 30, 20, 10, 15, 15 };

	logBrush.lbColor = RGB(0, 200, 200);
	newPen = new CPen(PS_GEOMETRIC | PS_USERSTYLE | PS_ENDCAP_FLAT, 10, &logBrush, 10, lpStyle);
	pDC->SelectObject(newPen);

	pDC->MoveTo(0, 0);
	pDC->LineTo(-250, 250);

	pDC->SelectObject(oldPen);
	newPen->DeleteObject();
	delete newPen;

	pDC->SetMapMode(mapMode);
}


// CTermin2View printing

BOOL CTermin2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTermin2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTermin2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CTermin2View diagnostics

#ifdef _DEBUG
void CTermin2View::AssertValid() const
{
	CView::AssertValid();
}

void CTermin2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTermin2Doc* CTermin2View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTermin2Doc)));
	return (CTermin2Doc*)m_pDocument;
}
#endif //_DEBUG


// CTermin2View message handlers
