
// April2022.h : main header file for the April2022 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CApril2022App:
// See April2022.cpp for the implementation of this class
//

class CApril2022App : public CWinApp
{
public:
	CApril2022App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CApril2022App theApp;
