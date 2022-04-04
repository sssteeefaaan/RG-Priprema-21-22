
// Brush_HatchView.h : interface of the CBrushHatchView class
//

#pragma once

struct list {
	CPoint* elements;
	long count;
	long max;
};

class CBrushHatchView : public CView
{
protected: // create from serialization only
	CBrushHatchView() noexcept;
	DECLARE_DYNCREATE(CBrushHatchView)

// Attributes
public:
	CBrushHatchDoc* GetDocument() const;
	void DrawUserInput(CDC* pDC);

private:
	list points;
	bool input;

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
	virtual ~CBrushHatchView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	void CBrushHatchView::DrawGrid(CDC* pDC, int xCount, int yCount, CRect* window);

	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // debug version in Brush_HatchView.cpp
inline CBrushHatchDoc* CBrushHatchView::GetDocument() const
   { return reinterpret_cast<CBrushHatchDoc*>(m_pDocument); }
#endif

