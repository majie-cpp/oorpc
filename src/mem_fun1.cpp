// mem_fun1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <boost/mem_fn.hpp>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

using namespace boost;
using namespace std;

//#define POLY


#include <strstream>


using namespace boost;







#include <windows.h>
#include <conio.h>

extern DWORD WINAPI testServer( LPVOID lpParam ) ;
extern void testClient();


#include <boost/type_traits/is_polymorphic.hpp>


int _tmain(int argc, _TCHAR* argv[])
{


   

   //////////////////////////////////////////////////////////////////////////////
   
   WORD wVersionRequested;
   WSADATA wsaData;
   wVersionRequested = MAKEWORD( 2, 2 );
   int err = WSAStartup( wVersionRequested, &wsaData );
   if ( err != 0 ) {
       return 0;
   }


   DWORD dwThreadId, dwThrdParam = 1; 
    HANDLE hThread; 

    hThread = CreateThread( 
        NULL,                        // default security attributes 
        0,                           // use default stack size  
        testServer,                  // thread function 
        &dwThrdParam,                // argument to thread function 
        0,                           // use default creation flags 
        &dwThreadId);                // returns the thread identifier 
 
   // Check the return value for success. 
 
   if (hThread == NULL) 
   {
      cout<< "testServer failed."; 
   }
   cout<<"Press any key to invoke server."<<endl;

   testClient();


   getchar();
	return 0;
}

