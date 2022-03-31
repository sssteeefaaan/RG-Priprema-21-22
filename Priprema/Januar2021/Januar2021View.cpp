
// Januar2021View.cpp : implementation of the CJanuar2021View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Januar2021.h"
#endif

#include "Januar2021Doc.h"
#include "Januar2021View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJanuar2021View

IMPLEMENT_DYNCREATE(CJanuar2021View, CView)

BEGIN_MESSAGE_MAP(CJanuar2021View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()

// CJanuar2021View construction/destruction

CJanuar2021View::CJanuar2021View() noexcept
{
	m_backdrop.Load(L"Backdrop.jpg");
	m_body.Load(L"Body.png");
	m_leg1.Load(L"Leg1.png");
	m_leg2.Load(L"Leg2.png");
	m_leg3.Load(L"Leg3.png");

	m_step = 0;
	m_lleg1 = 0;
	m_lleg2 = 4;
	m_rleg1 = 2;
	m_rleg2 = 6;
}

CJanuar2021View::~CJanuar2021View()
{
}

void CJanuar2021View::DrawTransparent(CDC* pDC, DImage* pImage, COLORREF color)
{
	CRect rect(0, 0, pImage->Width(), pImage->Height());
	int w = rect.Width(), h = rect.Height();

	CDC* srcDC = new CDC(), *dstDC = new CDC();
	srcDC->CreateCompatibleDC(pDC);
	dstDC->CreateCompatibleDC(pDC);

	CBitmap* src = new CBitmap(), * dst = new CBitmap();
	src->CreateCompatibleBitmap(pDC, w, h);
	dst->CreateBitmap(w, h, 1, 1, NULL);

	srcDC->SelectObject(src);
	dstDC->SelectObject(dst);

	pImage->Draw(srcDC, rect, rect);

	srcDC->SetBkColor(color);
	dstDC->BitBlt(0, 0, w, h, srcDC, 0, 0, SRCCOPY);

	srcDC->SetBkColor(RGB(0, 0, 0));
	srcDC->SetTextColor(RGB(255, 255, 255));
	srcDC->BitBlt(0, 0, w, h, dstDC, 0, 0, SRCAND);

	pDC->BitBlt(0, 0, w, h, dstDC, 0, 0, SRCAND);
	pDC->BitBlt(0, 0, w, h, srcDC, 0, 0, SRCPAINT);

	delete(srcDC);
	delete(dstDC);
	delete(src);
	delete(dst);
}

void CJanuar2021View::Translate(CDC* pDC, float dX, float dY, bool rightMultiply)
{
	XFORM t = { 1, 0, 0, 1, dX, dY };
	pDC->ModifyWorldTransform(&t, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CJanuar2021View::Rotate(CDC* pDC, float angle, bool rightMultiply)
{
	XFORM t{};
	t.eDx = t.eDy = 0;
	t.eM11 = t.eM22 = cos(angle);
	t.eM21 = -(t.eM12 = sin(angle));

	pDC->ModifyWorldTransform(&t, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CJanuar2021View::Scale(CDC* pDC, float sX, float sY, bool rightMultiply)
{
	XFORM t = { sX, 0, 0, sY, 0, 0 };
	pDC->ModifyWorldTransform(&t, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CJanuar2021View::DrawLeg(CDC* pDC, double alpha, double dx, double dy)
{
	int x = 20, y = 30;

	XFORM t{};
	pDC->GetWorldTransform(&t);
	{
		Translate(pDC, dx - x, dy - y, false);
		Rotate(pDC, alpha, false);
		Translate(pDC, -x, -y, false);
		DrawTransparent(pDC, &m_leg1, RGB(255, 255, 255));

		Translate(pDC, x, m_leg1.Height() - y, false);
		Rotate(pDC, -alpha, false);
		Translate(pDC, -x, -y, false);
		DrawTransparent(pDC, &m_leg2, RGB(255, 255, 255));

		Translate(pDC, (double)(m_leg2.Width() - m_leg3.Width()) / 2.0, m_leg2.Height(), false);
		DrawTransparent(pDC, &m_leg3, RGB(255, 255, 255));
	}
	pDC->SetWorldTransform(&t);
}

void CJanuar2021View::DrawScene(CDC* pDC, double scale, int step)
{
	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);

	XFORM t{};
	pDC->GetWorldTransform(&t);
	{
		CRect rect, img(0, 0, m_backdrop.Width(), m_backdrop.Height());
		GetClientRect(&rect);
		m_backdrop.Draw(pDC, img, rect);

		Scale(pDC, scale, scale, false);
		Translate(pDC, 100 + m_step * step, rect.Height() - (m_body.Height() - 300) * scale, false);
		DrawTransparent(pDC, &m_body, RGB(255, 255, 255));

		int x1 = 90, x2 = 300, y = m_body.Height(),
			v[] = { -20, -10, 0, 10, 20, 10, 0, -10 };

		DrawLeg(pDC, v[m_lleg1] * 3.14 / 180, x1, y);
		DrawLeg(pDC, v[m_lleg2] * 3.14 / 180, x1, y);
		DrawLeg(pDC, v[m_rleg1] * 3.14 / 180, x2, y);
		DrawLeg(pDC, v[m_rleg2] * 3.14 / 180, x2, y);
	}
	pDC->SetWorldTransform(&t);

	pDC->SetGraphicsMode(oldGM);
}

BOOL CJanuar2021View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CJanuar2021View drawing

void CJanuar2021View::OnDraw(CDC* pDC)
{
	CRect client;
	GetClientRect(&client);

	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, client.Width(), client.Height());

	bm = memDC->SelectObject(bm);
	memDC->Rectangle(client);

	DrawScene(memDC, .5, 20);
	pDC->BitBlt(0, 0, client.Width(), client.Height(), memDC, 0, 0, SRCCOPY);

	delete(memDC->SelectObject(bm));
	delete(memDC);
}


// CJanuar2021View printing

BOOL CJanuar2021View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CJanuar2021View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CJanuar2021View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CJanuar2021View diagnostics

#ifdef _DEBUG
void CJanuar2021View::AssertValid() const
{
	CView::AssertValid();
}

void CJanuar2021View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CJanuar2021Doc* CJanuar2021View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CJanuar2021Doc)));
	return (CJanuar2021Doc*)m_pDocument;
}
#endif //_DEBUG


// CJanuar2021View message handlers


void CJanuar2021View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
	case('D'):
		m_step += 1;
		CalcOffsets(1);
		break;
	case('A'):
		m_step -= 1;
		CalcOffsets(-1);
		break;
	default:
		break;
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	Invalidate();
}

void CJanuar2021View::CalcOffsets(int offset)
{
	m_lleg1 += offset;
	m_lleg2 += offset;
	m_rleg1 += offset;
	m_rleg2 += offset;

	if (m_lleg1 < 0)
		m_lleg1 = 7;
	else if (m_lleg1 > 7)
		m_lleg1 = 0;

	if (m_lleg2 < 0)
		m_lleg2 = 7;
	else if (m_lleg2 > 7)
		m_lleg2 = 0;

	if (m_rleg1 < 0)
		m_rleg1 = 7;
	else if (m_rleg1 > 7)
		m_rleg1 = 0;

	if (m_rleg2 < 0)
		m_rleg2 = 7;
	else if (m_rleg2 > 7)
		m_rleg2 = 0;
}

BOOL CJanuar2021View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}
