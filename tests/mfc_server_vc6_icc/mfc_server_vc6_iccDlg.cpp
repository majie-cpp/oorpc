// mfc_server_vc6_iccDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mfc_server_vc6_icc.h"
#include "mfc_server_vc6_iccDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "IServiceEcho.h"
#include "socketTransportImpl.h"
#include "ServiceDriver.h"
#include "service_err.hpp"


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
// CMfc_server_vc6_iccDlg dialog

CMfc_server_vc6_iccDlg::CMfc_server_vc6_iccDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMfc_server_vc6_iccDlg::IDD, pParent), serveTrans(NULL), errCode(0),impl(&this->m_listCtrl),
   readSel(NULL), acceptSel(NULL)
{
	//{{AFX_DATA_INIT(CMfc_server_vc6_iccDlg)
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMfc_server_vc6_iccDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMfc_server_vc6_iccDlg)
	DDX_Control(pDX, IDC_LIST1, m_listCtrl);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CMfc_server_vc6_iccDlg, CDialog)
	//{{AFX_MSG_MAP(CMfc_server_vc6_iccDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
   ON_MESSAGE(TRANS_EVT, OnTransEvent )
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMfc_server_vc6_iccDlg message handlers

BOOL CMfc_server_vc6_iccDlg::OnInitDialog()
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
   listenTrans.bind("127.0.0.1:9999");
   this->acceptSel = 
      new AsyncSelector(listenTrans.getSocketHandle(), 
         TRANS_EVT, (unsigned int )this->m_hWnd, AsyncSelector::accept);
   this->acceptSel->Select();
   
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMfc_server_vc6_iccDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMfc_server_vc6_iccDlg::OnPaint() 
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
HCURSOR CMfc_server_vc6_iccDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMfc_server_vc6_iccDlg::addMessage(const CString& msg)
{
   
}

void CMfc_server_vc6_iccDlg::OnTransEvent(WPARAM wParam, LPARAM lParam)
{
if (lParam  == AsyncSelector::accept)
   {
      try {
         // Firstly close selector, then transportation
         if (readSel ) delete readSel, readSel = NULL;
         if (serveTrans ) delete serveTrans, serveTrans = NULL;         
         serveTrans = dynamic_cast<SocketTransportImpl *>(listenTrans.waitForConnect());
      }
      catch (ServiceException & ex)
      {
         AfxMessageBox(ex.what(),MB_ICONERROR);
         throw;
      }
      this->acceptSel->Select();
      
      this->readSel = new AsyncSelector(serveTrans->getSocketHandle(), 
            TRANS_EVT, (unsigned int)this->m_hWnd, AsyncSelector::read);
      this->readSel->Select();
      
   }
   else if (lParam  == AsyncSelector::read)
   {
      ServiceDriver<IServiceEcho> driver(impl);
      try
      {
         driver.serveOnce(*(dynamic_cast<IServerTransport*>(this->serveTrans)));
      }
      catch (ServiceException& ex)
      {
         if (readSel ) delete readSel, readSel = NULL;
         if (serveTrans ) delete serveTrans, serveTrans = NULL;
         
         if (ex.getErrCode() != WSAECONNRESET && ex.getErrCode() != R_PEER_DISCONNECTED)
         {
            CString tmp;
            tmp.Format("Socket error:%d",ex.getErrCode());
            AfxMessageBox(ex.what(),MB_ICONERROR);
            throw;
         }
         else
         {
            CString tmp;
            tmp.Format("Client disconnected.:%d",ex.getErrCode());
            AfxMessageBox(tmp);
         }
         return;
            
      }
      this->readSel->Select();

   }
   else
      ASSERT(0);
}

void CMfc_server_vc6_iccDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
   if (this->acceptSel)
      delete this->acceptSel;
   if (this->readSel )
      delete this->readSel;
   if (serveTrans ) 
      delete serveTrans;
	
}
