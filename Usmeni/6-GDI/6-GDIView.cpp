
// 6-GDIView.cpp : implementation of the CMy6GDIView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "6-GDI.h"
#endif

#include "6-GDIDoc.h"
#include "6-GDIView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy6GDIView

IMPLEMENT_DYNCREATE(CMy6GDIView, CView)

BEGIN_MESSAGE_MAP(CMy6GDIView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMy6GDIView construction/destruction

CMy6GDIView::CMy6GDIView() noexcept
{
	// TODO: add construction code here

}

CMy6GDIView::~CMy6GDIView()
{
}

BOOL CMy6GDIView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMy6GDIView drawing

void CMy6GDIView::OnDraw(CDC* pDC)
{
	CRect c;
	GetClientRect(&c);

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 5, RGB(0, 0, 0)));
	pDC->Ellipse(100, 100, 200, 200);
	Boundry_Defined_Fill_8_Pixel(pDC, 150, 150, RGB(0, 0, 0), RGB(200, 100, 50));

	delete(pDC->SelectObject(oldPen));
}

void CMy6GDIView::Interior_Defined_Fill_4_Pixel(CDC* pDC, int x, int y, COLORREF old_value, COLORREF new_value)
{
	if (pDC->GetPixel(x, y) == old_value)
	{
		pDC->SetPixel(x, y, new_value);
		Interior_Defined_Fill_4_Pixel(pDC, x, y + 1, old_value, new_value);
		Interior_Defined_Fill_4_Pixel(pDC, x, y - 1, old_value, new_value);
		Interior_Defined_Fill_4_Pixel(pDC, x + 1, y, old_value, new_value);
		Interior_Defined_Fill_4_Pixel(pDC, x - 1, y, old_value, new_value);
	}
}

void CMy6GDIView::Interior_Defined_Fill_8_Pixel(CDC* pDC, int x, int y, COLORREF old_value, COLORREF new_value)
{
	if (pDC->GetPixel(x, y) == old_value)
	{
		pDC->SetPixel(x, y, new_value);
		Interior_Defined_Fill_8_Pixel(pDC, x, y + 1, old_value, new_value);
		Interior_Defined_Fill_8_Pixel(pDC, x, y - 1, old_value, new_value);
		Interior_Defined_Fill_8_Pixel(pDC, x + 1, y, old_value, new_value);
		Interior_Defined_Fill_8_Pixel(pDC, x - 1, y, old_value, new_value);

		Interior_Defined_Fill_8_Pixel(pDC, x + 1, y + 1, old_value, new_value);
		Interior_Defined_Fill_8_Pixel(pDC, x + 1, y - 1, old_value, new_value);
		Interior_Defined_Fill_8_Pixel(pDC, x - 1, y + 1, old_value, new_value);
		Interior_Defined_Fill_8_Pixel(pDC, x - 1, y - 1, old_value, new_value);
	}
}

void CMy6GDIView::Boundry_Defined_Fill_4_Pixel(CDC* pDC, int x, int y, COLORREF boundry_value, COLORREF new_value)
{
	COLORREF old_value;
	if ((old_value = pDC->GetPixel(x, y)) != boundry_value && old_value != new_value)
	{
		pDC->SetPixel(x, y, new_value);
		Boundry_Defined_Fill_4_Pixel(pDC, x, y + 1, boundry_value, new_value);
		Boundry_Defined_Fill_4_Pixel(pDC, x, y - 1, boundry_value, new_value);
		Boundry_Defined_Fill_4_Pixel(pDC, x + 1, y, boundry_value, new_value);
		Boundry_Defined_Fill_4_Pixel(pDC, x - 1, y, boundry_value, new_value);
	}
}

void CMy6GDIView::Boundry_Defined_Fill_8_Pixel(CDC* pDC, int x, int y, COLORREF boundry_value, COLORREF new_value)
{
	COLORREF old_value;
	if ((old_value = pDC->GetPixel(x, y)) != boundry_value && old_value != new_value)
	{
		pDC->SetPixel(x, y, new_value);
		Boundry_Defined_Fill_8_Pixel(pDC, x, y + 1, boundry_value, new_value);
		Boundry_Defined_Fill_8_Pixel(pDC, x, y - 1, boundry_value, new_value);
		Boundry_Defined_Fill_8_Pixel(pDC, x + 1, y, boundry_value, new_value);
		Boundry_Defined_Fill_8_Pixel(pDC, x - 1, y, boundry_value, new_value);

		Boundry_Defined_Fill_8_Pixel(pDC, x + 1, y + 1, boundry_value, new_value);
		Boundry_Defined_Fill_8_Pixel(pDC, x + 1, y - 1, boundry_value, new_value);
		Boundry_Defined_Fill_8_Pixel(pDC, x - 1, y + 1, boundry_value, new_value);
		Boundry_Defined_Fill_8_Pixel(pDC, x - 1, y - 1, boundry_value, new_value);
	}
}


// CMy6GDIView printing

BOOL CMy6GDIView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMy6GDIView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMy6GDIView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMy6GDIView diagnostics

#ifdef _DEBUG
void CMy6GDIView::AssertValid() const
{
	CView::AssertValid();
}

void CMy6GDIView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMy6GDIDoc* CMy6GDIView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMy6GDIDoc)));
	return (CMy6GDIDoc*)m_pDocument;
}
#endif //_DEBUG


// CMy6GDIView message handlers
