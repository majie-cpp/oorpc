// mfc_client_vc6_iccDlg.h : header file
//

#if !defined(AFX_MFC_CLIENT_VC6_ICCDLG_H__BA064052_8EDA_4E2F_9333_55F74A3E0ED2__INCLUDED_)
#define AFX_MFC_CLIENT_VC6_ICCDLG_H__BA064052_8EDA_4E2F_9333_55F74A3E0ED2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
// CMfc_client_vc6_iccDlg dialog
#include "socketTransportImpl.h"

class CMfc_client_vc6_iccDlg : public CDialog
{
// Construction
public:
	CMfc_client_vc6_iccDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CMfc_client_vc6_iccDlg)
	enum { IDD = IDD_MFC_CLIENT_VC6_ICC_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfc_client_vc6_iccDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

   SocketTransportImpl trans;

	// Generated message map functions
	//{{AFX_MSG(CMfc_client_vc6_iccDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnButtonInvoke();
	afx_msg void OnButtonInvoke0();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFC_CLIENT_VC6_ICCDLG_H__BA064052_8EDA_4E2F_9333_55F74A3E0ED2__INCLUDED_)
