#ifndef _TRANSPORT_HELPER_H
#define _TRANSPORT_HELPER_H

// The following byte converter wrapper is platform dependent and
// is impletmented in socketTransportImpl.
extern unsigned long _htonl (unsigned long);
extern unsigned short _htons (unsigned short);
extern unsigned long _ntohl (unsigned long);
extern unsigned short _ntohs (unsigned short);


class TransportHelper
{
public:
   template <class T> static T n2HByteOrder(T t)
   {
      return t;
   }
   template <class T> static T h2NByteOrder(T t)
   {
      return t;
   }

   /////////////////////////////////////////////////////////////
   //template <> 
   static int h2NByteOrder(int t)
   {
      return _htonl(t);
   }
   //template <> 
   static unsigned int h2NByteOrder(unsigned int t)
   {
      return _htonl(t);
   }

   //template <> 
   static long h2NByteOrder(long t)
   {
      return _htonl(t);
   }

   //template <> 
   static unsigned long h2NByteOrder(unsigned long t)
   {
      return _htonl(t);
   }

   //template <> 
   static short h2NByteOrder(short t)
   {
      return _htons(t);
   }
   //template <> 
   static unsigned short h2NByteOrder(unsigned short t)
   {
      return _htons(t);
   }

   

   ////////////////////////////////////////////////////////////
   //template <> 
   static int n2HByteOrder(int t)
   {
      return _ntohl(t);
   }
   //template <> 
   static unsigned int n2HByteOrder(unsigned int t)
   {
      return _ntohl(t);
   }
   //template <> 
   static long n2HByteOrder(long t)
   {
      return _ntohl(t);
   }
   //template <> 
   static unsigned long n2HByteOrder(unsigned long t)
   {
      return _ntohl(t);
   }
   //template <> 
   static short n2HByteOrder(short t)
   {
      return _ntohs(t);
   }
   //template <> 
   static unsigned short n2HByteOrder(unsigned short t)
   {
      return _ntohs(t);
   }
};



#endif
