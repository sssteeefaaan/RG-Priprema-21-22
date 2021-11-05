
// IND_16995View.h : interface of the CIND16995View class
//

#pragma once

#define _USE_MATH_DEFINES
#include <math.h>

struct DPOINT {
	double x;
	double y;
};

struct triangle {
	DPOINT center;
	double a;
	double rot;
	int inscribedPolygonPoints;
	COLORREF color;
	int HB;
};

struct square {
	DPOINT center;
	double a;
	double rot;
	COLORREF color;
	int HB;
};

struct parallelogram {
	DPOINT vertex;
	double a;
	double h;
	double rot;
	bool mirrorX;
	COLORREF color;
	int HB;
};


class CIND16995View : public CView
{
protected: // create from serialization only
	CIND16995View() noexcept;
	DECLARE_DYNCREATE(CIND16995View)

// Attributes
public:
	CIND16995Doc* GetDocument() const;

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
	virtual ~CIND16995View();
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
	void DrawGrid(CDC*);
	void DrawBackground(CDC* pDC);
	void DrawRegularPolygon(CDC* pDC, int cx, int cy, int r, int n, int rot);
	void DrawTriangleWithInscribedPolygon(CDC* pDC, struct triangle t);
	void DrawSquare(CDC* pDC, struct square s);
	void DrawParallelogram(CDC* pDC, struct parallelogram p);

	POINT* GetRegularPoligonPoints(int cx, int cy, int r, int n, int rot);
	POINT* GetParalelogramPoints(DPOINT vertex, int a, int h, int rot, bool mirrorX);
	double GetDistance(POINT a, POINT b);

private:
	bool grid;
	int gridSize;
	int gridCount;
	COLORREF backgroundColor;
	COLORREF penColor;
	CRect windowSize;
};

#ifndef _DEBUG  // debug version in IND_16995View.cpp
inline CIND16995Doc* CIND16995View::GetDocument() const
   { return reinterpret_cast<CIND16995Doc*>(m_pDocument); }
#endif

