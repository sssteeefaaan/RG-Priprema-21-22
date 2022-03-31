
// OpenGLView.cpp : implementation of the COpenGLView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL.h"
#endif

#include "OpenGLDoc.h"
#include "OpenGLView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#include "Januar2021.h"


// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COpenGLView construction/destruction

COpenGLView::COpenGLView() noexcept
{
	this->m_renderer = new Januar2021();
}

COpenGLView::~COpenGLView()
{
	if (this->m_renderer) {
		delete(this->m_renderer);
		this->m_renderer = nullptr;
	}
}

BOOL COpenGLView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenGLView drawing

void COpenGLView::OnDraw(CDC* pDC)
{
	m_renderer->DrawScene(pDC);
}


// COpenGLView printing

BOOL COpenGLView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COpenGLView diagnostics

#ifdef _DEBUG
void COpenGLView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLDoc* COpenGLView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLDoc)));
	return (COpenGLDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLView message handlers


void COpenGLView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	m_renderer->DestroyScene(pDC);
	ReleaseDC(pDC);
}


BOOL COpenGLView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
}


void COpenGLView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	m_renderer->PrepareScene(pDC);
	ReleaseDC(pDC);
}


int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	CDC* pDC = GetDC();
	m_renderer->CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void COpenGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	CDC* pDC = GetDC();
	m_renderer->Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


BOOL COpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	this->m_renderer->OnMouseWheel(nFlags, zDelta, pt);
	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	this->m_renderer->OnKeyDown(nChar, nRepCnt, nFlags);
	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}
