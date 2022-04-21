
// 6-GDI.h : main header file for the 6-GDI application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMy6GDIApp:
// See 6-GDI.cpp for the implementation of this class
//

class CMy6GDIApp : public CWinApp
{
public:
	CMy6GDIApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMy6GDIApp theApp;
