
// IND_16995View.cpp : implementation of the CIND16995View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "IND_16995.h"
#endif

#include "IND_16995Doc.h"
#include "IND_16995View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CIND16995View

IMPLEMENT_DYNCREATE(CIND16995View, CView)

BEGIN_MESSAGE_MAP(CIND16995View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// CIND16995View construction/destruction

CIND16995View::CIND16995View() noexcept
{
	this->windowSize.SetRect({ 0,0 }, { 500, 500 });
	this->gridCount = 20;
	this->gridSize = int(500 / this->gridCount + 0.5);
	this->backgroundColor = RGB(200, 200, 200);
	this->penColor = RGB(0, 0, 255);

	this->largeTriangle1 = new RightTriangle({ 7, 13 }, 12, gridSize, 6, penColor, RGB(180, 0, 220), 135);
	this->largeTriangle2 = new RightTriangle({ 7, 13 }, 12, gridSize, 4, penColor, RGB(255, 255, 0), -45);
	this->mediumTriangle = new RightTriangle({ 7, 7 }, 6 * M_SQRT2, gridSize, 8, penColor, RGB(255, 0, 0), 180);
	this->smallTriangle1 = new RightTriangle({ 16, 4 }, 6, gridSize, 5, penColor, RGB(255, 150, 0), -135);
	this->smallTriangle2 = new RightTriangle({ 16, 16 }, 6, gridSize, 7, penColor, RGB(0, 200, 0), 135);
	this->square = new Square({ 16, 10 }, 6, gridSize, penColor, RGB(0, 0, 255), 45, HS_FDIAGONAL);
	this->parallelogram = new Parallelogram({ 7, 1 }, 6, 6, gridSize, penColor, RGB(255, 185, 200));

	this->grid = false;
}

CIND16995View::~CIND16995View()
{
	if (this->largeTriangle1 != nullptr)
	{
		delete this->largeTriangle1;
		this->largeTriangle1 = nullptr;
	}

	if (this->largeTriangle2 != nullptr)
	{
		delete this->largeTriangle2;
		this->largeTriangle2 = nullptr;
	}

	if (this->mediumTriangle != nullptr)
	{
		delete this->mediumTriangle;
		this->mediumTriangle = nullptr;
	}

	if (this->smallTriangle1 != nullptr)
	{
		delete this->smallTriangle1;
		this->smallTriangle1 = nullptr;
	}

	if (this->smallTriangle2 != nullptr)
	{
		delete this->smallTriangle2;
		this->smallTriangle2 = nullptr;
	}

	if (this->square != nullptr)
	{
		delete this->square;
		this->square = nullptr;
	}

	if (this->parallelogram != nullptr)
	{
		delete this->parallelogram;
		this->parallelogram = nullptr;
	}

	if (this->drawingPen != nullptr)
	{
		delete this->drawingPen;
		this->drawingPen = nullptr;
	}
}

BOOL CIND16995View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CIND16995View drawing

void CIND16995View::DrawBackground(CDC* pDC)
{
	CPen* oldPen = (CPen*) pDC->SelectStockObject(NULL_PEN);
	CBrush* newBrush = new CBrush(RGB(200, 200, 200)),
		* oldBrush = pDC->SelectObject(newBrush);

	pDC->Rectangle(0, 0, windowSize.Width(), windowSize.Height());

	pDC->SelectObject(oldBrush);
	pDC->SelectObject(oldPen);

	delete newBrush;
}

void CIND16995View::DrawGrid(CDC* pDC)
{
	if (this->grid)
	{
		CPen* newPen = new CPen(PS_SOLID, 1, RGB(255, 255, 255)),
			*oldPen = pDC->SelectObject(newPen);

		POINT* points = new POINT[(this->gridCount + 1) << 2];
		DWORD* lengths = new DWORD[(this->gridCount + 1) << 1];

		int endW = windowSize.Width(),
			endH = windowSize.Height(),
			step = this->gridSize,
			i = 0,
			j = 0;

		for (int par = 0; par <= endH; par += step)
		{
			points[i++] = { 0, par };
			points[i++] = { endW, par };
			lengths[j++] = 2;
		}

		for (int par = 0; par <= endW; par += step)
		{
			points[i++] = { par, 0 };
			points[i++] = { par, endH };
			lengths[j++] = 2;
		}

		pDC->PolyPolyline(points, lengths, (this->gridCount + 1) << 1);

		delete[] lengths;
		delete[] points;

		pDC->SelectObject(oldPen);
		delete newPen;
	}
}

void CIND16995View::OnDraw(CDC* pDC)
{
	CIND16995Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	CRect rect;
	GetClientRect(&rect);
	CPoint viewportOrg = pDC->SetViewportOrg((rect.Width() - this->windowSize.Width()) / 2, (rect.Height() - this->windowSize.Height()) / 2);

	this->DrawBackground(pDC);

	this->largeTriangle1->Draw(pDC);
	this->largeTriangle2->Draw(pDC);
	this->mediumTriangle->Draw(pDC);
	this->smallTriangle1->Draw(pDC);
	this->smallTriangle2->Draw(pDC);
	this->square->Draw(pDC);
	this->parallelogram->Draw(pDC);

	this->DrawGrid(pDC);

	pDC->SetViewportOrg(viewportOrg);
}

// CIND16995View printing

BOOL CIND16995View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CIND16995View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CIND16995View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CIND16995View diagnostics

#ifdef _DEBUG
void CIND16995View::AssertValid() const
{
	CView::AssertValid();
}

void CIND16995View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CIND16995Doc* CIND16995View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CIND16995Doc)));
	return (CIND16995Doc*)m_pDocument;
}
#endif //_DEBUG


// CIND16995View message handlers


void CIND16995View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	if (nChar == VK_SPACE)
	{
		this->grid = !this->grid;
		// this->OnDraw(GetDC());
		Invalidate();
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
