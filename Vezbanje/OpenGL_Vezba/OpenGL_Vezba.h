
// OpenGL_Vezba.h : main header file for the OpenGL_Vezba application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COpenGLVezbaApp:
// See OpenGL_Vezba.cpp for the implementation of this class
//

class COpenGLVezbaApp : public CWinApp
{
public:
	COpenGLVezbaApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGLVezbaApp theApp;
