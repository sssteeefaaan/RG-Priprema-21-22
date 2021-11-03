
// Lab_1_Proba_1.h : main header file for the Lab_1_Proba_1 application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CLab1Proba1App:
// See Lab_1_Proba_1.cpp for the implementation of this class
//

class CLab1Proba1App : public CWinApp
{
public:
	CLab1Proba1App() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	UINT  m_nAppLook;
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CLab1Proba1App theApp;
