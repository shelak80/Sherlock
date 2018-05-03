// FAROpenDemoAppDlg.h : header file
//

#include "afxwin.h"
#include "afxcmn.h"
#if !defined(AFX_FAROOPENDEMOAPPDLG_H__BE0669AF_57B0_4779_B3DC_68AA18078D50__INCLUDED_)
#define AFX_FAROOPENDEMOAPPDLG_H__BE0669AF_57B0_4779_B3DC_68AA18078D50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CFAROOpenDemoAppDlgAutoProxy;

/////////////////////////////////////////////////////////////////////////////
// CFAROOpenDemoAppDlg dialog

class CFAROOpenDemoAppDlg : public CDialog
{
	DECLARE_DYNAMIC(CFAROOpenDemoAppDlg);
	friend class CFAROOpenDemoAppDlgAutoProxy;

// Construction
public:
	CFAROOpenDemoAppDlg(CWnd* pParent = NULL);	// standard constructor
	virtual ~CFAROOpenDemoAppDlg();

// Dialog Data
	//{{AFX_DATA(CFAROOpenDemoAppDlg)
	enum { IDD = IDD_FAROOPENDEMOAPP_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFAROOpenDemoAppDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CFAROOpenDemoAppDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();
	void UpdateScanLoadState();

	// Generated message map functions
	//{{AFX_MSG(CFAROOpenDemoAppDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CString m_VersionStr;

	CString m_Workspace;
	CString m_NumScans;
	afx_msg void OnBnClickedBrowse();
	afx_msg void OnBnClickedLoadWsp();

	CString m_ScanNo;
	CButton m_LoadScanCtrl;
	CButton m_UnloadScanCtrl;
	CSpinButtonCtrl m_SpinScansCtrl;
	afx_msg void OnBnClickedLoadScan();
	afx_msg void OnBnClickedUnloadScan();
	afx_msg void OnDeltaposSpinScans(NMHDR *pNMHDR, LRESULT *pResult);

	CString m_NumRows;
	CString m_NumCols;

	CButton m_AccessScanCtrl;
	CButton m_AccessScanCtrl2;
	CProgressCtrl m_AccessProgressCtrl;
	afx_msg void OnBnClickedAccessScan();
	afx_msg void OnBnClickedAccessScan2();
	afx_msg void OnBnClickedGetMessage();
	afx_msg void OnBnClickedGetTrigger();
	// automation message nr 
	int automationMessageNr;
	// automation trigger nr
	int automationTriggerMarkerNr;
	// resulting string holding automation message data
	CString automationMessageStr;
	// automation trigger string holding its informoriton
	CString automationTriggerStr;
	afx_msg void OnStnClickedTriggerTxt();
	// info about number of automation messages and triggers
	CString automationDataStr;
	// Column of scanpoint for automation time
	int scanPtColumn;
	// scan point row for automation time
	int scanPtRow;
	CString resultAutomationTimeOfScanPoint;
	CString resultScanPtCoords;
	ULONGLONG automationTimeOfScanPt;
	afx_msg void OnBnClickedTimeOfScanPoint();
	afx_msg void OnBnGetScanPtCoordsFromAtime();
	afx_msg void OnBnClickedAutomationTest();

	int dummy;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FAROOPENDEMOAPPDLG_H__BE0669AF_57B0_4779_B3DC_68AA18078D50__INCLUDED_)
