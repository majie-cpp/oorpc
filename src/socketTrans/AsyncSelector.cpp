#include "stdafx.h"
#include <Afxmt.h>

#include "AsyncSelector.h"
//#include <winsock2.h>

DWORD WINAPI select_proc( LPVOID lpParam ) ;

AsyncSelector::AsyncSelector (int socket, int msg, unsigned int wndHdl, EventType eventType)
   :_sock(socket), _wndMsg(msg), _wndHdl(wndHdl), _eventType(eventType)
{

   FD_ZERO(&rd);
   FD_ZERO(&wrt);
   FD_ZERO(&excp);

   switch (_eventType)
   {
   case  conn :
      FD_SET(_sock, &wrt);
      break;
   case  read :
      FD_SET(_sock, &rd);
      break;
   case  write :
      FD_SET(_sock, &wrt);
      break;
   case  accept:
      FD_SET(_sock, &rd);
      break;
   case  conn_err:
      FD_SET(_sock, &excp);
      break;
   default:
      break;
   }
   
   // Create automatically reset event with initial state as nonsignaled.
   _suspendEvt = CreateEvent(NULL,false,false,NULL);
   _exitEvt = CreateEvent(NULL,false,false,NULL);
   ASSERT(_suspendEvt);
   ASSERT(_exitEvt);


   DWORD dwThreadId;
   
   _hThread = CreateThread( 
        NULL,                        // default security attributes 
        100,                           // use default stack size  
        select_proc,                  // thread function 
        (void*)this,                // argument to thread function 
        0,                           // use default creation flags 
        &dwThreadId);                // returns the thread identifier 
 
   // Check the return value for success. 
   ASSERT(_hThread); 
}

void AsyncSelector::Select ()
{
   SetEvent(_suspendEvt);
}

AsyncSelector::~AsyncSelector ()
{
   SetEvent(_exitEvt);
   SetEvent(_suspendEvt);
   // Make sure the thread is terminated.
   WaitForSingleObject(_hThread, INFINITE);
   CloseHandle(_exitEvt);
   CloseHandle(_suspendEvt);
   CloseHandle(_hThread);


}

DWORD WINAPI select_proc( LPVOID lpParam ) 
{
   AsyncSelector *p = (AsyncSelector*) lpParam;

   while (true )
   {
      // Suspended for the next select().
      TRACE("Thread[0x%X]:Suspended.\n", GetCurrentThreadId());
      WaitForSingleObject(p->_suspendEvt,INFINITE);
      if (WaitForSingleObject(p->_exitEvt,0) == WAIT_OBJECT_0 )
      {
         TRACE("Thread[0x%X]:Get exit signal, terminating..\n",GetCurrentThreadId());
         return 0; // terminate the thread;
      }
      timeval tm;
      tm.tv_sec = 0;
      tm.tv_usec = 200;
      

      while (true)
      {
         // make a copy firstly.
         fd_set rd (p->rd),wrt(p->wrt),excp(p->excp) ;
         int ret  = select(0, &rd, &wrt, &excp, &tm);
         
         if (WaitForSingleObject(p->_exitEvt,0) == WAIT_OBJECT_0 )
         {
            TRACE("Thread[0x%X]:Get exit signal, terminating..\n",
               GetCurrentThreadId());
            return 0; // terminate the thread;
         }

         if (ret == 0 )
         {
            continue; // keep in inner loop. continue selecting;
         }
         else if ( ret > 0 )
         {
            TRACE("Thread[0x%X]:Receive socket event, sending message...\n",
               GetCurrentThreadId());
            if ( FD_ISSET(p->_sock, &excp ) )
            {
               // connect fail
               ASSERT(::PostMessage((HWND)p->_wndHdl, 
                  p->_wndMsg, 
                  p->_sock, 
                  AsyncSelector::conn_err));

            }
            else
                ASSERT(::PostMessage((HWND)p->_wndHdl, 
                  p->_wndMsg, 
                  p->_sock, 
                  p->_eventType));
            break; // Jump to outter loop

         }
         else if (ret == SOCKET_ERROR)
         {
            TRACE("Thread[0x%X]:selector thread calling select(..) failed, error code:%d\n", 
               GetCurrentThreadId(),WSAGetLastError());
            break; // Encountered error. Jump to outer loop. suspended. 
                   //can be resumed by re-calling to select()
         }
         else
            ASSERT(0);
      } // inner loop
   } // outer loop

   return 0;
}
