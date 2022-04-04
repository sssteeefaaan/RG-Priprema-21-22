
// Maj2021View.cpp : implementation of the CMaj2021View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Maj2021.h"
#endif

#include "Maj2021Doc.h"
#include "Maj2021View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMaj2021View

IMPLEMENT_DYNCREATE(CMaj2021View, CView)

BEGIN_MESSAGE_MAP(CMaj2021View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMaj2021View construction/destruction

CMaj2021View::CMaj2021View() noexcept
{
	// TODO: add construction code here

}

CMaj2021View::~CMaj2021View()
{
}

BOOL CMaj2021View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CMaj2021View drawing

void CMaj2021View::OnDraw(CDC* pDC)
{
	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);
	
	CRect window;
	GetClientRect(&window);
	DrawFigure(pDC, window.Width() / 2.0, window.Height() / 2.0, 50, 25, 100, 20, 50);

	pDC->SetGraphicsMode(oldGM);
}

void CMaj2021View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM transform = { 1, 0, 0, 1, dX, dY };

	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CMaj2021View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM transform{};
	transform.eM11 = transform.eM22 = cos(angle);
	transform.eM21 = -(transform.eM12 = sin(angle));

	pDC->ModifyWorldTransform(&transform, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CMaj2021View::DrawConeBottom(CDC* pDC, float cX, float cY, float a, float b, float h, int n)
{
	double dAlpha = 2.0 * 3.14 / n,
		angle = 0;

	double dColor = 2.0 * 255.0 / n,
		color = 0;

	CPoint* elipse = new CPoint[n];
	CBrush* oldBrush = pDC->GetCurrentBrush();

	for (int i = 0; i < n; i++)
	{
		elipse[i] = { (int)(cX + .5 + a * cos(angle)), (int)(cY + h + b * sin(angle) + .5) };
		angle -= dAlpha;

		if (angle >= -3.14 && i > 0)
		{
			CPoint strip[3] = { elipse[i - 1], { (int)(cX + .5), (int)(cY + .5) }, elipse[i] };
			CBrush brush(RGB((int)(color + .5), (int)(color + .5), (int)(color + .5)));
			pDC->SelectObject(&brush);
			pDC->Polygon(strip, 3);
			pDC->SelectObject(oldBrush)->DeleteObject();
			color += dColor;
		}
	}

	CBrush brush(RGB(255, 255, 255));
	pDC->SelectObject(&brush);
	pDC->Polygon(elipse, n);
	pDC->SelectObject(oldBrush)->DeleteObject();
	delete[] elipse;
}
void CMaj2021View::DrawConeTop(CDC* pDC, float cX, float cY, float a, float b, float h, int n)
{
	double dAlpha = 2.0 * 3.14 / n,
		angle = 0;

	double dColor = 2.0 * 255.0 / n,
		color = 0;

	CPoint* elipse = new CPoint[n];
	CBrush* oldBrush = pDC->GetCurrentBrush();

	for (int i = 0; i <= n >> 1; i++)
	{
		elipse[i] = { (int)(cX + .5 + a * cos(angle)), (int)(cY + h + b * sin(angle) + .5) };
		angle += dAlpha;

		if (angle >= -3.14 && i > 0)
		{
			CPoint strip[3] = { elipse[i - 1], { (int)(cX + .5), (int)(cY + .5) }, elipse[i] };
			CBrush brush(RGB((int)(color + .5), (int)(color + .5), (int)(color + .5)));
			pDC->SelectObject(&brush);
			pDC->Polygon(strip, 3);
			pDC->SelectObject(oldBrush)->DeleteObject();
			color += dColor;
		}
	}
}
void CMaj2021View::DrawCylinder(CDC* pDC, float cX, float cY, float a, float b, float h, int n)
{
	double dAlpha = 2.0 * 3.14 / n,
		angle = 0;

	double dColor = 2.0 * 255.0 / n,
		color = 0;

	CPoint* elipse = new CPoint[n];
	CBrush* oldBrush = pDC->GetCurrentBrush();

	for (int i = 0; i < n; i++)
	{
		elipse[i] = { (int)(cX + .5 + a * cos(angle)), (int)(cY + h + b * sin(angle) + .5) };
		angle -= dAlpha;

		if (angle >= -3.14 && i > 0)
		{
			CPoint strip[4] = { elipse[i - 1], { elipse[i - 1].x, (int)(elipse[i - 1].y - h) }, { elipse[i].x, (int)(elipse[i].y - h) } , elipse[i] };
			CBrush brush(RGB((int)(color + .5), (int)(color + .5), (int)(color + .5)));
			pDC->SelectObject(&brush);
			pDC->Polygon(strip, 4);
			pDC->SelectObject(oldBrush)->DeleteObject();
			color += dColor;
		}
	}

	CBrush brush(RGB(255, 255, 255));
	pDC->SelectObject(&brush);
	pDC->Polygon(elipse, n);
	pDC->SelectObject(oldBrush)->DeleteObject();
	delete[] elipse;
}
void CMaj2021View::DrawFigure(CDC* pDC, float cX, float cY, float a, float b, float h, int n, float r)
{
	XFORM state{};
	pDC->GetWorldTransform(&state);

	Translate(pDC, cX, cY, false);
	Rotate(pDC, -3.14 / 4.0, false);

	// Push

	Translate(pDC, 0, r, false);
	DrawCylinder(pDC, 0, 0, a, b, h, n);

	Translate(pDC, 0, -r, false); // Pop

	Rotate(pDC, -3.14 / 2.0, false);
	//Push
	Translate(pDC, 0, r, false);
	DrawConeBottom(pDC, 0, 0, a, b, h, n);

	Translate(pDC, 0, -r, false); // Pop

	Rotate(pDC, -3.14 / 2.0, false);
	// Push
	Translate(pDC, 0, r, false);
	DrawConeTop(pDC, 0, 0, a, b, h, n);

	Translate(pDC, 0, -r, false); // Pop

	Rotate(pDC, -3.14 / 2.0, false);
	Translate(pDC, 0, r, false);
	DrawConeBottom(pDC, 0, 0, a, b, h, n);

	pDC->SetWorldTransform(&state);
}


// CMaj2021View printing

BOOL CMaj2021View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CMaj2021View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CMaj2021View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CMaj2021View diagnostics

#ifdef _DEBUG
void CMaj2021View::AssertValid() const
{
	CView::AssertValid();
}

void CMaj2021View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMaj2021Doc* CMaj2021View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMaj2021Doc)));
	return (CMaj2021Doc*)m_pDocument;
}
#endif //_DEBUG


// CMaj2021View message handlers
