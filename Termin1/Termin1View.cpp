
// Termin1View.cpp : implementation of the CTermin1View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Termin1.h"
#endif

#include "Termin1Doc.h"
#include "Termin1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTermin1View

IMPLEMENT_DYNCREATE(CTermin1View, CView)

BEGIN_MESSAGE_MAP(CTermin1View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CTermin1View::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CTermin1View construction/destruction

CTermin1View::CTermin1View() noexcept
{
	// TODO: add construction code here

}

CTermin1View::~CTermin1View()
{
}

BOOL CTermin1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CTermin1View drawing
#define RGB(r, g, b) ((DWORD) (((DWORD)(b) << 16) | ((WORD)(g) << 8) | (BYTE) (r)))
#define RGBInverse(color) ((DWORD) color ^ ((1 << 24) - 1))
void CTermin1View::OnDraw(CDC* pDC)
{
	CTermin1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	srand(time(NULL));
	COLORREF boja = RGB(0, 0, 255);
	COLORREF tempTextColor = pDC->SetTextColor(boja);
	COLORREF tempBkColor = pDC->SetBkColor(RGBInverse(boja));
	int tempBkMode = pDC->SetBkMode(OPAQUE);
	// int tempBkMode = pDC->SetBkMode(TRANSPARENT);

	CRect rect;
	GetClientRect(&rect);
	int tempMapMode = pDC->SetMapMode(MM_ANISOTROPIC);
	CSize tempWindowExt = pDC->SetWindowExt(100, -100);
	// (0, 0) => koordinate levog gornjeg ugla
	// (x, y) => koordinate desnog donjeg ugla

	CSize tempViewportExt = pDC->SetViewportExt(rect.Width(), rect.Height());
	// ukoliko se znak x/y koordinate ne poklope u window i viewport extent-u, onda se menja smer rasta koordinata
	// default je x raste na desno, y raste na dole

	CSize tempWindowOrg = pDC->SetWindowOrg(-50, 50);
	// zavisi od znaka, gleda se na koje logicke koordinate treba da se popne levi gornji ugao ekrana
	// da bi se koordinatni pocetak našao na sredini
	
	// CSize tempViewportOrg = pDC->SetViewportOrg(rect.Width() / 2, rect.Height() / 2);
	// uvek isto, tj. ne zavisi od znaka

	// pDC->Rectangle(-20, 20, 20, -20);
	// pDC->Ellipse(-10, 10, 10, -10);

	CPen* newPen = new CPen(PS_SOLID, 1, RGB(0, 200, 0)),
		*oldPen = pDC->SelectObject(newPen);

	CBrush* newBrush = new CBrush(RGB(200, 0, 0)),
		*oldBrush = pDC->SelectObject(newBrush);

	pDC->Ellipse(-22, 22, 22, -22);

	newBrush->DeleteObject();
	newPen->DeleteObject();

	newBrush = new CBrush(RGB(0, 0, 200));
	newPen = new CPen(PS_SOLID, 1, RGB(120, 120, 0));

	pDC->SelectObject(newBrush);
	pDC->SelectObject(newPen);

	pDC->Ellipse(-18, 18, 18, -18);

	newBrush->DeleteObject();
	newPen->DeleteObject();

	pDC->TextOutW(-5, 4, (const CString)"Racunarska");
	pDC->TextOutW(-3, 2, (const CString)"Grafika");

	CPoint points[] = { CPoint(-13, -15), CPoint(0, 20), CPoint(13, -15), CPoint(-18, 8), CPoint(18, 8) };

	for (int i = 0; i < 5; i++)
	{
		COLORREF tempCol = RGB(rand() % 200 + 10*i, rand() % 200 + 10 * i, rand() % 200 + 10*i);
		newBrush = new CBrush(tempCol);
		newPen = new CPen(PS_SOLID, 1, RGBInverse(tempCol));

		pDC->SelectObject(newBrush);
		pDC->SelectObject(newPen);

		pDC->Ellipse(points[i].x - 2, points[i].y + 2, points[i].x + 2, points[i].y - 2);

		newBrush->DeleteObject();
		newPen->DeleteObject();
	}

	newBrush = new CBrush(RGB(0, 200, 0));
	newPen = new CPen(PS_SOLID, 1, RGB(200, 0, 0));

	pDC->SelectObject(newBrush);
	pDC->SelectObject(newPen);

	int tempPolyFillMode = pDC->SetPolyFillMode(ALTERNATE);
	pDC->Polygon(points, 5);

	newBrush->DeleteObject();
	newPen->DeleteObject();

	// Restore
	pDC->SetPolyFillMode(tempPolyFillMode);

	pDC->SetWindowOrg(tempWindowOrg.cx, tempWindowOrg.cy);
	pDC->SetViewportExt(tempViewportExt);
	pDC->SetWindowExt(tempWindowExt.cx, tempWindowExt.cy);
	pDC->SetMapMode(tempMapMode);

	pDC->SetBkMode(tempBkMode);
	pDC->SetBkColor(tempBkColor);
	pDC->SetTextColor(tempTextColor);

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);
}


// CTermin1View printing


void CTermin1View::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CTermin1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CTermin1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CTermin1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CTermin1View::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CTermin1View::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CTermin1View diagnostics

#ifdef _DEBUG
void CTermin1View::AssertValid() const
{
	CView::AssertValid();
}

void CTermin1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CTermin1Doc* CTermin1View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CTermin1Doc)));
	return (CTermin1Doc*)m_pDocument;
}
#endif //_DEBUG


// CTermin1View message handlers
