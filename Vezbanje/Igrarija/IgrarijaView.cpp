
// IgrarijaView.cpp : implementation of the CIgrarijaView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Igrarija.h"
#endif

#include "IgrarijaDoc.h"
#include "IgrarijaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIgrarijaView

IMPLEMENT_DYNCREATE(CIgrarijaView, CView)

BEGIN_MESSAGE_MAP(CIgrarijaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CIgrarijaView construction/destruction

CIgrarijaView::CIgrarijaView() noexcept
{
	// TODO: add construction code here

}

CIgrarijaView::~CIgrarijaView()
{
}

BOOL CIgrarijaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIgrarijaView drawing
#define _USE_MATH_DEFINES
#include <math.h>

void Rotate(CDC* pDC, double angle, bool isRight = false)
{
	XFORM mat;
	mat.eM11 =
		mat.eM22 = cos(angle);
	mat.eM12 = sin(angle);
	mat.eM21 = -mat.eM12;
	mat.eDx = mat.eDy = 0;

	pDC->ModifyWorldTransform(&mat, isRight ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void Translate(CDC* pDC, double Dx, double Dy, bool isRight = false)
{
	XFORM mat = { 1, 0, 0, 1, Dx, Dy };

	pDC->ModifyWorldTransform(&mat, isRight ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void Scale(CDC* pDC, double sX, double sY, bool isRight = false)
{
	XFORM mat = { sX, 0, 0, sY, 0, 0 };

	pDC->ModifyWorldTransform(&mat, isRight ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CIgrarijaView::OnDraw(CDC* pDC)
{
	/*CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 3, RGB(255, 0, 0)));
	CBrush* oldBrush = pDC->SelectObject(new CBrush(HS_CROSS, RGB(0, 0, 255)));

	pDC->MoveTo(100, 100);
	pDC->SetArcDirection(AD_CLOCKWISE);
	pDC->BeginPath();
	{
		int r = 50;

		pDC->LineTo(300, 100);
		pDC->ArcTo(CRect(300 - r, 100, 300 + r, int(100 + 2 * r + 0.5)), { 300, 100 }, { 300, int(100 + 2 * r + 0.5)});
		pDC->LineTo(100, int(100 + 2 * r - 0.5));
		pDC->ArcTo(CRect(100 + r, int(100 + 2 * r - 0.5), 100 - r, 100), { 100, int(100 + 2 * r - 0.5) }, { 100, 100 });

	}
	pDC->EndPath();

	pDC->StrokeAndFillPath();

	delete pDC->SelectObject(oldBrush);
	delete pDC->SelectObject(oldPen);

	CRgn uni, elps, sqr, clientRgn;
	CRect clientRect;
	elps.CreateEllipticRgn(400, 400, 600, 600);
	sqr.CreateRectRgn(500, 200, 800, 500);
	uni.CreateRectRgn(0, 0, 0, 0);
	uni.CombineRgn(&elps, &sqr, RGN_OR);

	pDC->GetClipBox(&clientRect);
	clientRgn.CreateRectRgnIndirect(clientRect);
	pDC->SelectClipRgn(&uni);

	oldBrush = pDC->SelectObject(new CBrush(RGB(255, 255, 0)));
	oldPen = (CPen*)pDC->SelectStockObject(NULL_PEN);

	pDC->GetClipBox(&clientRect);
	pDC->Rectangle(&clientRect);

	pDC->SelectObject(oldPen);
	delete pDC->SelectObject(oldBrush);
	pDC->SelectClipRgn(&clientRgn);*/

	/*CMetaFileDC metaDC;
	metaDC.CreateEnhanced(pDC, _T("Probicica2.emf"), CRect(0, 0, 15000, 15000), _T("Proba"));

	HENHMETAFILE MF;
	int x = 750, y = 750;
	double step = 0, r;
	metaDC.MoveTo(x, y);

	CPen* newPen = new CPen(PS_SOLID, 3, RGB(255, 255, 0)),
		* oldPen = metaDC.SelectObject(newPen);
	for (double angle = 0; angle <= 20 * M_PI; angle += step)
	{
		r = 180 * angle / (20 * M_PI);
		step = 3 / (r + 1);

		x = (int)(750 + r * cos(angle + step) + 0.5);
		y = (int)(750 - r * sin(angle + step) + 0.5);

		delete newPen;
		newPen = new CPen(PS_SOLID, 3, RGB(200 + (int)x % 56, 200 + (int)angle % 56,2050 + (int)y % 56));
		metaDC.SelectObject(newPen);

		metaDC.LineTo(x, y);
	}
	delete metaDC.SelectObject(oldPen);

	MF = metaDC.CloseEnhanced();
	metaDC.DeleteDC();*/
	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM oldWT;
	pDC->GetWorldTransform(&oldWT);
	pDC->ModifyWorldTransform(nullptr, MWT_IDENTITY);

	pDC->Rectangle(200, 100, 300, 200);

	Rotate(pDC, M_PI / 4);

	CFont f;
	f.CreateFontW(20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, L"Times New Roman");
	pDC->SelectObject(&f);

	pDC->TextOut(100, 100, L"Stefan");

	pDC->Rectangle(200, 100, 300, 200);

	pDC->SetWorldTransform(&oldWT);
	pDC->SetGraphicsMode(oldGM);


	//pDC->SetViewportOrg(oldViewport);
}


// CIgrarijaView printing

BOOL CIgrarijaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIgrarijaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIgrarijaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CIgrarijaView diagnostics

#ifdef _DEBUG
void CIgrarijaView::AssertValid() const
{
	CView::AssertValid();
}

void CIgrarijaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIgrarijaDoc* CIgrarijaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIgrarijaDoc)));
	return (CIgrarijaDoc*)m_pDocument;
}
#endif //_DEBUG


// CIgrarijaView message handlers
