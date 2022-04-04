
// Termin2View.h : interface of the CTermin2View class
//

#pragma once


class CTermin2View : public CView
{
protected: // create from serialization only
	CTermin2View() noexcept;
	DECLARE_DYNCREATE(CTermin2View)

// Attributes
public:
	CTermin2Doc* GetDocument() const;

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
	virtual ~CTermin2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Termin2View.cpp
inline CTermin2Doc* CTermin2View::GetDocument() const
   { return reinterpret_cast<CTermin2Doc*>(m_pDocument); }
#endif

