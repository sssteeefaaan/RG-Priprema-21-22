
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

	// Algoritmi

	// Nagibni
	void NagibniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	void NagibniAlgoritamFULL(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	
	// Digitalni diferencijalni analizator
	// Inkrementalni
	void InkrementalniAlgoritam(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	void InkrementalniAlgoritamFULL(CDC* pDC, int x0, int y0, int x1, int y1, COLORREF value);
	
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

