
// Brush_Hatch.h : main header file for the Brush_Hatch application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CBrushHatchApp:
// See Brush_Hatch.cpp for the implementation of this class
//

class CBrushHatchApp : public CWinApp
{
public:
	CBrushHatchApp() noexcept;


// Overrides
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// Implementation
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CBrushHatchApp theApp;
