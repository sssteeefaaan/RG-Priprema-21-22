
// Januar2021.h : main header file for the Januar2021 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CJanuar2021App:
// See Januar2021.cpp for the implementation of this class
//

class CJanuar2021App : public CWinApp
{
public:
	CJanuar2021App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CJanuar2021App theApp;
