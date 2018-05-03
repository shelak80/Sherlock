// FAROOpenDemoApp.h : main header file for the FAROOpenDemoApp application
//

#if !defined(AFX_FAROOPENDEMOAPP_H__967ABCAF_2BE2_43D7_A3A0_89970F18D261__INCLUDED_)
#define AFX_FAROOPENDEMOAPP_H__967ABCAF_2BE2_43D7_A3A0_89970F18D261__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CFAROOpenDemoAppApp:
// See FAROOpenDemoApp.cpp for the implementation of this class
//

class CFAROOpenDemoAppApp : public CWinApp
{
public:
	CFAROOpenDemoAppApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFAROOpenDemoAppApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CFAROOpenDemoAppApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAROOPENDEMOAPP_H__967ABCAF_2BE2_43D7_A3A0_89970F18D261__INCLUDED_)
