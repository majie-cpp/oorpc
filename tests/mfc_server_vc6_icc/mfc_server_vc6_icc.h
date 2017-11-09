// mfc_server_vc6_icc.h : main header file for the MFC_SERVER_VC6_ICC application
//

#if !defined(AFX_MFC_SERVER_VC6_ICC_H__4D0C201F_F299_4408_B8F7_81E6EE17433F__INCLUDED_)
#define AFX_MFC_SERVER_VC6_ICC_H__4D0C201F_F299_4408_B8F7_81E6EE17433F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfc_server_vc6_iccApp:
// See mfc_server_vc6_icc.cpp for the implementation of this class
//

class CMfc_server_vc6_iccApp : public CWinApp
{
public:
	CMfc_server_vc6_iccApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfc_server_vc6_iccApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMfc_server_vc6_iccApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFC_SERVER_VC6_ICC_H__4D0C201F_F299_4408_B8F7_81E6EE17433F__INCLUDED_)
