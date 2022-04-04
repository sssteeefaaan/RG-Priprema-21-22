
// Maj2021View.h : interface of the CMaj2021View class
//

#pragma once


class CMaj2021View : public CView
{
protected: // create from serialization only
	CMaj2021View() noexcept;
	DECLARE_DYNCREATE(CMaj2021View)

// Attributes
public:
	CMaj2021Doc* GetDocument() const;

// Operations
public:
	void Translate(CDC* pDC, float dX, float dY, bool rightMultiply);
	void Rotate(CDC* pDC, float angle, bool rightMultiply);
	void DrawConeBottom(CDC* pDC, float cX, float cY, float a, float b, float h, int n);
	void DrawConeTop(CDC* pDC, float cX, float cY, float a, float b, float h, int n);
	void DrawCylinder(CDC* pDC, float cX, float cY, float a, float b, float h, int n);
	void DrawFigure(CDC* pDC, float cX, float cY, float a, float b, float h, int n, float r);

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
	virtual ~CMaj2021View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in Maj2021View.cpp
inline CMaj2021Doc* CMaj2021View::GetDocument() const
   { return reinterpret_cast<CMaj2021Doc*>(m_pDocument); }
#endif

