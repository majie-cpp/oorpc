#include <windows.h>
#include <conio.h>
#include <iostream>
using namespace std;

extern void testClient();


int main(int argc, char* argv[])
{

   WORD wVersionRequested;
   WSADATA wsaData;
   int err;
 
   wVersionRequested = MAKEWORD( 2, 2 );
 
   err = WSAStartup( wVersionRequested, &wsaData );
   if ( err != 0 ) {
       /* Tell the user that we could not find a usable */
       /* WinSock DLL.                                  */
       return 0;
   }


   testClient();

   getchar();
	return 0;
}
