#ifndef __SOCKET_TRANSPORT_IMPL_H
#define __SOCKET_TRANSPORT_IMPL_H

#include "service_err.hpp"
#include "transport.hpp"

#define DEFAULT_SERVER_PORT 4044
#define PORT_SEP            ':'

class SocketTransportImpl: public IServerTransport,public IClientTransport
{
public:
   SocketTransportImpl();
   ~SocketTransportImpl();
   virtual void send(char * buf, int size) throw(ServiceException);
   virtual void recv(std::string &outBuf ) throw(ServiceException);
   // client side
   virtual void connect(const std::string& serverAddress) throw(ServiceException);
   // server side
   virtual ITransport* waitForConnect() throw(ServiceException);
   virtual void bind(const std::string& bindAddress) throw(ServiceException);

   virtual void close() throw(ServiceException);
   inline virtual int getLastErrorCode() { return _lastErr;}

   SocketTransportImpl(int newSock);
   inline int getSocketHandle() { return _sock; }
private:
   std::pair<std::string,short> parseAddr(const std::string& addrStr);
   int _sock;
   int _lastErr;
   bool _attachedSock;
};


#endif