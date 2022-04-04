
// April2021.h : main header file for the April2021 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CApril2021App:
// See April2021.cpp for the implementation of this class
//

class CApril2021App : public CWinApp
{
public:
	CApril2021App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CApril2021App theApp;
