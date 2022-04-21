
// 6-GDIView.h : interface of the CMy6GDIView class
//

#pragma once


class CMy6GDIView : public CView
{
protected: // create from serialization only
	CMy6GDIView() noexcept;
	DECLARE_DYNCREATE(CMy6GDIView)

// Attributes
public:
	CMy6GDIDoc* GetDocument() const;

// Operations
public:
	void Interior_Defined_Fill_4_Pixel(CDC* pDC, int x, int y, COLORREF old_value, COLORREF new_value);
	void Interior_Defined_Fill_8_Pixel(CDC* pDC, int x, int y, COLORREF old_value, COLORREF new_value);
	void Boundry_Defined_Fill_4_Pixel(CDC* pDC, int x, int y, COLORREF boundry_value, COLORREF new_value);
	void Boundry_Defined_Fill_8_Pixel(CDC* pDC, int x, int y, COLORREF boundry_value, COLORREF new_value);
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
	virtual ~CMy6GDIView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in 6-GDIView.cpp
inline CMy6GDIDoc* CMy6GDIView::GetDocument() const
   { return reinterpret_cast<CMy6GDIDoc*>(m_pDocument); }
#endif

