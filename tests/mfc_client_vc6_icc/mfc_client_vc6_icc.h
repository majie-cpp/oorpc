// mfc_client_vc6_icc.h : main header file for the MFC_CLIENT_VC6_ICC application
//

#if !defined(AFX_MFC_CLIENT_VC6_ICC_H__576307D5_5789_4B69_8FEB_F5C61B52153D__INCLUDED_)
#define AFX_MFC_CLIENT_VC6_ICC_H__576307D5_5789_4B69_8FEB_F5C61B52153D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CMfc_client_vc6_iccApp:
// See mfc_client_vc6_icc.cpp for the implementation of this class
//

class CMfc_client_vc6_iccApp : public CWinApp
{
public:
	CMfc_client_vc6_iccApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMfc_client_vc6_iccApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CMfc_client_vc6_iccApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFC_CLIENT_VC6_ICC_H__576307D5_5789_4B69_8FEB_F5C61B52153D__INCLUDED_)
