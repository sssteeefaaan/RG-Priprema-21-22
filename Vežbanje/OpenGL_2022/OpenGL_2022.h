
// OpenGL_2022.h : main header file for the OpenGL_2022 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COpenGL2022App:
// See OpenGL_2022.cpp for the implementation of this class
//

class COpenGL2022App : public CWinApp
{
public:
	COpenGL2022App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COpenGL2022App theApp;
