
// Januar2020View.h : interface of the CJanuar2020View class
//

#pragma once
#include "DImage.h"

class CJanuar2020View : public CView
{
protected: // create from serialization only
	CJanuar2020View() noexcept;
	DECLARE_DYNCREATE(CJanuar2020View)

// Attributes
public:
	CJanuar2020Doc* GetDocument() const;

// Operations
public:
	void DrawCycle(CDC* pDC, int r, int n, int d);
	CPoint DrawBicycle(CDC* pDC, int r, int n, int d, int alpha, int beta);
	void Draw_Text(CDC* pDC, int size, CString strText, COLORREF clrText);
	void SaveDC(CDC* pDC, CRect rcDC, CRect rcBmp);
	
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
	virtual ~CJanuar2020View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Januar2020View.cpp
inline CJanuar2020Doc* CJanuar2020View::GetDocument() const
   { return reinterpret_cast<CJanuar2020Doc*>(m_pDocument); }
#endif

