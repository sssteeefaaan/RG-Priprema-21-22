
// OpenGL_2022View.h : interface of the COpenGL2022View class
//

#pragma once
#include "CGLRenderer.h"

class COpenGL2022View : public CView
{
protected: // create from serialization only
	COpenGL2022View() noexcept;
	DECLARE_DYNCREATE(COpenGL2022View)

// Attributes
public:
	COpenGL2022Doc* GetDocument() const;
	CGLRenderer m_glRenderer;
	CPoint prev_mouse;

// Operations
public:

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
	virtual ~COpenGL2022View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
};

#ifndef _DEBUG  // debug version in OpenGL_2022View.cpp
inline COpenGL2022Doc* COpenGL2022View::GetDocument() const
   { return reinterpret_cast<COpenGL2022Doc*>(m_pDocument); }
#endif

