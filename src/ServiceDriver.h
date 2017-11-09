#ifndef __SERVICE_H
#define __SERVICE_H


#include "socketTransportImpl.h"

template<class Service>
class ServiceDriver
{
public:
   ~ServiceDriver() {}
   ServiceDriver(Service & service) 
      : _service(service) {}
   
   void serveOnce(ITransport & trans)
   {
      CPstream oa;

      std::string recvBuf;
      
      trans.recv(recvBuf);

      CPstream iar((char*)recvBuf.data(),recvBuf.length());

      while(true)
      {
         // De-Serialize service name
         std::string svrName;
         iar >> svrName;
			int ret;

         if ( svrName != _serviceDef.getServiceName() )
         {
            ret = R_INVALID_SERVICE_NAME;
			   oa << ret;
            break;
         }

         // De-Serialize method id
         int svrId;
         iar >> svrId;

         IServiceMethod<Service> * method = _serviceDef.getMethodById(svrId);
         if (method == NULL)
         {
            ret = R_INVALID_METHOD_ID;
			   oa << ret;
            break;
         }
			ret = R_OK;
         oa << ret;
         method->dispatch(_service, iar, oa);
         break;
      }

      trans.send(oa.buf(), oa.bufSize());
   }
   
private:
    ServiceDefinition<Service> _serviceDef;
    Service & _service;
};


#endif