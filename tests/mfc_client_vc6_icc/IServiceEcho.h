#ifndef _ISERVICEECHO_H_
#define _ISERVICEECHO_H_

#include <string>
using namespace std;

#include "..\service_define_template.h"

class IServiceEcho
{
public:
   virtual void echo() = 0;
   virtual void echo1(string& str) = 0;

   virtual ~IServiceEcho() {}
};

BEGIN_DEFINE_SERVICE(IServiceEcho)
   EXPOSE_METHOD(IServiceEcho,echo)
   EXPOSE_METHOD(IServiceEcho,echo1)
END_DEFINE_SERVICE

#endif