// FAROOpenDemoAppDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FAROOpenDemoApp.h"
#include "FAROOpenDemoAppDlg.h"
#include "DlgProxy.h"
#include <iostream>

#include <atlsafe.h>

// Note: use the version string here which
// a) is installed on your development computer
// b) is the least required version for your application
// You don't have to enter the newest version here if your application can live with
// an older one!

#ifdef _WIN64
// Yes - type is 'win32' even on WIN64!
#pragma comment(linker, "\"/manifestdependency:type='win32' name='FARO.LS' version='1.1.408.2' processorArchitecture='amd64' publicKeyToken='1d23f5635ba800ab'\"")
#else
#pragma comment(linker, "\"/manifestdependency:type='win32' name='FARO.LS' version='1.1.408.2' processorArchitecture='x86' publicKeyToken='1d23f5635ba800ab'\"")
#endif

// These imports just defines the types - they don't determine which DLLs are actually loaded!
// You can choose whatever version you have installed on your system - as long as the interface is compatible
//#import "C:\Windows\winsxs\amd64_faro.ls_1d23f5635ba800ab_1.1.503.3_none_34818da5032c9ddb\iQopen.dll" no_namespace
//#import "C:\3DSystems\ScanDesign\XO\Branch\ControlX2018\XOV\DLL\x64.Release\bin\iQopen.dll" no_namespace
#import "C:\Windows\WinSxS\amd64_faro.ls_1d23f5635ba800ab_1.1.701.1_none_3591adaf356ae9b1\iQOpen.dll" no_namespace


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

IiQLibIfPtr iQLibIfPtr = NULL;

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFAROOpenDemoAppDlg dialog

IMPLEMENT_DYNAMIC(CFAROOpenDemoAppDlg, CDialog);

CFAROOpenDemoAppDlg::CFAROOpenDemoAppDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFAROOpenDemoAppDlg::IDD, pParent)
	, m_VersionStr(_T(""))
	, m_Workspace(_T(""))
	, m_NumScans(_T("-"))
	, m_ScanNo(_T("-"))
	, m_NumRows(_T("-"))
	, m_NumCols(_T("-"))
	, automationMessageNr(0)
	, automationTriggerMarkerNr(0)
	, automationMessageStr(_T(""))
	, automationTriggerStr(_T(""))
	, automationDataStr(_T(""))
	, scanPtColumn(0)
	, scanPtRow(0)
	, resultAutomationTimeOfScanPoint(_T(""))
	, resultScanPtCoords(_T(""))
	, automationTimeOfScanPt(0)
{
	//{{AFX_DATA_INIT(CFAROOpenDemoAppDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = NULL;

	CoInitialize(NULL);

	try {
		// Please note: The cryptic key is only a part of the complete license
		// string you need to unlock the interface. Please
		// follow the instructions in the 2nd line below
		BSTR licenseCode = L"FARO Open Runtime License\n"
			//#include "../FAROOpenLicense"	// Delete this line, uncomment the following line, and enter your own license key here:
			L"Key:N24E4N6MTAKXFM6T8KZHSQMPL\n"
			L"\n"
			L"The software is the registered property of FARO Scanner Production GmbH, Stuttgart, Germany.\n"
			L"All rights reserved.\n"
			L"This software may only be used with written permission of FARO Scanner Production GmbH, Stuttgart, Germany.";

		IiQLicensedInterfaceIfPtr licPtr(__uuidof(iQLibIf));
		try {
			licPtr->License = licenseCode;
			iQLibIfPtr = static_cast<IiQLibIfPtr>(licPtr);
		}
		catch (...) {
			AfxMessageBox("No license for FARO Open interface provided");
		}
	}
	catch (...) {
		AfxMessageBox("Cannot instantiate FARO Open interface");
		exit(1);
	}

	BSTR versionStr;
	versionStr = iQLibIfPtr->getLibVersion();
	m_VersionStr = versionStr;
}

CFAROOpenDemoAppDlg::~CFAROOpenDemoAppDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to NULL, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != NULL)
		m_pAutoProxy->m_pDialog = NULL;

	iQLibIfPtr = NULL;

	CoUninitialize();
	CoFreeUnusedLibraries();
}

void CFAROOpenDemoAppDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFAROOpenDemoAppDlg)
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_VERSION_STR, m_VersionStr);
	DDX_Text(pDX, IDC_WORKSPACE, m_Workspace);
	DDX_Control(pDX, IDC_LOAD_SCAN, m_LoadScanCtrl);
	DDX_Control(pDX, IDC_UNLOAD_SCAN, m_UnloadScanCtrl);
	DDX_Control(pDX, IDC_ACCESS_SCAN, m_AccessScanCtrl);
	DDX_Control(pDX, IDC_ACCESS_SCAN2, m_AccessScanCtrl2);
	DDX_Control(pDX, IDC_SPIN_SCANS, m_SpinScansCtrl);
	DDX_Control(pDX, IDC_ACCESS_PROGRESS, m_AccessProgressCtrl);
	DDX_Text(pDX, IDC_SCAN_NO, m_ScanNo);
	DDX_Text(pDX, IDC_NUM_ROWS, m_NumRows);
	DDX_Text(pDX, IDC_NUM_COLS, m_NumCols);
	DDX_Text(pDX, IDC_NUM_SCANS, m_NumScans);
	DDX_Text(pDX, IDC_MESSAGE_NR, automationMessageNr);
	DDX_Text(pDX, IDC_TRIGGER_NR, automationTriggerMarkerNr);
	DDX_Text(pDX, IDC_MESSAGE_TXT, automationMessageStr);
	DDX_Text(pDX, IDC_TRIGGER_TXT, automationTriggerStr);
	DDX_Text(pDX, IDC_AUTOMATION_INFO, automationDataStr);
	DDX_Text(pDX, IDC_EDIT_AUTOM_COL, scanPtColumn);
	DDX_Text(pDX, IDC_EDIT_AUTOM_ROW, scanPtRow);
	DDX_Text(pDX, IDC_STATIC_ATIME_OF_SCANPOINT, resultAutomationTimeOfScanPoint);
	DDX_Text(pDX, IDC_STATIC_SCAN_POINT_COORDS, resultScanPtCoords);
	DDX_Text(pDX, IDC_EDIT_AUTOMATION_TIME_TO_SCANPOINT, automationTimeOfScanPt);
}

BEGIN_MESSAGE_MAP(CFAROOpenDemoAppDlg, CDialog)
	//{{AFX_MSG_MAP(CFAROOpenDemoAppDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BROWSE, &CFAROOpenDemoAppDlg::OnBnClickedBrowse)
	ON_BN_CLICKED(IDC_LOAD_WSP, &CFAROOpenDemoAppDlg::OnBnClickedLoadWsp)
	ON_BN_CLICKED(IDC_LOAD_SCAN, &CFAROOpenDemoAppDlg::OnBnClickedLoadScan)
	ON_BN_CLICKED(IDC_UNLOAD_SCAN, &CFAROOpenDemoAppDlg::OnBnClickedUnloadScan)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SCANS, &CFAROOpenDemoAppDlg::OnDeltaposSpinScans)
	ON_BN_CLICKED(IDC_ACCESS_SCAN, &CFAROOpenDemoAppDlg::OnBnClickedAccessScan)
	ON_BN_CLICKED(IDC_ACCESS_SCAN2, &CFAROOpenDemoAppDlg::OnBnClickedAccessScan2)
	ON_BN_CLICKED(IDC_GET_MESSAGE, &CFAROOpenDemoAppDlg::OnBnClickedGetMessage)
	ON_BN_CLICKED(IDC_GET_TRIGGER, &CFAROOpenDemoAppDlg::OnBnClickedGetTrigger)
	ON_BN_CLICKED(IDC_BUTTON1, &CFAROOpenDemoAppDlg::OnBnClickedTimeOfScanPoint)
	ON_BN_CLICKED(IDC_BUTTON2, &CFAROOpenDemoAppDlg::OnBnGetScanPtCoordsFromAtime)
	ON_BN_CLICKED(IDC_AUTOMATION_TEST, &CFAROOpenDemoAppDlg::OnBnClickedAutomationTest)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFAROOpenDemoAppDlg message handlers

BOOL CFAROOpenDemoAppDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFAROOpenDemoAppDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFAROOpenDemoAppDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFAROOpenDemoAppDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CFAROOpenDemoAppDlg::OnClose() 
{
	if (CanExit())
		CDialog::OnClose();
}

void CFAROOpenDemoAppDlg::OnOK() 
{
	if (CanExit())
		CDialog::OnOK();
}

void CFAROOpenDemoAppDlg::OnCancel() 
{
	if (CanExit())
		CDialog::OnCancel();
}

BOOL CFAROOpenDemoAppDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != NULL)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}

//
// Update of:
//   - #Rows and #Cols
//   - the accessibility of the Load/Unload and Access buttons
//
void CFAROOpenDemoAppDlg::UpdateScanLoadState() 
{
	int scanNo = atoi(m_ScanNo);
	m_NumRows.Format("%d", iQLibIfPtr->getScanNumRows(scanNo));
	m_NumCols.Format("%d", iQLibIfPtr->getScanNumCols(scanNo));

	bool loadState = iQLibIfPtr->getScanLoadState(scanNo) ? true : false;
	m_LoadScanCtrl.EnableWindow(!loadState);
	m_UnloadScanCtrl.EnableWindow(loadState);
	m_AccessScanCtrl.EnableWindow(loadState);
	m_AccessScanCtrl2.EnableWindow(loadState);

	int numMessages = iQLibIfPtr->getNumAutomationMessages(scanNo);
	int numTriggers = iQLibIfPtr->getNumAutomationTriggers(scanNo);
	automationDataStr.Format("Automation data: Messages:%d, Triggers:%d",numMessages,numTriggers);

	UpdateData(false);
}

//
// Browse for Workspace
//
void CFAROOpenDemoAppDlg::OnBnClickedBrowse()
{
	CFileDialog fileDialog(true);

	if (fileDialog.DoModal()==IDOK) {
		m_Workspace = fileDialog.GetPathName();
	}

	UpdateData(false);
}

//
// Load the workspace (but no scan inside of it)
//
void CFAROOpenDemoAppDlg::OnBnClickedLoadWsp()
{
	HRESULT result;

	UpdateData(true);

	_bstr_t filename(m_Workspace);

	HCURSOR oldCurs = GetCursor();
	HCURSOR hCurs;
	hCurs = LoadCursor(NULL, IDC_WAIT);
	SetCursor(hCurs);

	result = iQLibIfPtr->load(filename);

	if (result==S_OK) {
		m_SpinScansCtrl.EnableWindow(true);
	}

	SetCursor(oldCurs);

	m_ScanNo = L"0";
	m_NumScans.Format("%d", iQLibIfPtr->getNumScans());

	UpdateScanLoadState();

	UpdateData(false);
}

//
// Load the currently selected scan
//
void CFAROOpenDemoAppDlg::OnBnClickedLoadScan()
{
	HRESULT result;

	UpdateData(true);

	HCURSOR oldCurs = GetCursor();
	HCURSOR hCurs;
	hCurs = LoadCursor(NULL, IDC_WAIT);
	SetCursor(hCurs);

	result = iQLibIfPtr->loadScan(atoi(m_ScanNo));

	SetCursor(oldCurs);

	UpdateScanLoadState();
}

//
// Unload the currently selected scan
//
void CFAROOpenDemoAppDlg::OnBnClickedUnloadScan()
{
	HRESULT result;

	UpdateData(true);

	result = iQLibIfPtr->unloadScan(atoi(m_ScanNo));

	UpdateScanLoadState();
}

//
// Spin the scan selection
//
void CFAROOpenDemoAppDlg::OnDeltaposSpinScans(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMUPDOWN pNMUpDown = reinterpret_cast<LPNMUPDOWN>(pNMHDR);

	int val;
	val = atoi(m_ScanNo);
	int numScans = atoi(m_NumScans);
	if (pNMUpDown->iDelta < 0) {
		if (val<numScans-1)
			val++;
	}
	else {
		if (val>0)
			val--;
	}
	m_ScanNo.Format("%d", val);
	
	*pResult = 0;

	UpdateScanLoadState();
}

//
// Access a scan column-by-column using the getXYZScanPoints() method
//
void CFAROOpenDemoAppDlg::OnBnClickedAccessScan()
{
	HRESULT result;

	UpdateData(true);

	HCURSOR oldCurs = GetCursor();
	HCURSOR hCurs;
	hCurs = LoadCursor(NULL, IDC_WAIT);
	SetCursor(hCurs);

	int scanNo = atoi(m_ScanNo);
	unsigned int numRows = iQLibIfPtr->getScanNumRows(scanNo);
	unsigned int numCols = iQLibIfPtr->getScanNumCols(scanNo);

	m_AccessProgressCtrl.SetRange(0, numCols/10);
	m_AccessProgressCtrl.SetPos(0);

	double* positions = new double[3*numRows];
	int* refls = new int[3*numRows];
	unsigned int invalidPts = 0;

	for (unsigned int col=0; col<numCols; col++) {
		if (!(col%10))
			m_AccessProgressCtrl.SetPos(col/10);
		
		result = iQLibIfPtr->getXYZScanPoints(scanNo, 0, col, numRows, positions, refls);

		if (result)
			break;
		for (unsigned row=0; row<numRows; row++)
			if (positions[(int)(3*row+0)]==0 && 
				positions[(int)(3*row+1)]==0 && 
				positions[(int)(3*row+2)]==0)
				invalidPts++;
	}

	delete refls;
	delete positions;

	SetCursor(oldCurs);

	UpdateData(false);
}

//
// Access a scan column-by-column using the getXYZScanPoints2() method. This
// method also supports correct marshaling between COM threads.
//
void CFAROOpenDemoAppDlg::OnBnClickedAccessScan2()
{
	HRESULT result;

	UpdateData(true);

	HCURSOR oldCurs = GetCursor();
	HCURSOR hCurs;
	hCurs = LoadCursor(NULL, IDC_WAIT);
	SetCursor(hCurs);

	int scanNo = atoi(m_ScanNo);
	unsigned int numRows = iQLibIfPtr->getScanNumRows(scanNo);
	unsigned int numCols = iQLibIfPtr->getScanNumCols(scanNo);

	m_AccessProgressCtrl.SetRange(0, numCols/10);
	m_AccessProgressCtrl.SetPos(0);

	unsigned int invalidPts = 0;

	for (unsigned int col=0; col<numCols; col++) {
		if (!(col%10))
			m_AccessProgressCtrl.SetPos(col/10);

		SAFEARRAY* arrayPositions;
		SAFEARRAY* arrayReflections;
		int result = iQLibIfPtr->getXYZScanPoints2(scanNo, 0, col, numRows, &arrayPositions, &arrayReflections);
		CComSafeArray<double> positions;
		positions.Attach(arrayPositions);
		CComSafeArray<int>  reflections;
		reflections.Attach(arrayReflections);

		if (result)
			break;
		for (unsigned row=0; row<numRows; row++)
			if (positions[(int)(3*row+0)]==0 && 
				positions[(int)(3*row+1)]==0 && 
				positions[(int)(3*row+2)]==0)
				invalidPts++;
	}

	SetCursor(oldCurs);

	UpdateData(false);
}

void CFAROOpenDemoAppDlg::OnBnClickedGetMessage()
{
	UpdateData(true);

	int scanNo = atoi(m_ScanNo);

	unsigned int canId,canDataHigh,canDataLow;
	unsigned long long atime;
	iQLibIfPtr->getAutomationMessage(scanNo,automationMessageNr,&atime,&canId,&canDataHigh,&canDataLow);
	
	automationMessageStr.Format("Msg.:%d, time:%I64d, id:%x, dh:%x, dl:%x",automationMessageNr, atime,canId,canDataHigh,canDataLow);

	UpdateData(false);
}

void CFAROOpenDemoAppDlg::OnBnClickedGetTrigger()
{
	UpdateData(true);

	int scanNo = atoi(m_ScanNo);

	unsigned long long atime;
	iQLibIfPtr->getAutomationTriggerTime(scanNo,automationTriggerMarkerNr,&atime);
	automationTriggerStr.Format("Tr.: %d, time:%I64d",automationTriggerMarkerNr, atime);

	UpdateData(false);
}


// get automation time of scan point
void CFAROOpenDemoAppDlg::OnBnClickedTimeOfScanPoint()
{
	UpdateData(true);

	int scanNo = atoi(m_ScanNo);

	unsigned long long atime=0;
	unsigned long long atimeSyncPulse=0;

	int res1 = iQLibIfPtr->getAutomationTimeOfScanPoint(scanNo,scanPtRow,scanPtColumn,&atime);

	//int res2 = iQLibIfPtr->getAutomationTimeOfSyncPulse(scanNo,scanPtColumn,&atimeSyncPulse);

	resultAutomationTimeOfScanPoint.Format("scan point time:%I64d, sync time:%I64d",atime,atimeSyncPulse);

	UpdateData(false);
}

void CFAROOpenDemoAppDlg::OnBnGetScanPtCoordsFromAtime()
{
	UpdateData(true);

	int scanNo = atoi(m_ScanNo);

	unsigned long long atime = automationTimeOfScanPt;
	int _scanPtRow=-1;
	int _scanPtColumn=-1;
	iQLibIfPtr->getNearestScanPointFromAutomationTime(scanNo,atime,&_scanPtRow,&_scanPtColumn);

	resultScanPtCoords.Format("col:%d,row:%d",_scanPtColumn,_scanPtRow);

	UpdateData(false);
}

void CFAROOpenDemoAppDlg::OnBnClickedAutomationTest()
{

	UpdateData(true);

	int scanNo = atoi(m_ScanNo);

	int numberOfAutomationMessages = iQLibIfPtr->getNumAutomationMessages(scanNo);

	unsigned int canId,dh,dl;
	unsigned long long atime;

	for (int m=0;m<numberOfAutomationMessages;m++)
	{
		iQLibIfPtr->getAutomationMessage(scanNo,m,&atime,&canId,&dh,&dl);

		// get trigger for messages which had trigger before. E.g. setting time (canId=0x4)
		if (canId==0x4)
		{
			// get automation trigger previous to given time
			int triggerNrForMessage = iQLibIfPtr->getPreviousAutomationTrigger(scanNo,atime);

			if (triggerNrForMessage >= iQLibIfPtr->getNumAutomationTriggers(scanNo))
			{
				// not existent
				continue;
			}


			// get automation time of trigger
			unsigned long long atimeTrigger;
			iQLibIfPtr->getAutomationTriggerTime(scanNo,triggerNrForMessage,&atimeTrigger);
			
			// the exact time of trigger is atimeTrigger. This should be very close to
			// what was sent via CAN message.

			// convert the time which was sent in CAN:
			unsigned long long providedTime = dh;
			providedTime = (providedTime << 32) + dl;

			// then difference should be 0:
			long long diff = (long long)providedTime-(long long)atimeTrigger;

			// check if there is a message after a certain time:
			int nextMessageNr = iQLibIfPtr->getNextAutomationMessage(scanNo,atime);
			{
				if (nextMessageNr < numberOfAutomationMessages)
				{
					// we can retrive the message with getAutomationMessage()

				}
			}

			// check if there is a message prior a certain time:
			int prevMessageNr = iQLibIfPtr->getPreviousAutomationMessage(scanNo,atime);
			{
				if (prevMessageNr < numberOfAutomationMessages)
				{
					// we can retrive the message with getAutomationMessage()

				}
			}

			// next trigger would be:
			int nextTrigger = iQLibIfPtr->getNextAutomationTrigger(scanNo,atime);

		}
	}

	UpdateData(false);
}
