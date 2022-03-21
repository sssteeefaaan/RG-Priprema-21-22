
// Lab_1_Proba_1View.h : interface of the CLab1Proba1View class
//

#pragma once


class CLab1Proba1View : public CView
{
protected: // create from serialization only
	CLab1Proba1View() noexcept;
	DECLARE_DYNCREATE(CLab1Proba1View)

// Attributes
public:
	CLab1Proba1Doc* GetDocument() const;

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
	virtual ~CLab1Proba1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Lab_1_Proba_1View.cpp
inline CLab1Proba1Doc* CLab1Proba1View::GetDocument() const
   { return reinterpret_cast<CLab1Proba1Doc*>(m_pDocument); }
#endif

