
// April2019View.h : interface of the CApril2019View class
//

#pragma once
#include "DImage.h"

class CApril2019View : public CView
{
protected: // create from serialization only
	CApril2019View() noexcept;
	DECLARE_DYNCREATE(CApril2019View)

// Attributes
public:
	CApril2019Doc* GetDocument() const;
	double m_step;
	double m_alpha;
	CBitmap* m_mipmaps;

// Operations
public:
	void DrawWheel(CDC* pDC, double r1, double r2, double w);
	void DrawWP(CDC* pDC, double r1, double r2, double w, double L, double alpha, double d);
	void CMipMap(CString name);
	void DrawMipMap(CDC* pDC, int x, int y, int size);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);

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
	virtual ~CApril2019View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
};

#ifndef _DEBUG  // debug version in April2019View.cpp
inline CApril2019Doc* CApril2019View::GetDocument() const
   { return reinterpret_cast<CApril2019Doc*>(m_pDocument); }
#endif

