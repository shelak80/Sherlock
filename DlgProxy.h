// DlgProxy.h : header file
//

#if !defined(AFX_DLGPROXY_H__C967C963_B63E_46FA_B449_EFD739EF1DF6__INCLUDED_)
#define AFX_DLGPROXY_H__C967C963_B63E_46FA_B449_EFD739EF1DF6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFAROOpenDemoAppDlg;

/////////////////////////////////////////////////////////////////////////////
// CFAROOpenDemoAppDlgAutoProxy command target

class CFAROOpenDemoAppDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CFAROOpenDemoAppDlgAutoProxy)

	CFAROOpenDemoAppDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CFAROOpenDemoAppDlg* m_pDialog;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFAROOpenDemoAppDlgAutoProxy)
	public:
	virtual void OnFinalRelease();
	//}}AFX_VIRTUAL

// Implementation
protected:
	virtual ~CFAROOpenDemoAppDlgAutoProxy();

	// Generated message map functions
	//{{AFX_MSG(CFAROOpenDemoAppDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CFAROOpenDemoAppDlgAutoProxy)

	// Generated OLE dispatch map functions
	//{{AFX_DISPATCH(CFAROOpenDemoAppDlgAutoProxy)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_DISPATCH
	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGPROXY_H__C967C963_B63E_46FA_B449_EFD739EF1DF6__INCLUDED_)
