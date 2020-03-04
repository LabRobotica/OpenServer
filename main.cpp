// #define debug
#include "serverTCPIP.h"
#include "CRCOpen.h"

void OPENSERVER_presentation();

int  main (int argc, char **argv)
{
  OPENSERVER_presentation();
  startCRCOpen();

  TCPIP_open_connect();

  while (true)
  {
    TCPIP_listen_mode();
    if(TCPIP_choose_mode()) cout << "New Cicle" << endl;
    TCPIP_close_mode();
  }
  close(listening);
  stopCRCOpen();

  return 0;
}

void OPENSERVER_presentation()
{
  cout << "\t\t*----------------------------------*" << endl;
  cout << "\t\t|         -> OpenServer <-         |" << endl;
  cout << "\t\t|       Comau C5G-Open eORL        |" << endl;
  cout << "\t\t|   CEFET-MG Unidade Divinópolis   |" << endl;
  cout << "\t\t*----------------------------------*" << endl << endl;
}
