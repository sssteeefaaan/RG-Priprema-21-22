
// Maj2021.h : main header file for the Maj2021 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CMaj2021App:
// See Maj2021.cpp for the implementation of this class
//

class CMaj2021App : public CWinApp
{
public:
	CMaj2021App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CMaj2021App theApp;
