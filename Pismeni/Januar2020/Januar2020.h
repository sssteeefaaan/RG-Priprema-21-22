
// Januar2020.h : main header file for the Januar2020 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CJanuar2020App:
// See Januar2020.cpp for the implementation of this class
//

class CJanuar2020App : public CWinApp
{
public:
	CJanuar2020App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CJanuar2020App theApp;
