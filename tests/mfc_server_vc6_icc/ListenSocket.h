#if !defined(AFX_LISTENSOCKET_H__B0CFD192_A900_415C_81B7_F5C069D5B9AA__INCLUDED_)
#define AFX_LISTENSOCKET_H__B0CFD192_A900_415C_81B7_F5C069D5B9AA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ListenSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// ListenSocket command target
class ServeSocket;

class ListenSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	ListenSocket();
	virtual ~ListenSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ListenSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(ListenSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
   ServeSocket* sock;
   virtual void OnAccept(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LISTENSOCKET_H__B0CFD192_A900_415C_81B7_F5C069D5B9AA__INCLUDED_)
