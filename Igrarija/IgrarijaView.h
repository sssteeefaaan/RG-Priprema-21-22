
// IgrarijaView.h : interface of the CIgrarijaView class
//

#pragma once


class CIgrarijaView : public CView
{
protected: // create from serialization only
	CIgrarijaView() noexcept;
	DECLARE_DYNCREATE(CIgrarijaView)

// Attributes
public:
	CIgrarijaDoc* GetDocument() const;

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
	virtual ~CIgrarijaView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in IgrarijaView.cpp
inline CIgrarijaDoc* CIgrarijaView::GetDocument() const
   { return reinterpret_cast<CIgrarijaDoc*>(m_pDocument); }
#endif

