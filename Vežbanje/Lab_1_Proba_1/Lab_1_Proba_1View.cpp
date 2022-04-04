
// Lab_1_Proba_1View.cpp : implementation of the CLab1Proba1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Lab_1_Proba_1.h"
#endif

#include "Lab_1_Proba_1Doc.h"
#include "Lab_1_Proba_1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLab1Proba1View

IMPLEMENT_DYNCREATE(CLab1Proba1View, CView)

BEGIN_MESSAGE_MAP(CLab1Proba1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CLab1Proba1View construction/destruction

CLab1Proba1View::CLab1Proba1View() noexcept
{
	// TODO: add construction code here

}

CLab1Proba1View::~CLab1Proba1View()
{
}

BOOL CLab1Proba1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CLab1Proba1View drawing

void CLab1Proba1View::OnDraw(CDC* pDC)
{
	CLab1Proba1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect window;
	GetClientRect(&window);

	int mapMode = pDC->SetMapMode(MM_ANISOTROPIC);
	pDC->SetWindowExt(550, -550);
	pDC->SetViewportExt(window.Width(), window.Height());
	pDC->SetWindowOrg(-275, 275);
	// pDC->SetViewportOrg(window.Width() / 2, window.Height() / 2);

	LOGBRUSH logBrush;
	logBrush.lbStyle = BS_SOLID;
	logBrush.lbColor = RGB(255, 0, 255);

	pDC->SetBkColor(RGB(0, 0, 255));
	pDC->SetBkMode(OPAQUE);

	CPen* newPen = new CPen(PS_DASH, 0, RGB(255, 0, 255)),//new CPen(PS_GEOMETRIC | PS_DASH | PS_JOIN_ROUND | PS_ENDCAP_ROUND, 3, &logBrush),
		* oldPen = pDC->SelectObject(newPen);

	pDC->Rectangle(-250, -250, 250, 250);

	CBrush* newBrush = new CBrush(RGB(255, 165, 0)),
		* oldBrush = pDC->SelectObject(newBrush);

	pDC->Rectangle(125, -83, 250, -250);

	delete newBrush;
	newBrush = new CBrush(RGB(255, 0, 0));
	pDC->SelectObject(newBrush);

	CPoint triangle[] = { CPoint(125, 83), CPoint(125, -83), CPoint(250, -83), CPoint(125, 83) };
	pDC->Polygon(triangle, 4);

	delete newBrush;
	newBrush = new CBrush(RGB(0, 150, 0));
	pDC->SelectObject(newBrush);

	CPoint triangle2[] = { CPoint(125, -83), CPoint(125, -250), CPoint(0, -250), CPoint(125, -83) };
	pDC->Polygon(triangle2, 4);

	delete newBrush;
	newBrush = new CBrush(RGB(175, 0, 175));
	pDC->SelectObject(newBrush);

	CPoint triangle3[] = { CPoint(0, 250), CPoint(250, -83), CPoint(250, 250), CPoint(0, 250) };
	pDC->Polygon(triangle3, 4);

	delete newBrush;
	newBrush = new CBrush(RGB(230, 220, 0));
	pDC->SelectObject(newBrush);

	CPoint triangle4[] = { CPoint(0, -250), CPoint(-250, -250), CPoint(-250, 83), CPoint(0, -250) };
	pDC->Polygon(triangle4, 4);

	delete newBrush;
	newBrush = new CBrush(HS_CROSS, RGB(0, 0, 255));
	pDC->SelectObject(newBrush);

	CPoint triangle5[] = { CPoint(-250, 250), CPoint(0, 250), CPoint(-125, 83), CPoint(-250, 250) };
	pDC->Polygon(triangle5, 4);

	delete newBrush;
	newBrush = new CBrush(RGB(255, 100, 200));
	pDC->SelectObject(newBrush);

	CPoint paralelogram[] = { CPoint(-250, 250), CPoint(-125, 83), CPoint(-125, -83), CPoint(-250, 83), CPoint(-250, 250) };
	pDC->Polygon(paralelogram, 5);

	pDC->SelectObject(oldBrush);
	delete newBrush;

	pDC->SelectObject(oldPen);
	delete newPen;

	pDC->SetMapMode(mapMode);
}


// CLab1Proba1View printing

BOOL CLab1Proba1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CLab1Proba1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CLab1Proba1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CLab1Proba1View diagnostics

#ifdef _DEBUG
void CLab1Proba1View::AssertValid() const
{
	CView::AssertValid();
}

void CLab1Proba1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CLab1Proba1Doc* CLab1Proba1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CLab1Proba1Doc)));
	return (CLab1Proba1Doc*)m_pDocument;
}
#endif //_DEBUG


// CLab1Proba1View message handlers
