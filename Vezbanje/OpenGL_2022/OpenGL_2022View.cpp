
// OpenGL_2022View.cpp : implementation of the COpenGL2022View class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL_2022.h"
#endif

#include "OpenGL_2022Doc.h"
#include "OpenGL_2022View.h"

#pragma comment (lib, "OpenGL32.lib")
#pragma comment (lib, "glu32.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGL2022View

IMPLEMENT_DYNCREATE(COpenGL2022View, CView)

BEGIN_MESSAGE_MAP(COpenGL2022View, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_WM_KEYUP()
	ON_WM_MOUSEWHEEL()
END_MESSAGE_MAP()

// COpenGL2022View construction/destruction

COpenGL2022View::COpenGL2022View() noexcept
{
	prev_mouse.x = prev_mouse.y = 0;
}

COpenGL2022View::~COpenGL2022View()
{
}

BOOL COpenGL2022View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenGL2022View drawing

void COpenGL2022View::OnDraw(CDC* pDC)
{
	m_glRenderer.DrawScene(pDC);
}


// COpenGL2022View printing

BOOL COpenGL2022View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGL2022View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGL2022View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COpenGL2022View diagnostics

#ifdef _DEBUG
void COpenGL2022View::AssertValid() const
{
	CView::AssertValid();
}

void COpenGL2022View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGL2022Doc* COpenGL2022View::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGL2022Doc)));
	return (COpenGL2022Doc*)m_pDocument;
}
#endif //_DEBUG


// COpenGL2022View message handlers


int COpenGL2022View::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_glRenderer.CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void COpenGL2022View::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_glRenderer.DestroyScene(pDC);
	ReleaseDC(pDC);
}


BOOL COpenGL2022View::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;

	// return CView::OnEraseBkgnd(pDC);
}


void COpenGL2022View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_glRenderer.Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void COpenGL2022View::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_glRenderer.PrepareScene(pDC);
	ReleaseDC(pDC);
}

void COpenGL2022View::OnMouseMove(UINT nFlags, CPoint point)
{
	CView::OnMouseMove(nFlags, point);
}


void COpenGL2022View::OnLButtonUp(UINT nFlags, CPoint point)
{
	CView::OnLButtonUp(nFlags, point);
}


void COpenGL2022View::OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	switch (nChar)
	{
		break;
	case('A'):
		this->m_glRenderer.RotateView(0, -5);
		break;
	case('D'):
		this->m_glRenderer.RotateView(0, 5);
		break;
	case('W'):
		this->m_glRenderer.RotateView(5, 0);
		break;
	case('S'):
		this->m_glRenderer.RotateView(-5, 0);
		break;
	default:
		break;
	}

	Invalidate();
	CView::OnKeyUp(nChar, nRepCnt, nFlags);
}


BOOL COpenGL2022View::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	m_glRenderer.Zoom(zDelta < 0);
	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}
