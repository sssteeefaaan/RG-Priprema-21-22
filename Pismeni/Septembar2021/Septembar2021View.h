
// Septembar2021View.h : interface of the CSeptembar2021View class
//

#pragma once
#include "DImage.h"

class CSeptembar2021View : public CView
{
protected: // create from serialization only
	CSeptembar2021View() noexcept;
	DECLARE_DYNCREATE(CSeptembar2021View)

// Attributes
public:
	CSeptembar2021Doc* GetDocument() const;

// Operations
public:
	void DrawTriangle(CDC* pDC, int side, int alpha, COLORREF clrFill, COLORREF clrLine);
	void DrawPart(CDC* pDC, int side, int alpha, COLORREF clrFill, COLORREF clrLine);
	void DrawParasol(CDC* pDC, int side, int nElement, bool bArc, COLORREF * aCrFill, COLORREF clrLine);
	void DrawSunbed(CDC* pDC, int size, int nElement, bool bArc, COLORREF* aClrFill, COLORREF clrLine);
	void DrawSunbeds(CDC* pDC, int size, int nElement, COLORREF* aClrFill, COLORREF clrLine, bool** arArc, int n, CPoint start);
	void SaveDC(CDC* pDC, CRect rcDC, CRect rcBmp, CString sFile);

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
	virtual ~CSeptembar2021View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Septembar2021View.cpp
inline CSeptembar2021Doc* CSeptembar2021View::GetDocument() const
   { return reinterpret_cast<CSeptembar2021Doc*>(m_pDocument); }
#endif

