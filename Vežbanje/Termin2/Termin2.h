
// Termin2.h : main header file for the Termin2 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CTermin2App:
// See Termin2.cpp for the implementation of this class
//

class CTermin2App : public CWinApp
{
public:
	CTermin2App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTermin2App theApp;
