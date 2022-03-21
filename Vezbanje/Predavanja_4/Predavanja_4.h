
// Predavanja_4.h : main header file for the Predavanja_4 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CPredavanja4App:
// See Predavanja_4.cpp for the implementation of this class
//

class CPredavanja4App : public CWinApp
{
public:
	CPredavanja4App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPredavanja4App theApp;
