
// April2022View.h : interface of the CApril2022View class
//

#pragma once


class CApril2022View : public CView
{
protected: // create from serialization only
	CApril2022View() noexcept;
	DECLARE_DYNCREATE(CApril2022View)

// Attributes
public:
	CApril2022Doc* GetDocument() const;
	int m_angle;

// Operations
public:
	void DrawCybin(CDC* pDC, int w, int d, COLORREF clr, CString str, int size);
	void DrawWheel(CDC* pDC, int r, int d, int n, COLORREF clr);
	void DrawObservationWheel(CDC* pDC, int r, int d, int n, COLORREF clr, CString arStr[], int size, int k, CPoint ptCenter, float alpha);
	void SaveDC(CDC* pDC, CRect rcDC, CRect rcBmp, CString strBmp);

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
	virtual ~CApril2022View();
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

#ifndef _DEBUG  // debug version in April2022View.cpp
inline CApril2022Doc* CApril2022View::GetDocument() const
   { return reinterpret_cast<CApril2022Doc*>(m_pDocument); }
#endif

