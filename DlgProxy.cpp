//test
// DlgProxy.cpp : implementation file
//

#include "stdafx.h"
#include "FAROOpenDemoApp.h"
#include "DlgProxy.h"
#include "FAROOpenDemoAppDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFAROOpenDemoAppDlgAutoProxy

IMPLEMENT_DYNCREATE(CFAROOpenDemoAppDlgAutoProxy, CCmdTarget)

CFAROOpenDemoAppDlgAutoProxy::CFAROOpenDemoAppDlgAutoProxy()
{
	EnableAutomation();
	
	// To keep the application running as long as an automation 
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT (AfxGetApp()->m_pMainWnd != NULL);
	ASSERT_VALID (AfxGetApp()->m_pMainWnd);
	ASSERT_KINDOF(CFAROOpenDemoAppDlg, AfxGetApp()->m_pMainWnd);
	m_pDialog = (CFAROOpenDemoAppDlg*) AfxGetApp()->m_pMainWnd;
	m_pDialog->m_pAutoProxy = this;
}

CFAROOpenDemoAppDlgAutoProxy::~CFAROOpenDemoAppDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != NULL)
		m_pDialog->m_pAutoProxy = NULL;
	AfxOleUnlockApp();
}

void CFAROOpenDemoAppDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CFAROOpenDemoAppDlgAutoProxy, CCmdTarget)
	//{{AFX_MSG_MAP(CFAROOpenDemoAppDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CFAROOpenDemoAppDlgAutoProxy, CCmdTarget)
	//{{AFX_DISPATCH_MAP(CFAROOpenDemoAppDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_DISPATCH_MAP
END_DISPATCH_MAP()

// Note: we add support for IID_IFAROOpenDemoApp to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the 
//  dispinterface in the .ODL file.

// {C520EC3B-FD2A-45A9-B298-D3380E658D55}
static const IID IID_IFAROOpenDemoApp =
{ 0xc520ec3b, 0xfd2a, 0x45a9, { 0xb2, 0x98, 0xd3, 0x38, 0xe, 0x65, 0x8d, 0x55 } };

BEGIN_INTERFACE_MAP(CFAROOpenDemoAppDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CFAROOpenDemoAppDlgAutoProxy, IID_IFAROOpenDemoApp, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in StdAfx.h of this project
// {058414C1-7294-4AD5-95ED-FD404FBBA733}
IMPLEMENT_OLECREATE2(CFAROOpenDemoAppDlgAutoProxy, "FAROOpenDemoApp.Application", 0x58414c1, 0x7294, 0x4ad5, 0x95, 0xed, 0xfd, 0x40, 0x4f, 0xbb, 0xa7, 0x33)

/////////////////////////////////////////////////////////////////////////////
// CFAROOpenDemoAppDlgAutoProxy message handlers
