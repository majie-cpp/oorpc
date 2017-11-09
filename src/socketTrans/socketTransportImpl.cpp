#include "transport.hpp"
#include "socketTransportImpl.h"
#include  <string>
#include <Winsock2.h>
#include "transporthelper.h"

SocketTransportImpl::SocketTransportImpl() : _lastErr(0),_attachedSock(false)
{
   _sock = socket(AF_INET, SOCK_STREAM, 0);
}
SocketTransportImpl::~SocketTransportImpl()
{
   if (! _attachedSock)
      ::closesocket(_sock);
}

SocketTransportImpl::SocketTransportImpl(int newSock) : _sock(newSock), _lastErr(0), _attachedSock(true){}

void SocketTransportImpl::send(char * buf, int size) throw(ServiceException)
{
   if (_sock == INVALID_SOCKET )
      throw ServiceException("Transport: Invalid socket handler");

   fd_set writefd;
   FD_ZERO(&writefd);
   FD_SET(_sock, &writefd);
   if ( select(0,0,&writefd,0,0) == SOCKET_ERROR )
      throw ServiceException("Transport: checking writability failed", WSAGetLastError());

   // Send data size.
   int ret = ::send(_sock,(const char*)&size,sizeof(int),0);
   if (ret == SOCKET_ERROR )
      throw ServiceException("Transport: socket sending failed", WSAGetLastError());

   FD_ZERO(&writefd);
   FD_SET(_sock, &writefd);
   if ( select(0,0,&writefd,0,0) == SOCKET_ERROR )
      throw ServiceException("Transport: checking writability failed", WSAGetLastError());

   ret = ::send(_sock,buf,size,0);
   if (ret == SOCKET_ERROR )
      throw ServiceException("Transport: socket sending failed", WSAGetLastError());

}
void SocketTransportImpl::recv(std::string &outBuf ) throw(ServiceException)
{
   if (_sock == INVALID_SOCKET )
      throw ServiceException("Transport: Invalid socket handler");

   // If the peer closes gracefully, recv receives 0 byte, 
   // otherwise recv returns with SOCKET_ERROR, and error code is: WSAECONNRESET(10054) 
   int size = 0;
   int ret = ::recv(_sock,(char*)&size,sizeof(int),0);
   if ( ret != sizeof(int) || ret == SOCKET_ERROR )
   {
      if ( ret == SOCKET_ERROR )
         throw ServiceException("Transport: socket recv failed",WSAGetLastError());
      else
         throw ServiceException("Transport: recv: Peer disconnected.", R_PEER_DISCONNECTED);
         
   }

   char * buf = new char[size];
   ret = ::recv(_sock,buf,size,0);
   if ( ret != size || ret == SOCKET_ERROR )
   {
      delete [] buf;
      if ( ret == SOCKET_ERROR )
         throw ServiceException("Transport: socket recv failed",WSAGetLastError());
      else
         throw ServiceException("Transport: recv: Peer disconnected.", R_PEER_DISCONNECTED);
         
   }

   outBuf.append(buf,size);
   delete [] buf;

}
void SocketTransportImpl::connect(const std::string& serverAddress) throw(ServiceException)
{
   if (_sock == INVALID_SOCKET )
      throw ServiceException("Transport: Invalid socket handler");

   // parse the input address firstly.
   std::pair<std::string,short> addr = parseAddr(serverAddress);

   struct sockaddr_in serv_addr;
   memset(&serv_addr, 0, sizeof(struct sockaddr_in));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_port = htons(addr.second);
   serv_addr.sin_addr.s_addr = inet_addr(addr.first.c_str());

   if ( ::connect(_sock, (const sockaddr*)&serv_addr, sizeof(serv_addr)) == SOCKET_ERROR )
      throw ServiceException("Transport: socket connect failed",WSAGetLastError());

}
void SocketTransportImpl::bind(const std::string& bindAddress) throw(ServiceException)
{
   struct sockaddr_in serv_addr;

   if (_sock == INVALID_SOCKET )
      throw ServiceException("Transport: Invalid socket handler");

   std::pair<std::string,short> addr = parseAddr(bindAddress);

   memset((char *) &serv_addr, 0, sizeof(serv_addr));
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = inet_addr(addr.first.c_str());
   serv_addr.sin_port = htons(addr.second);
   int ret = ::bind(_sock, (struct sockaddr *) &serv_addr,
            sizeof(serv_addr));
   if (ret  == SOCKET_ERROR) 
      throw ServiceException("Transport: socket bind failed",WSAGetLastError());

   if (::listen(_sock,SOMAXCONN) == SOCKET_ERROR )
      throw ServiceException("Transport: socket listening failed",WSAGetLastError());

}
ITransport* SocketTransportImpl::waitForConnect() throw(ServiceException)
{
   struct sockaddr_in cli_addr;


   int clilen = sizeof(cli_addr);

   SOCKET newsockfd = accept(_sock, 
               (struct sockaddr *) &cli_addr, 
               &clilen);
   if (newsockfd == INVALID_SOCKET) 
      throw ServiceException("Transport: socket accept failed",WSAGetLastError());

   return (IServerTransport*) new SocketTransportImpl(newsockfd);
}

void SocketTransportImpl::close() throw(ServiceException)
{
   if (_sock != INVALID_SOCKET)
      closesocket(_sock);
}

std::pair<std::string,short> SocketTransportImpl::parseAddr(const std::string& addrStr)
{
   int pos = addrStr.find(PORT_SEP);
   if (pos == std::string::npos) 
   {
      return std::pair<std::string,short> (addrStr.substr(0,pos),DEFAULT_SERVER_PORT);
   }
   else
   {
      std::string portStr = addrStr.substr(pos+1);
      short port = atoi(portStr.c_str());
      if (port <=0 ) port = DEFAULT_SERVER_PORT;
      return std::pair<std::string,short> (addrStr.substr(0,pos),port);
   }

}


////////////////////////////////////////////////////
//  Network to host byte order converter
//

unsigned long _htonl (unsigned long l)
{
   return htonl(l);
}
unsigned short _htons (unsigned short s)
{
   return htons(s);
}
unsigned long _ntohl (unsigned long l)
{
   return ntohl(l);
}
unsigned short _ntohs (unsigned short s)
{
   return ntohs(s);
}