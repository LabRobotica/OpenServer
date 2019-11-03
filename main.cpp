#define debug

#include "serverTCPIP.h"
//#include "CRCOpen.h"

int  main (void) //(int argc, char **argv)
{
  TCPIP_listen_mode();
  while (true)
  {
    if(TCPIP_mirror_mode()) break;
  }
  TCPIP_close_mode();  

  //startCRCOpen();
  //stopCRCOpen();
  return 0;
}
 