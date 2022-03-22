
// Oktobar2021.h : main header file for the Oktobar2021 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// COktobar2021App:
// See Oktobar2021.cpp for the implementation of this class
//

class COktobar2021App : public CWinApp
{
public:
	COktobar2021App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern COktobar2021App theApp;
