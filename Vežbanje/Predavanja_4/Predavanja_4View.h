
// Predavanja_4View.h : interface of the CPredavanja4View class
//

#pragma once


class CPredavanja4View : public CView
{
protected: // create from serialization only
	CPredavanja4View() noexcept;
	DECLARE_DYNCREATE(CPredavanja4View)

// Attributes
public:
	CPredavanja4Doc* GetDocument() const;

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
	virtual ~CPredavanja4View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Predavanja_4View.cpp
inline CPredavanja4Doc* CPredavanja4View::GetDocument() const
   { return reinterpret_cast<CPredavanja4Doc*>(m_pDocument); }
#endif

