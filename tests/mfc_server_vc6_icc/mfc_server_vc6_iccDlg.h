// mfc_server_vc6_iccDlg.h : header file
//

#if !defined(AFX_MFC_SERVER_VC6_ICCDLG_H__DFD263F7_FF03_420E_AD7A_C51846394635__INCLUDED_)
#define AFX_MFC_SERVER_VC6_ICCDLG_H__DFD263F7_FF03_420E_AD7A_C51846394635__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMfc_server_vc6_iccDlg dialog

#include "SocketTransportImpl.h"
#include "IServiceEcho.h"
#include "AsyncSelector.h"

#define TRANS_EVT WM_USER + 100

class IServiceEchoImpl: public IServiceEcho
{
public:
   IServiceEchoImpl(CListBox * list): _list(list){}
   virtual void echo()
   {
      _list->InsertString(0,"echo is invoked.\n");
   }
   virtual void echo1(string& str)
   {
      CString cstr;
      cstr.Format("echo1() is invoked:%s\n",str.c_str());
      _list->InsertString(0,cstr);
   }

   virtual ~IServiceEchoImpl() {}
private:

   CListBox * _list;

};

class CMfc_server_vc6_iccDlg : public CDialog
{
// Construction
public:
	CMfc_server_vc6_iccDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMfc_server_vc6_iccDlg)
	enum { IDD = IDD_MFC_SERVER_VC6_ICC_DIALOG };
	CListBox	m_listCtrl;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfc_server_vc6_iccDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

   void addMessage(const CString& msg);
   
// Implementation
protected:
	HICON m_hIcon;

   //ListenSocket listenSock;
   SocketTransportImpl listenTrans;
   SocketTransportImpl * serveTrans;
   int errCode;
   IServiceEchoImpl impl;
   AsyncSelector *acceptSel, *readSel;

   void OnTransEvent(WPARAM wParam, LPARAM lParam);

	// Generated message map functions
	//{{AFX_MSG(CMfc_server_vc6_iccDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};




//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFC_SERVER_VC6_ICCDLG_H__DFD263F7_FF03_420E_AD7A_C51846394635__INCLUDED_)
