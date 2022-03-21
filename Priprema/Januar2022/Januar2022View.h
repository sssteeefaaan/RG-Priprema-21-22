
// Januar2022View.h : interface of the CJanuar2022View class
//

#pragma once

#include "DImage.h"


class CJanuar2022View : public CView
{
protected: // create from serialization only
	CJanuar2022View() noexcept;
	DECLARE_DYNCREATE(CJanuar2022View)

// Attributes
public:
	CJanuar2022Doc* GetDocument() const;

// Operations
public:
	void Translate(CDC*, float, float, bool);
	void Rotate(CDC*, float, bool);
	void Part1(CDC*, int);
	void Part2(CDC*, int);
	void Part3(CDC*, int);
	void Part4(CDC*, int);
	void DrawPuzzle(CDC*, int, float, int, int);
	void DrawMagnifiedBitmap(CDC*, int, const CString&);

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
	virtual ~CJanuar2022View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Januar2022View.cpp
inline CJanuar2022Doc* CJanuar2022View::GetDocument() const
   { return reinterpret_cast<CJanuar2022Doc*>(m_pDocument); }
#endif

