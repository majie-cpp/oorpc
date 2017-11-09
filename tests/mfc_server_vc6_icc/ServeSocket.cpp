// ServeSocket.cpp : implementation file
//

#include "stdafx.h"
#include "mfc_server_vc6_icc.h"
#include "ServeSocket.h"

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

#include "IServiceEcho.h"
#include "socketTransportImpl.h"
#include "ServiceDriver.h"
#include "service_err.hpp"


class IServiceEchoImpl: public IServiceEcho
{
public:
   virtual void echo()
   {
      //AfxMessageBox("echo() is invoked.");
   }
   virtual void echo1(string& str)
   {
      //AfxMessageBox(string(string("echo1() is invoked:") + str).c_str());
   }

   virtual ~IServiceEchoImpl() {}

};

/////////////////////////////////////////////////////////////////////////////
// ServeSocket

ServeSocket::ServeSocket()
{
}

ServeSocket::~ServeSocket()
{
}

void ServeSocket::OnReceive(int nErrorCode)
{
   CSocket::OnReceive(nErrorCode);

   SocketTransportImpl trans(this->m_hSocket);
   IServiceEchoImpl impl;
   ServiceDriver<IServiceEcho> driver(impl,trans);
   try
   {
      driver.serveOnce(dynamic_cast<IServerTransport&>(trans));
   }
   catch (ServiceException& ex)
   {
      AfxMessageBox(ex.what());
   }

   TRACE("ServerSocket::OnReveive\n");

}

// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(ServeSocket, CSocket)
	//{{AFX_MSG_MAP(ServeSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// ServeSocket member functions
