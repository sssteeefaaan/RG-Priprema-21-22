
// OpenGL_VezbaView.cpp : implementation of the COpenGLVezbaView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "OpenGL_Vezba.h"
#endif

#include "OpenGL_VezbaDoc.h"
#include "OpenGL_VezbaView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// COpenGLVezbaView

IMPLEMENT_DYNCREATE(COpenGLVezbaView, CView)

BEGIN_MESSAGE_MAP(COpenGLVezbaView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_MOUSEWHEEL()
	ON_WM_ERASEBKGND()
	ON_WM_SIZE()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP()

// COpenGLVezbaView construction/destruction

COpenGLVezbaView::COpenGLVezbaView() noexcept
{
	// TODO: add construction code here
	this->m_glRenderer = new CGLRender();
}

COpenGLVezbaView::~COpenGLVezbaView()
{
	if (this->m_glRenderer)
	{
		delete(this->m_glRenderer);
		this->m_glRenderer = nullptr;
	}
}

BOOL COpenGLVezbaView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// COpenGLVezbaView drawing

void COpenGLVezbaView::OnDraw(CDC* pDC)
{
	COpenGLVezbaDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;
	this->m_glRenderer->DrawScene(pDC);
	// TODO: add draw code for native data here
}


// COpenGLVezbaView printing

BOOL COpenGLVezbaView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void COpenGLVezbaView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void COpenGLVezbaView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// COpenGLVezbaView diagnostics

#ifdef _DEBUG
void COpenGLVezbaView::AssertValid() const
{
	CView::AssertValid();
}

void COpenGLVezbaView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

COpenGLVezbaDoc* COpenGLVezbaView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(COpenGLVezbaDoc)));
	return (COpenGLVezbaDoc*)m_pDocument;
}
#endif //_DEBUG


// COpenGLVezbaView message handlers


int COpenGLVezbaView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here
	CDC* pDC = GetDC();
	this->m_glRenderer->CreateGLContext(pDC);
	ReleaseDC(pDC);

	return 0;
}


void COpenGLVezbaView::OnDestroy()
{
	CView::OnDestroy();

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	this->m_glRenderer->DestroyScene(pDC);
	ReleaseDC(pDC);
}


BOOL COpenGLVezbaView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: Add your message handler code here and/or call default
	this->m_glRenderer->Zoom(zDelta < 0);

	Invalidate();
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}


BOOL COpenGLVezbaView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: Add your message handler code here and/or call default
	return TRUE;
	return CView::OnEraseBkgnd(pDC);
}


void COpenGLVezbaView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	CDC* pDC = GetDC();
	this->m_glRenderer->Reshape(pDC, cx, cy);
	ReleaseDC(pDC);
}


void COpenGLVezbaView::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: Add your message handler code here and/or call default
	double dW = (GetKeyState(VK_SHIFT) & 0x8000) ? -5 : 5;
	switch (nChar)
	{
	case('P'):
		this->m_glRenderer->ToggleGrid();
		break;
	case('C'):
		this->m_glRenderer->ToggleAxes();
		break;
	case('A'):
		this->m_glRenderer->RotateView(0, -5);
		break;
	case('D'):
		this->m_glRenderer->RotateView(0, 5);
		break;
	case('W'):
		this->m_glRenderer->RotateView(5, 0);
		break;
	case('S'):
		this->m_glRenderer->RotateView(-5, 0);
		break;
	case('B'):
		this->m_glRenderer->RotateBody(dW);
		break;
	case('H'):
		this->m_glRenderer->RotateHead(dW);
		break;
	case('J'):
		this->m_glRenderer->RotateLeftArm(dW);
		break;
	case('N'):
		this->m_glRenderer->RotateLeftElbow(dW);
		break;
	case('K'):
		this->m_glRenderer->RotateRightArm(dW);
		break;
	case('M'):
		this->m_glRenderer->RotateRightElbow(dW);
		break;
	default:
		break;
	}

	Invalidate();
	CView::OnKeyDown(nChar, nRepCnt, nFlags);
	
}


void COpenGLVezbaView::OnInitialUpdate()
{
	CView::OnInitialUpdate();

	// TODO: Add your specialized code here and/or call the base class
	CDC* pDC = GetDC();
	this->m_glRenderer->PrepareScene(pDC);
	ReleaseDC(pDC);
}
