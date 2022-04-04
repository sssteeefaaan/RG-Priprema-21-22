
// April2019.h : main header file for the April2019 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CApril2019App:
// See April2019.cpp for the implementation of this class
//

class CApril2019App : public CWinApp
{
public:
	CApril2019App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CApril2019App theApp;
