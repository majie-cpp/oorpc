#ifndef _ASYNC_SELECTOR_H
#define _ASYNC_SELECTOR_H


class AsyncSelector
{
public:
   typedef enum {
      conn     = 1,
      read     ,
      write    ,
      accept   ,
      conn_err 
   } EventType;
public:
   AsyncSelector (int socket, int msg, unsigned int wndHdl, EventType eventType);
   void Select ();

   ~AsyncSelector ();
private:
   int _sock;
   int _wndMsg;
   unsigned int _wndHdl;
   EventType _eventType;
   HANDLE _hThread;

   HANDLE _suspendEvt;
   HANDLE _exitEvt;

   fd_set rd,wrt,excp;
   
   friend DWORD WINAPI select_proc( LPVOID lpParam ) ;
};

#endif