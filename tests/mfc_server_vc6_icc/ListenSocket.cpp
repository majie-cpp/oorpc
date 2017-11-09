// ListenSocket.cpp : implementation file
//

#include "stdafx.h"
#include "mfc_server_vc6_icc.h"
#include "ListenSocket.h"
#include "Servesocket.h"

//
// The following lines have to be commented.
//
/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

#include <string>
#include "IServiceEcho.h"
#include "socketTransportImpl.h"
#include "ServiceDriver.h"
#include "service_err.hpp"

/////////////////////////////////////////////////////////////////////////////
// ListenSocket

ListenSocket::ListenSocket(): sock(NULL)
{
}

ListenSocket::~ListenSocket()
{
   delete sock;
}

void ListenSocket::OnAccept(int nErrorCode)
{
   CSocket::OnAccept(nErrorCode);
   sock = new ServeSocket;
   this->Accept(*sock);
}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(ListenSocket, CSocket)
	//{{AFX_MSG_MAP(ListenSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// ListenSocket member functions
