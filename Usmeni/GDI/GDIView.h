
// GDIView.h : interface of the CGDIView class
//

#pragma once


class CGDIView : public CView
{
protected: // create from serialization only
	CGDIView() noexcept;
	DECLARE_DYNCREATE(CGDIView)

// Attributes
public:
	CGDIDoc* GetDocument() const;

// Operations
public:
	void WritePixel(CDC* pDC, int x, int y, COLORREF value);
	void WritePixel4(CDC* pDC, int x, int y, COLORREF value);
	void WritePixel8(CDC* pDC, int x, int y, COLORREF value);

#pragma region Linija

	// Nagibni
	void NagibniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	void NagibniAlgoritamFULL(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	
	// Digitalni diferencijalni analizator
	// Inkrementalni
	void InkrementalniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	void InkrementalniAlgoritamFULL(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);

	// Bresenhem
	void Bresenham(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	void BresenhamFULL(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);

#pragma endregion

#pragma region Krug

	// Trigonometrijski algoritam
	void TrigCircle(CDC* pDC, int R, COLORREF value);
	
	// Polinomni algoritam
	void PolinomialCircle(CDC* pDC, int R, COLORREF value);

	// Bresenhemov algoritam
	void BresenhamCircle(CDC* pDC, int R, COLORREF value);

#pragma endregion

#pragma region Elipsa

	// Trigonometrijski algoritam
	void TrigEllipse(CDC* pDC, int a, int b, COLORREF value);

	// Polinomni algoritam
	void PolinomialElipse(CDC* pDC, int a, int b, COLORREF value);

	// Bresenhemov algoritam
	// Nope

	// Diferencijalni prvog i drugog reda
	void I_DifferentialEllipse(CDC* pDC, int a, int b, COLORREF value);
	void II_DifferentialEllipse(CDC* pDC, int a, int b, COLORREF value);

	void Ellipse(CDC* pDC, int left, int top, int right, int bottom);

#pragma endregion
	
	void Translate(CDC* pDC, float dX, float dY, bool rM = false);
	void Rotate(CDC* pDC, float angle, bool rM = false);
	void Scale(CDC* pDC, float sX, float sY, bool rM = false);
// Overrides
public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CGDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in GDIView.cpp
inline CGDIDoc* CGDIView::GetDocument() const
   { return reinterpret_cast<CGDIDoc*>(m_pDocument); }
#endif

