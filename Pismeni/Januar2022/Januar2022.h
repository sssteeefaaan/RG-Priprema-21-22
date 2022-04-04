
// Januar2022.h : main header file for the Januar2022 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CJanuar2022App:
// See Januar2022.cpp for the implementation of this class
//

class CJanuar2022App : public CWinApp
{
public:
	CJanuar2022App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CJanuar2022App theApp;
