
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


// COpenGLView

IMPLEMENT_DYNCREATE(COpenGLView, CView)

BEGIN_MESSAGE_MAP(COpenGLView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_KEYDOWN()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

// COpenGLView construction/destruction

COpenGLView::COpenGLView() noexcept
{
	// TODO: add construction code here
	this->m_glRender = new CGLRender();
}

COpenGLView::~COpenGLView()
{
	if (this->m_glRender != NULL)
	{
		delete(this->m_glRender);
		this->m_glRender = NULL;
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
	COpenGLDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	this->m_glRender->DrawScene(pDC);
	// TODO: add draw code for native data here
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


int COpenGLView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CDC* pDC = GetDC();
	this->m_glRender->CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void COpenGLView::OnDestroy()
{
	CView::OnDestroy();

	CDC* pDC = GetDC();
	this->m_glRender->DestroyScene(pDC);
	ReleaseDC(pDC);
}


BOOL COpenGLView::OnEraseBkgnd(CDC* pDC)
{
	return TRUE;
	// TODO: Add your message handler code here and/or call default

	return CView::OnEraseBkgnd(pDC);
}


void COpenGLView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	this->m_glRender->Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void COpenGLView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	CDC* pDC = GetDC();
	this->m_glRender->PrepareScene(pDC);
	ReleaseDC(pDC);
}


BOOL COpenGLView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	this->m_glRender->Zoom(zDelta < 0);
	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


void COpenGLView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	switch (nChar)
	{
	case('P'):
		this->m_glRender->ToggleGrid();
		break;
	case('C'):
		this->m_glRender->ToggleAxes();
		break;
	case('Q'):
		this->m_glRender->RotatePiece(5);
		break;
	case('E'):
		this->m_glRender->RotatePiece(-5);
		break;
	case('A'):
		this->m_glRender->RotateView(0, 5);
		break;
	case('D'):
		this->m_glRender->RotateView(0, -5);
		break;
	case('W'):
		this->m_glRender->RotateView(5, 0);
		break;
	case('S'):
		this->m_glRender->RotateView(-5, 0);
		break;
	default:
		break;
	}

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void COpenGLView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default
	//this->m_glRender->LookAt(point.x, point.y, 0);
	//Invalidate();
	//CView::OnMouseMove(nFlags, point);
}
