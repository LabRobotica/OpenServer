#include "functions.h"
#include "serverTCPIP.h"
#include "CRCOpen.h"


int  main (int argc, char **argv)
{
  OPENSERVER_presentation();
  startCRCOpen();
  TCPIP_open_connect();

  while (true)
  {
    TCPIP_listen_mode();
    if( TCPIP_choose_mode() ) {dprint("New Cicle");}
    else break;
    TCPIP_close_mode();
  }

  close(listening);
  stopCRCOpen();

  return 0;
}
