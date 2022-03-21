
// OpenGL_VezbaView.h : interface of the COpenGLVezbaView class
//

#pragma once
#include "CGLRender.h"


class COpenGLVezbaView : public CView
{
protected: // create from serialization only
	COpenGLVezbaView() noexcept;
	DECLARE_DYNCREATE(COpenGLVezbaView)

// Attributes
public:
	COpenGLVezbaDoc* GetDocument() const;
	CGLRender *m_glRenderer;
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
	virtual ~COpenGLVezbaView();
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
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // debug version in OpenGL_VezbaView.cpp
inline COpenGLVezbaDoc* COpenGLVezbaView::GetDocument() const
   { return reinterpret_cast<COpenGLVezbaDoc*>(m_pDocument); }
#endif

