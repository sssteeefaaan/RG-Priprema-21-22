
// Oktobar2021View.h : interface of the COktobar2021View class
//

#pragma once


class COktobar2021View : public CView
{
protected: // create from serialization only
	COktobar2021View() noexcept;
	DECLARE_DYNCREATE(COktobar2021View)

// Attributes
public:
	COktobar2021Doc* GetDocument() const;

// Operations
public:
	void DrawTop(CDC* pDC, int size);
	void LoadIdentity(CDC* pDC);
	void Mirror(CDC* pDC, bool x, bool y, bool rightMultiply);
	void Translate(CDC* pDC, double x, double y, bool rightMultiply);
	void Rotate(CDC* pDC, double alpha, bool rightMultiply);
	void DrawTop2(CDC* pDC, int size);
	void DrawTail(CDC* pDC, int size, int count, double alpha);

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
	virtual ~COktobar2021View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Oktobar2021View.cpp
inline COktobar2021Doc* COktobar2021View::GetDocument() const
   { return reinterpret_cast<COktobar2021Doc*>(m_pDocument); }
#endif

