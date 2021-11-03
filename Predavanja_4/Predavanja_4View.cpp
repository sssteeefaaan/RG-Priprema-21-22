
// Predavanja_4View.cpp : implementation of the CPredavanja4View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Predavanja_4.h"
#endif

#include "Predavanja_4Doc.h"
#include "Predavanja_4View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CPredavanja4View

IMPLEMENT_DYNCREATE(CPredavanja4View, CView)

BEGIN_MESSAGE_MAP(CPredavanja4View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CPredavanja4View construction/destruction

CPredavanja4View::CPredavanja4View() noexcept
{
	// TODO: add construction code here

}

CPredavanja4View::~CPredavanja4View()
{
}

BOOL CPredavanja4View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// Algoritmi
void NagibniAlgoritam(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF value)
{
	double dx, dy, m, y, y0;

	dx = x2 - x1;
	dy = y2 - y1;
	m = dy / dx;
	y0 = y1 - m * x1;

	for (int x = x1; x < x2; x++)
	{
		y = m * x + y0;
		pDC->SetPixel(x, int(y + 0.5), value);
	}
}

void NagibniAlgoritamFixed(CDC* pDC, int x1, int y1, int x2, int y2, COLORREF value)
{
	double dx = x2 - x1,
		dy = y2 - y1;

	int start_x = min(x1, x2),
		start_y = min(y1, y2),
		end_x = max(x1, x2),
		end_y = max(y1, y2);


	if (dx == 0 && dy == 0)
	{
		pDC->SetPixel(x1, y1, value);
		pDC->LineTo(50, 50);
	}
	else if (dx == 0)
	{
		for (int y = start_y; y < end_y; y++)
			pDC->SetPixel(x1, y, value);
	}
	else if (dy == 0)
	{
		for (int x = start_x; x < end_x; x++)
			pDC->SetPixel(x, y1, value);
	}
	else {
		double m = dy / dx,
			y0 = y1 - m * x1;

		if (abs(m) < 1)
		{
			for (int x = start_x; x < end_x; x++)
				pDC->SetPixel(x, int(m * x + y0 + 0.5), value);
		}
		else {
			for (int y = start_y; y < end_y; y++)
				pDC->SetPixel(int((y - y0) / m + 0.5), y, value);
		}
	}
}

// CPredavanja4View drawing

void CPredavanja4View::OnDraw(CDC* pDC)
{
	CPredavanja4Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	NagibniAlgoritamFixed(pDC, 100, 600, 200, 100, RGB(255,0,255));
	NagibniAlgoritam(pDC, 150, 600, 250, 100, RGB(255, 0, 0));

	NagibniAlgoritamFixed(pDC, 100, 600, 500, 500, RGB(255, 0, 255));
	NagibniAlgoritam(pDC, 150, 600, 550, 500, RGB(255, 0, 0));

	//NagibniAlgoritamFixed(pDC, 500, 600, 500, 400, RGB(255, 0, 255));
	//NagibniAlgoritamFixed(pDC, 300, 300, 700, 300, RGB(255, 0, 255));

	//pDC->MoveTo(100, 100);
	//pDC->LineTo(200, 200);
}


// CPredavanja4View printing

BOOL CPredavanja4View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPredavanja4View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPredavanja4View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CPredavanja4View diagnostics

#ifdef _DEBUG
void CPredavanja4View::AssertValid() const
{
	CView::AssertValid();
}

void CPredavanja4View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CPredavanja4Doc* CPredavanja4View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPredavanja4Doc)));
	return (CPredavanja4Doc*)m_pDocument;
}
#endif //_DEBUG


// CPredavanja4View message handlers
