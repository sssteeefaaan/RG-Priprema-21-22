
// April2021View.cpp : implementation of the CApril2021View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "April2021.h"
#endif

#include "April2021Doc.h"
#include "April2021View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "DImage.h"


// CApril2021View

IMPLEMENT_DYNCREATE(CApril2021View, CView)

BEGIN_MESSAGE_MAP(CApril2021View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CApril2021View construction/destruction

CApril2021View::CApril2021View() noexcept
{
	// TODO: add construction code here

}

CApril2021View::~CApril2021View()
{
}

BOOL CApril2021View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CApril2021View drawing

void CApril2021View::Translate(CDC* pDC, int dX, int dY, bool rightMultiply)
{
	XFORM transformation = { 1, 0, 0, 1, dX, dY };

	pDC->ModifyWorldTransform(&transformation, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}
void CApril2021View::Rotate(CDC* pDC, double angle, bool rightMultiply)
{
	XFORM transformation{};
	transformation.eM11 = transformation.eM22 = cos(angle);
	transformation.eM12 = -(transformation.eM21 = sin(angle));

	pDC->ModifyWorldTransform(&transformation, rightMultiply ? MWT_RIGHTMULTIPLY : MWT_LEFTMULTIPLY);
}

void CApril2021View::OnDraw(CDC* pDC)
{
	int oldGM = pDC->SetGraphicsMode(GM_ADVANCED);

	CRect aRect[3] = { CRect(0, 0, 60, 60), CRect(0, 0, 80, 80), CRect(0, 0, 70, 70) };
	int anArcs[3] = { 1, 2, 3 };
	COLORREF aClrFill[3] = { RGB(200, 0, 0), RGB(200, 100, 0), RGB(200, 0, 200) },
		aClrLine[3] = { RGB(100, 0, 0), RGB(100, 50, 0), RGB(100, 0, 100) };
	float aRot[3] = { 3.14 / 4, 3.14 / 6, 3.14 / 8 };
	CString aStr[3] = { L"Ružičica", L"Laličica", L"Ljubičica" };
	CPoint aPts[3] = { { 300, 100 }, { 500, 400 }, { 1000, 300 } };

	DrawFlowers(pDC, aRect, anArcs, aClrFill, aClrLine, aRot, aStr, aPts, 3);

	CRect window;
	GetClientRect(&window);
	SaveDC(pDC, window, window);

	pDC->SetGraphicsMode(oldGM);
}

void CApril2021View::DrawPetal(CDC* pDC, CRect rect, int nArcs, COLORREF clrFill, COLORREF clrLine)
{
	double R = rect.Width() / (double)nArcs;
	CRect begin((int)(rect.Width() / 2.0 - R + .5), (int)(- R / 2.0 - rect.Height()), rect.Width() / 2.0 + 0.5, (int)(R / 2.0 - rect.Height()));
	CPoint start = { begin.right, -rect.Height() },
		end = { begin.left, -rect.Height() };

	pDC->BeginPath();
	{
		pDC->MoveTo(0, 0);
		pDC->LineTo(rect.Width() / 2.0 + .5, - rect.Height());
		for (int i = 0; i < nArcs; i++)
		{
			pDC->ArcTo(begin, start, end);
			begin.right = begin.left;
			begin.left -= (R + .5);
			start.x = begin.right;
			end.x = begin.left;
		}
		pDC->LineTo(0, 0);
	}
	pDC->EndPath();

	CPen* oldPen = pDC->SelectObject(new CPen(PS_SOLID, 1, clrLine));
	CBrush* oldBrush = pDC->SelectObject(new CBrush(clrFill));

	pDC->StrokeAndFillPath();

	delete(pDC->SelectObject(oldBrush));
	delete(pDC->SelectObject(oldPen));
}
void CApril2021View::DrawFlower(CDC* pDC, CRect rect, int nArcs, COLORREF clrFill, COLORREF clrLine, float dRot, CString str)
{
	XFORM state{};
	pDC->GetWorldTransform(&state);

	Rotate(pDC, dRot, false);

	for (int i = 0; i < 4; i++)
	{
		DrawPetal(pDC, rect, nArcs, clrFill, clrLine);
		Rotate(pDC, 3.14 / 2.0, false);
	}

	CBrush* oldBrush = pDC->SelectObject(new CBrush(RGB(200, 200, 0)));

	int R = (double) rect.Height() / 4 + .5;
	//int R = rect.Width() / (2.0 * nArcs) + .5;
	pDC->Ellipse(-R, -R, R, R);

	delete(pDC->SelectObject(oldBrush));

	pDC->SetWorldTransform(&state);

	int oldTA = pDC->SetTextAlign(TA_CENTER | TA_TOP | TA_NOUPDATECP),
		oldBkM = pDC->SetBkMode(TRANSPARENT);

	double r = 1.5 * rect.Height(),
		arcLength = 3.14 / 2 * r,
		dAlpha = (3.14 / 2.0) / (str.GetLength() - 1),
		angle = 135 * 3.14 / 180;

	LOGFONT font{};
	CSize textSize = pDC->GetTextExtent(str);
	pDC->GetCurrentFont()->GetLogFont(&font);
	font.lfHeight = (double)textSize.cy / textSize.cx * arcLength + .5;
	font.lfWidth = arcLength / str.GetLength() + 0.5;
	font.lfPitchAndFamily = FIXED_PITCH | FF_ROMAN;
	wcscpy_s(font.lfFaceName, CString("Times New Roman"));

	for (int i = 0; i < str.GetLength(); i++)
	{
		double x = r * cos(angle),
			y = r * sin(angle);
		font.lfOrientation = (90.5 - (angle * 180 / 3.14)) * 10;

		CFont newFont;
		newFont.CreateFontIndirect(&font);
		CFont *oldFont = pDC->SelectObject(&newFont);

		pDC->TextOutW(x + .5, y + .5, CString(str.GetAt(i)));

		pDC->SelectObject(oldFont);
		newFont.DeleteObject();
		angle -= dAlpha;
	}

	pDC->SetBkMode(oldBkM);
	pDC->SetTextAlign(oldTA);
}
void CApril2021View::DrawFlowers(CDC* pDC, CRect* aRect, int* anArcs, COLORREF* aClrFill, COLORREF* aClrLine, float* aRot, CString* aStr, CPoint* aPts, int flowerNumber)
{
	XFORM state{};
	pDC->GetWorldTransform(&state);

	int x = 0, y = 0;

	for (int i = 0; i < flowerNumber; i++)
	{
		Translate(pDC, aPts[i].x - x, aPts[i].y - y, false);
		DrawFlower(pDC, aRect[i], anArcs[i], aClrFill[i], aClrLine[i], aRot[i], aStr[i]);
		x = aPts[i].x;
		y = aPts[i].y;
	}

	pDC->SetWorldTransform(&state);
}
void CApril2021View::SaveDC(CDC* pDC, CRect reDC, CRect rcBmp)
{
	CDC* memDC = new CDC();
	memDC->CreateCompatibleDC(pDC);

	CBitmap* bm = new CBitmap();
	bm->CreateCompatibleBitmap(pDC, rcBmp.Width(), rcBmp.Height());
	CBitmap* oldBM = memDC->SelectObject(bm);

	memDC->StretchBlt(rcBmp.left, rcBmp.top, rcBmp.Width(), rcBmp.Height(), pDC, reDC.left, reDC.top, reDC.Width(), reDC.Height(), SRCCOPY);

	DImage img(*bm);
	img.Save(CString("screenshot.png"));

	delete(memDC->SelectObject(oldBM));
	delete(memDC);
}


// CApril2021View printing

BOOL CApril2021View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CApril2021View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CApril2021View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CApril2021View diagnostics

#ifdef _DEBUG
void CApril2021View::AssertValid() const
{
	CView::AssertValid();
}

void CApril2021View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CApril2021Doc* CApril2021View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CApril2021Doc)));
	return (CApril2021Doc*)m_pDocument;
}
#endif //_DEBUG


// CApril2021View message handlers
