
// Septembar2021.h : main header file for the Septembar2021 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CSeptembar2021App:
// See Septembar2021.cpp for the implementation of this class
//

class CSeptembar2021App : public CWinApp
{
public:
	CSeptembar2021App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CSeptembar2021App theApp;
