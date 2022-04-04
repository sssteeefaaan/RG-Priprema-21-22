
// Januar2021View.h : interface of the CJanuar2021View class
//

#pragma once
#include "DImage.h"

class CJanuar2021View : public CView
{
protected: // create from serialization only
	CJanuar2021View() noexcept;
	DECLARE_DYNCREATE(CJanuar2021View)

// Attributes
public:
	CJanuar2021Doc* GetDocument() const;
	DImage m_backdrop;
	DImage m_body;
	DImage m_leg1;
	DImage m_leg2;
	DImage m_leg3;

	int m_step;
	int m_lleg1;
	int m_lleg2;
	int m_rleg1;
	int m_rleg2;

// Operations
public:
	void DrawTransparent(CDC* pDC, DImage* pImage, COLORREF color);
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void Scale(CDC* pDC, float sX, float sY, bool rightMultiply);
	void DrawLeg(CDC* pDC, double alpha, double dx, double dy);
	void DrawScene(CDC* pDC, double scale, int step);
	void CalcOffsets(int offset);

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
	virtual ~CJanuar2021View();
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
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
};

#ifndef _DEBUG  // debug version in Januar2021View.cpp
inline CJanuar2021Doc* CJanuar2021View::GetDocument() const
   { return reinterpret_cast<CJanuar2021Doc*>(m_pDocument); }
#endif

