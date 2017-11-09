

#include "serviceDef.h"
#include "proxy.hpp"

#include "ServiceDriver.h"
#include "service_err.hpp"

//#include "transport.hpp"
#include "socketTransportImpl.h"
#include <iostream>

// For mem leak detection
/*
#define _CRTDBG_MAP_ALLOC 
#include <stdlib.h>
#include <crtdbg.h>
*/
class TestArgImpl: public TestArg
{
public:
   virtual void Serialize(CPstream& ar)
   {
      TestArg::Serialize(ar);
      
      if (ar.isLoading())
         ar >> _argStr;
      else
         ar << _argStr;
   }
public:
   TestArgImpl(): _argStr("000000000"){}
   virtual void doSomething()
   {
      std::cout<<"* Changing the member _argStr to 123456789."<<std::endl;
      _argStr = "123456789";
   }
   virtual void show() { std::cout<<"* TestArgImpl member: _argStr = "<< _argStr.data()<<std::endl;}
private:
   std::string _argStr;

   declare_serial(TestArgImpl)
};

class TestInterfaceImpl: public TestInterface
{
public:
   TestInterfaceImpl():_str(""){}
   virtual std::string& echo(std::string& str) 
   {
      std::cout<<"[Server], std::string& echo(std::string& str): "<<endl;
      cout<<"...param1:"<<str<<std::endl;
      _str = str;
      str = "莫";
      cout<<"param1= 莫"<<endl;
      
      cout<<"...returned:"<<string(_str+"1234").c_str()<<endl;
      return *new string(_str+"1234");
   }

   virtual void echo1(TestArg& testArg) 
   { 
      std::cout<<"[Server],void echo1(TestArg& testArg):"<<endl;
      cout<<"...invoke virtual void show()....output:"<<endl;
      testArg.show();
      std::cout<<"...invoke doSomething()....output:"<<endl;
      testArg.doSomething();
   }

   virtual string echo2 ( string str)
   {
      cout<<"echo2(): received input string:"<<str.c_str()<<endl;
      cout<<"echo2(): Return string value type: 你好7777"<<endl;
      return "你好7777";
   }

   virtual TestArg1 echo3()
   {
      TestArg1 arg1;

      arg1.ll = 2222;
      return arg1;
   }

   double echo4 (unsigned long & ll, float& ff)
   {
      cout<<"echo4(): received param1 = "<<ll<<", param2 = "<<ff<<endl;
      cout<<"echo4(): changed param1 to 3333, param2 to 0.9999, returned value: 0.7777"<<endl;
      ll = 3333;
      ff = 0.9999;
      return 0.7777;
   }

   virtual char* echo5 (char * cp, int * ip, char  cc)
   {
      cout<<"[Server]: short echo5 (char * cp, int * ip, char & cc):"<<endl;
      cout<<"...param1:"<<cp<<",param2:"<<*ip<<",param3:"<<cc;
      cout<<"...Changed param1[0] to \'A\'."<<endl;
      string tmp(cp, strlen(cp));
      tmp.at(0) = 'A';
      strncpy(cp,tmp.data(),tmp.size());
      
      cout<<"...Changed param1[1] to 123'."<<endl;
      *ip = 123;
      cout<<"...Changed param1[2] to \'X\'."<<endl;
      cc = 'X';

      char * retStr = new char[100];
      strcpy(retStr,"你好，世界！");
      return retStr;
   }

   virtual double * echo6(float* ff, TestArg1 arg, unsigned short* ss, long* ll)
   {
      cout<<"[Server]:ouble * echo6(float* ff, TestArg1 arg, unsigned short* ss, long* ll):"<<endl;
      cout<<"...param0:"<<*ff<<",param1 (TestArg::ll):"<<arg.ll<<",param2:"<<*ss<<",param3:"<<*ll;

      *ff = 99.99;
      arg.ll = 999;
      *ss = 99;
      *ll = 9999;
      cout<<"...Changed value:  *ff = 99.99, arg.ll = 999, *ss = 99, *ll = 9999"<<endl;
      cout<<"...Returned: 88.88"<<endl;
      return new double(88.88);
   }
   virtual double * echo7(float* ff, TestArg1 arg, unsigned short* ss, long* ll, string& str1)
   {
      cout<<"[Server]: double * echo7(float* ff, TestArg1 arg, unsigned short* ss, long* ll, string& str1):"<<endl;
      cout<<"...param4:"<<str1.c_str()<<endl;
      return echo6(ff,arg,ss,ll);
   }
   virtual TestArg * echo8(float* ff, TestArg1 arg, unsigned short* ss, long* ll, string& str1, bool* bb)
   {
      cout<<"[Server]: double * echo8(float* ff, TestArg1 arg, unsigned short* ss, long* ll, string& str1, bool* bb):"<<endl;
      cout<<"...param5:"<<*bb<<endl;
      cout<<"...Change param5 to false."<<endl;
      *bb = false;
      return NULL;
   }
   virtual TestArg& echo9(float* ff, TestArg1 arg, unsigned short* ss, long* ll, string& str1, string& str2, bool bb)
   {
      cout<<"[Server]:double * echo9(float* ff, TestArg1 arg, unsigned short* ss, long* ll, string& str1, string& str2, bool bb):"<<endl;
      cout<<"[Server]: param0="<<(ff?*ff:0.0)<<",param1: TestArg1("<<arg.ll<<"),param2:"<<(ss?*ss:0)
         <<",param3:"<<(ll?*ll:0)<<",param4:"
         <<str1<<",param5:"<<str2<<",param6:"<<bb<<endl;
      return *(new TestArgImpl);
   }
   virtual double* echo10(float* ff, TestArg1 arg, unsigned short* ss, long* ll, string* str, string& str2, int & ii, TestArg* bb)
   {
         cout<<"[Server]:"<<endl;
         cout<<"...float ff = "<<*ff<<endl;
         cout<<"...unsigned short *ss = "<<*ss<<endl;
         cout<<"...TestArg1 arg="<<arg.ll<<endl;
         cout<<"...long ll = "<<*ll<<endl;
         cout<<"...string str = "<<*str<<endl;
         cout<<"...string str2 = "<<str2<<endl;
         cout<<"...int ii = "<<ii<<endl;
         cout<<"...TestArg* arg = "<<endl;
         bb->show();
         bb->doSomething();

         cout<<"...Changed str to \"uuuu\""<<endl;
         *str = "uuuu";

         return new double(66.66);
   }


   virtual ~TestInterfaceImpl(){}
private:
   std::string _str;


};



implement_serial(TestArg)
implement_serial(TestArgImpl)
implement_serial(TestArg1)

void TestArg1::Serialize(CPstream& ar)
{
   if (ar.isLoading())
      ar >> ll;
   else
      ar << ll;
}
//BOOST_CLASS_EXPORT_GUID(TestArgImpl, "TestArgImpl")

void testClient()
{
   
   string *strr = NULL, *strr1;
   char * chp = NULL, *chp1;
   double ddd1 = 99.99, *ddd1p, *ddd2p = NULL;
   CPstream ostrm;
   ostrm << strr<<ddd2p<<chp;
   CPstream istrm (ostrm);
   istrm >> strr1>>ddd1p>>chp1;
   

   SocketTransportImpl trans;

   Proxy<TestInterface> proxy(trans);

   std::string echoStr = "Hello.";
   std::string& echoStrRef(echoStr);
   try {
      trans.connect("127.0.0.1:999");
   }
   catch( ServiceException& ex)
   {
      cout<<ex.what()<<endl;
      return;
   }

   try 
   {
      int cnt = 0;
      while(true) {
     
         std::cout<<"=========== Invoking echo ====================="<<endl;
      
         std::string str("ABCDE");
         string &retStr = proxy.invoke(&TestInterface::echo)(str);
         std::cout<<"[Client]: received returned:"<<retStr.c_str()<<endl;
         std::cout<<"[Client]: param1="<<str.c_str()<<endl;

         delete & retStr ; // reference to locally allocated obj, it's invoker's responsibility to release.
      
      
         std::cout<<"=========== Invoking echo1 ====================="<<endl;
         TestArgImpl argImpl;
         cout<<"[Client]: proxy.invoke(&TestInterface::echo1)(argImpl):"<<endl;
         proxy.invoke(&TestInterface::echo1)(argImpl);
         cout<<"[Client]: argImpl.show() after invoking:"<<endl;
         argImpl.show(); 

         std::cout<<"=========== Invoking echo2 ====================="<<endl;
         string str1 = proxy.invoke(&TestInterface::echo2)("6666");
         cout<<"[Cleint]: proxy.invoke(&TestInterface::echo2)(\"6666\");"<<endl;
         cout<<"[Client]: received returned string:"<<str1<<endl;
      

         std::cout<<"=========== Invoking echo3 ====================="<<endl;
         TestArg1 arg1 =  proxy.invoke(&TestInterface::echo3)();
         cout<<"Cleint received returned TestArg1, ll = :"<<arg1.ll<<endl;

         std::cout<<"=========== Invoking echo4 ====================="<<endl;
         unsigned long ll = 1111;
         float ff = 0.7777;
         cout<<"Client: Invoking echo4() with param1:"<<ll<<",param2:"<<ff<<endl;
         double dd =  proxy.invoke(&TestInterface::echo4)(ll,ff);
         cout<<"Cleint: received returned double val :"<<dd<<endl;
         cout<<"Client: param1:"<<ll<<",param2:"<<ff<<endl;

         std::cout<<"=========== Invoking echo5 ====================="<<endl;
      
         string tmpstr ("床前明月光");
         char * cp = (char*)tmpstr.c_str();
      
         int ii = 777;
         char cc = 'A';
         char* sret = proxy.invoke(&TestInterface::echo5)(cp,&ii,cc);
         cout<<"[Client]: param0:"<<cp<<endl;
         cout<<"[Client]: param1:"<<ii<<",param2:"<<cc<<endl;
         cout<<"[Client]: returned:"<<sret<<endl;

         delete [] sret;
     
         std::cout<<"=========== Invoking echo6 ====================="<<endl;
         {
            float ff = 11.11;
            unsigned short ss = 111;
            long ll = 1111;
            cout<<"[Client]: param0=11.11, param1=TestArg1(11), param2=111, param3=1111"<<endl;
            double *pp = proxy.invoke(&TestInterface::echo6)(& ff, TestArg1(11), &ss, & ll);
            cout<<"[Client]: after invoking, param0="<<ff<<",param2="<<ss<<",param3="<<ll<<endl;
            cout<<"[Client]: returned:"<<*pp<<endl;
            delete pp;
         }     

         std::cout<<"=========== Invoking echo7 ====================="<<endl;
         {
            float ff = 11.11;
            unsigned short ss = 111;
            long ll = 1111;
            string str = "床前明月光";
            cout<<"[Client]: param0=11.11, param1=TestArg1(11), param2=111, param3=1111, param4="<<str.c_str()<<endl;
            double *pp = proxy.invoke(&TestInterface::echo7)(& ff, TestArg1(11), &ss, & ll, str);
            cout<<"[Client]: after invoking, param0="<<ff<<",param2="<<ss<<",param3="<<ll<<endl;
            cout<<"[Client]: returned:"<<*pp<<endl;
            delete pp;
         }   

         std::cout<<"=========== Invoking echo8 ====================="<<endl;
         {
            float ff = 11.11;
            unsigned short ss = 111;
            long ll = 1111;
            string str = "床前明月光";
            bool bb = true;
            cout<<"[Client]: param0=11.11, param1=TestArg1(11), param2=111, param3=1111, param4="
               <<str.c_str()<<",param5="<<bb<<endl;
            TestArg *pp = proxy.invoke(&TestInterface::echo8)(& ff, TestArg1(11), &ss, & ll, str, &bb);
            cout<<"[Client]: after invoking, param0="<<ff<<
               ",param2="<<ss<<",param3="<<ll<<",param4:"<<str<<",param5:"<<(bb?"true":"false")<<endl;
            cout<<"[Client]: returned:"<<endl;
            if (pp)
            {
               pp->show();
               delete pp;
            }
            else
               cout<<"[Client]: Received NULL return value"<<endl;
         }   

         std::cout<<"=========== Invoking echo9 ======================"<<endl;
         {
            string str1 = "aaaa";
            string str2 = "bbbb";
            cout<<"[Client]: param0=null, param1=TestArg1(22), param2=null, param3=null,param4=\"aaaa\", param5=\"bbbb\", param6=true"<<endl;
            TestArg & ret = proxy.invoke(&TestInterface::echo9)(NULL, TestArg1(22), NULL,NULL, str1, str2, true);        
            ret.show();
            delete & ret;
         }

         {
            cout <<"=========== Invoking echo10 ======================"<<endl;

            float ff = 11.11;
            unsigned short ss = 11;
            TestArg1 arg1(99);
            long ll = 1111;
            string str = "ssss"; 
            string str2 = "ssss2";
            int ii = 2222;
            TestArgImpl * arg = new TestArgImpl;

            cout<<"[Client]:"<<endl;
            cout<<"...float ff = 11.11;"<<endl;
            cout<<"...unsigned short ss = 11;"<<endl;
            cout<<"...TestArg1 arg1(99);"<<endl;
            cout<<"...long ll = 1111;"<<endl;
            cout<<"...string str = \"ssss\"; "<<endl;
            cout<<"...string str2 = \"ssss2\";"<<endl;
            cout<<"...int ii = 2222;"<<endl;
            cout<<"...TestArgImpl * arg = new TestArgImpl;"<<endl;

            double *dd = proxy.invoke(&TestInterface::echo10)(&ff, arg1, &ss, &ll, 
               &str, str2, ii, arg);
         
            cout<<"[Client]:"<<endl;
            cout<<"...float ff = "<<ff<<endl;
            cout<<"...unsigned short ss = "<<ss<<endl;
            cout<<"...TestArg1 arg1(99)="<<arg1.ll<<endl;
            cout<<"...long ll = "<<ll<<endl;
            cout<<"...string str = "<<str<<endl;
            cout<<"...string str2 = "<<str2<<endl;
            cout<<"...int ii = "<<ii<<endl;
            cout<<"...TestArgImpl * arg = "<<endl;
            arg->show();

            cout<<"...Returned value:"<<*dd<<endl;
            delete dd;
            delete arg;
         }
      
         getchar();
      }

   } // try block ends
   catch (ServiceException& ex)
   {
      if (ex.getErrCode() == R_PEER_DISCONNECTED )
         cout<<"Detected server disconnected."<<endl;
      else
         cout<<"Client error:"<<ex.what()<<endl;
   }

   //_CrtDumpMemoryLeaks();

}

#include <windows.h>
DWORD WINAPI testServer( LPVOID lpParam ) 
{

   TestInterfaceImpl impl;
   SocketTransportImpl trans;
   ServiceDriver<TestInterface> driver(impl);
   std::cout<<"* Server started, serving...."<<std::endl;
   
   try
   {
      trans.bind("127.0.0.1:999");      
      ITransport* recvTrans = trans.waitForConnect() ;
      while(true) 
         driver.serveOnce(*recvTrans);
  
   }
   catch (ServiceException& ex)
   {
      if (ex.getErrCode() == R_PEER_DISCONNECTED )
         cout<<"Detected client disconnected."<<endl;
      else
         cout<<"Server error:"<<ex.what()<<endl;
   }

   return 0;
}
