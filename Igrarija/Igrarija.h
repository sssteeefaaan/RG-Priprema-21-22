
// Igrarija.h : main header file for the Igrarija application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CIgrarijaApp:
// See Igrarija.cpp for the implementation of this class
//

class CIgrarijaApp : public CWinApp
{
public:
	CIgrarijaApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CIgrarijaApp theApp;
