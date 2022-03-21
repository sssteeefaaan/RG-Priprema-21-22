
// April2021View.h : interface of the CApril2021View class
//

#pragma once


class CApril2021View : public CView
{
protected: // create from serialization only
	CApril2021View() noexcept;
	DECLARE_DYNCREATE(CApril2021View)

// Attributes
public:
	CApril2021Doc* GetDocument() const;

// Operations
public:
	void DrawPetal(CDC* pDC, CRect rect, int nArcs, COLORREF clrFill, COLORREF clrLine);
	void DrawFlower(CDC* pDC, CRect rect, int nArcs, COLORREF clrFill, COLORREF clrLine, float dRot, CString str);
	void DrawFlowers(CDC* pDC, CRect* aRect, int* anArcs, COLORREF* aClrFill, COLORREF* aClrLine, float* aRot, CString* aStr, CPoint* aPts, int flowerNumber);
	void SaveDC(CDC* pDC, CRect reDC, CRect rcBmp);

	void Translate(CDC* pDC, int dX, int dY, bool rightMultiply);
	void Rotate(CDC* pDC, double angle, bool rightMultiply);

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
	virtual ~CApril2021View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in April2021View.cpp
inline CApril2021Doc* CApril2021View::GetDocument() const
   { return reinterpret_cast<CApril2021Doc*>(m_pDocument); }
#endif

