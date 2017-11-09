#if !defined(AFX_SERVESOCKET_H__89D5C888_2CCA_4CA6_B863_004F4D90153F__INCLUDED_)
#define AFX_SERVESOCKET_H__89D5C888_2CCA_4CA6_B863_004F4D90153F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ServeSocket.h : header file
//



/////////////////////////////////////////////////////////////////////////////
// ServeSocket command target

class ServeSocket : public CSocket
{
// Attributes
public:

// Operations
public:
	ServeSocket();
	virtual ~ServeSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ServeSocket)
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(ServeSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
      virtual void OnReceive(int nErrorCode);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SERVESOCKET_H__89D5C888_2CCA_4CA6_B863_004F4D90153F__INCLUDED_)
