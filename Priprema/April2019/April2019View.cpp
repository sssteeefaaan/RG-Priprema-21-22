
// April2019View.cpp : implementation of the CApril2019View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "April2019.h"
#endif

#include "April2019Doc.h"
#include "April2019View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CApril2019View

IMPLEMENT_DYNCREATE(CApril2019View, CView)

BEGIN_MESSAGE_MAP(CApril2019View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CApril2019View construction/destruction

CApril2019View::CApril2019View() noexcept
{
	// TODO: add construction code here
	m_step = 10;
	m_mipmaps = nullptr;
	m_alpha = 0;
}

CApril2019View::~CApril2019View()
{
	if (m_mipmaps)
	{
		delete(m_mipmaps);
		m_mipmaps = nullptr;
	}
}

BOOL CApril2019View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CApril2019View drawing

void CApril2019View::OnDraw(CDC* pDC)
{
	CRect c;
	GetClientRect(&c);

	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);
	XFORM t{};
	pDC->GetWorldTransform(&t);

	Translate(pDC, 0, 200, false);
	DrawWP(pDC, 100, 75, 20, c.Width(), 3.14 / 8 + m_alpha * 3.14 / 180, m_step);

	pDC->SetWorldTransform(&t);
	pDC->SetGraphicsMode(oldGM);

	CMipMap(L"unnamed.png");

	DrawMipMap(pDC, 900, 50, 128);
}

void CApril2019View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM t = { 1, 0, 0, 1, dX, dY };
	pDC->ModifyWorldTransform(&t, rightMultiply ? MWT_RIGHTMULTIPLY: MWT_LEFTMULTIPLY);
}

void CApril2019View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM t{};
	t.eM11 = t.eM22 = cos(angle);
	t.eM21 = -(t.eM12 = sin(angle));

	pDC->ModifyWorldTransform(&t, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CApril2019View::DrawWheel(CDC* pDC, double r1, double r2, double w)
{
	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(125, 125, 125)));
	pDC->Ellipse(-r1, -r1, r1, r1);
	oldBrush = pDC->SelectObject(oldBrush);

	pDC->Ellipse(-r2, -r2, r2, r2);
	oldBrush = pDC->SelectObject(oldBrush);

	XFORM t{};
	pDC->GetWorldTransform(&t);
	for (int i = 0; i < 3; i++)
	{
		Rotate(pDC, i * 3.14 / 4, false);
		pDC->Rectangle(-(w / 2 + .5), -(r2 + .5), w / 2 + .5, r2 + .5);
	}
	pDC->SetWorldTransform(&t);

	delete(pDC->SelectObject(oldBrush));
}

void CApril2019View::DrawWP(CDC* pDC, double r1, double r2, double w, double L, double alpha, double d)
{
	double h = L * tan(alpha);
	CPoint p[] = { CPoint(0, 0), CPoint(0, h), CPoint(L, h) };

	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(32, 0, 206)));
	pDC->Polygon(p, 3);
	delete(pDC->SelectObject(oldBrush));

	XFORM t{};
	pDC->GetWorldTransform(&t);

	Translate(pDC, 0, -r1, false);
	Rotate(pDC, alpha, false);
	Translate(pDC, d, 0, false);
	Rotate(pDC, d / r1, false);
	DrawWheel(pDC, r1, r2, w);

	pDC->SetWorldTransform(&t);
}

void CApril2019View::CMipMap(CString name)
{
	DImage img;
	img.Load(name);
	img.Flip();

	CDC* memDC = new CDC(), *pDC = GetDC();
	memDC->CreateCompatibleDC(pDC);
	
	if (m_mipmaps)
	{
		delete(m_mipmaps);
		m_mipmaps = nullptr;
	}

	m_mipmaps = new CBitmap();
	m_mipmaps->CreateCompatibleBitmap(pDC, img.Width() * 2, img.Height());
	ReleaseDC(pDC);

	CBitmap* oldBM = memDC->SelectObject(m_mipmaps);
	int w = img.Width(),
		h = img.Height(),
		w0 = 0,
		h0 = 0;

	while (w > 0 && h > 0)
	{
		img.Draw(memDC, CRect(0, 0, img.Width(), img.Height()), CRect(w0, img.Height() - h, w0 + w, img.Height()));
		w0 += w;
		h0 += h;
		w >>= 1;
		h >>= 1;
	}

	memDC->SelectObject(oldBM);
	delete(memDC);

	DImage img2(*m_mipmaps);
	img2.Save(L"Proba.jpg");
}

void CApril2019View::DrawMipMap(CDC* pDC, int x, int y, int size)
{
	BITMAP bm{};
	m_mipmaps->GetBitmap(&bm);
	CSize c(bm.bmWidth, bm.bmHeight), offset(0, 0);

	while ((c.cx - (c.cx >> 1)) > size && c.cy > size) {
		c.cx >>= 1;
		c.cy >>= 1;

		offset.cx += c.cx;
		offset.cy = bm.bmHeight - c.cy;
	}

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);
	CBitmap* oldBM = memDC->SelectObject(m_mipmaps);

	pDC->BitBlt(x, y, size, size, memDC, offset.cx, offset.cy, SRCCOPY);

	memDC->SelectObject(oldBM);
	delete(memDC);
}



// CApril2019View printing

BOOL CApril2019View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CApril2019View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CApril2019View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CApril2019View diagnostics

#ifdef _DEBUG
void CApril2019View::AssertValid() const
{
	CView::AssertValid();
}

void CApril2019View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApril2019Doc* CApril2019View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApril2019Doc)));
	return (CApril2019Doc*)m_pDocument;
}
#endif //_DEBUG


// CApril2019View message handlers


void CApril2019View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case('A'):
		m_step -= 5;
		break;
	case('D'):
		m_step += 5;
		break;
	case('W'):
		m_alpha += 5;
		break;
	case('S'):
		m_alpha -= 5;
		break;
	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	Invalidate();
}
