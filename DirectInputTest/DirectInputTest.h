
// DirectInputTest.h : main header file for the DirectInputTest application
//
#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"       // main symbols


// CDirectInputTestApp:
// See DirectInputTest.cpp for the implementation of this class
//

class CDirectInputTestApp : public CWinApp
{
public:
	CDirectInputTestApp();


// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

public:
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CDirectInputTestApp theApp;
