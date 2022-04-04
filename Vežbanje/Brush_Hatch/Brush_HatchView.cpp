
// Brush_HatchView.cpp : implementation of the CBrushHatchView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "Brush_Hatch.h"
#endif

#include "Brush_HatchDoc.h"
#include "Brush_HatchView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CBrushHatchView

IMPLEMENT_DYNCREATE(CBrushHatchView, CView)

BEGIN_MESSAGE_MAP(CBrushHatchView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEWHEEL()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CBrushHatchView construction/destruction

CBrushHatchView::CBrushHatchView() noexcept
{
	// TODO: add construction code here
	this->points = { new CPoint[32], 0, 32 };
	this->input = false;
}

CBrushHatchView::~CBrushHatchView()
{
	if (this->points.elements)
		delete(this->points.elements);
}

BOOL CBrushHatchView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CBrushHatchView drawing

void CBrushHatchView::OnDraw(CDC* pDC)
{
	/*CGdiObject *oldPen = pDC->SelectStockObject(NULL_PEN);
	CBrush* oldBrush = pDC->SelectObject(new CBrush(HS_CROSS, RGB(200, 0, 0)));
	pDC->Rectangle(this->point->x - this->halfSize, this->point->y - this->halfSize, this->point->x + this->halfSize, this->point->y + this->halfSize);
	delete(pDC->SelectObject(oldBrush));
	pDC->SelectObject(oldPen);*/

	/*CRect window;
	GetWindowRect(&window);

	pDC->SetWindowOrg(window.TopLeft());*/

	int oldGMMode = pDC->SetGraphicsMode(GM_ADVANCED);
	//int oldBkMode = pDC->SetBkMode(TRANSPARENT);

	DrawUserInput(pDC);

	pDC->SetGraphicsMode(oldGMMode);
	//pDC->SetBkMode(oldBkMode);
}

void CBrushHatchView::DrawUserInput(CDC* pDC)
{
	LOGBRUSH pen{};
	pen.lbColor = RGB(150, 0, 200);
	pen.lbStyle = BS_SOLID;

	CPen* oldPen = pDC->SelectObject(new CPen(PS_GEOMETRIC | PS_DASH, 5, &pen));

	for (int i = 0; i < this->points.count; i++)
		pDC->Ellipse(this->points.elements[i].x - 20, this->points.elements[i].y - 20, this->points.elements[i].x + 20, this->points.elements[i].y + 20);

	if (this->points.count > 1) {
		pDC->Polyline(this->points.elements, this->points.count);

		CFont newFont;
		LOGFONT font{};
		font.lfHeight = 20;
		wcsncpy_s(font.lfFaceName, L"Times New Roman", sizeof(L"Times New Roman"));
		CFont* oldFont = pDC->SelectObject(&newFont);

		COLORREF oldTextColor = pDC->SetTextColor(RGB(150, 0, 200));
		CString text("Stefan je car!");
		double textLenght = 20.0 / sqrt(pow(pDC->GetTextExtent(text).cx, 2) + pow(pDC->GetTextExtent(text).cy, 2));

		pDC->SelectObject(oldFont);
		
		for (int i = 0; i < this->points.count - 1; i++)
		{
			int ind1 = this->points.elements[i].x < this->points.elements[i + 1].x ? i : i + 1,
				ind2 = ind1 == i ? i + 1 : i;

			double lenght = sqrt(pow(this->points.elements[ind2].y - this->points.elements[ind1].y, 2) + pow(this->points.elements[ind2].x - this->points.elements[ind1].x, 2));
			font.lfHeight = lenght * textLenght + 0.5;
			font.lfEscapement = atan((double)(this->points.elements[ind2].y - this->points.elements[ind1].y) / (this->points.elements[ind2].x - this->points.elements[ind1].x)) * 180.0 / 3.14 * -10;

			newFont.CreateFontIndirectW(&font);
			CFont* oldFont = pDC->SelectObject(&newFont);

			pDC->TextOutW(this->points.elements[ind1].x, this->points.elements[ind1].y, text);

			pDC->SelectObject(oldFont);
			newFont.DeleteObject();
		}

		pDC->SetTextColor(oldTextColor);
	}
	if (this->input)
	{
		this->input = false;
		if (this->points.elements)
		{
			delete(this->points.elements);
			this->points.elements = new CPoint[this->points.max];
			this->points.count = 0;
		}
	}

	delete(pDC->SelectObject(oldPen));
}

void CBrushHatchView::DrawGrid(CDC* pDC, int xCount, int yCount, CRect* window)
{
	POINT* points = new POINT[(xCount + yCount + 2) << 1];
	DWORD* segments = new DWORD[xCount + yCount + 2];
	int dx = window->Width() / (double)xCount + 0.5,
		dy = window->Height() / (double)yCount +0.5,
		counter = 0;

	for (int i = window->TopLeft().y; i < window->BottomRight().y; i += dy)
	{
		segments[counter >> 1] = 2;
		points[counter++] = { window->TopLeft().x, i };
		points[counter++] = { window->BottomRight().x, i };
	}
	for (int i = window->TopLeft().x; i < window->BottomRight().x; i += dx)
	{
		segments[counter >> 1] = 2;
		points[counter++] = { i, window->TopLeft().y };
		points[counter++] = { i, window->BottomRight().y };
	}

	pDC->PolyPolyline(points, segments, counter >> 1);

	if(segments)
		delete(segments);
	if(points)
		delete(points);
}


// CBrushHatchView printing

BOOL CBrushHatchView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CBrushHatchView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CBrushHatchView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CBrushHatchView diagnostics

#ifdef _DEBUG
void CBrushHatchView::AssertValid() const
{
	CView::AssertValid();
}

void CBrushHatchView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CBrushHatchDoc* CBrushHatchView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CBrushHatchDoc)));
	return (CBrushHatchDoc*)m_pDocument;
}
#endif //_DEBUG


// CBrushHatchView message handlers


void CBrushHatchView::OnLButtonUp(UINT nFlags, CPoint point)
{
	if (this->points.max > this->points.count)
		this->points.elements[this->points.count++] = point;
	else
		MessageBoxA(NULL, "Prekoracen broj tacaka", "Greska", MB_ABORTRETRYIGNORE);
	CView::OnLButtonUp(nFlags, point);
	Invalidate();
}


BOOL CBrushHatchView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default

	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CBrushHatchView::OnRButtonUp(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	this->input = true;
	CView::OnRButtonUp(nFlags, point);
	Invalidate();
}
