// mem_fun1.cpp : 定义控制台应用程序的入口点。
//

#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

extern DWORD WINAPI testServer( LPVOID lpParam ) ;
extern void testClient();

int main(int argc, char* argv[])
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
   getchar();
	return 0;
}

