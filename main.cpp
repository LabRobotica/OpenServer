#define debug
#include "serverTCPIP.h"
//#include "CRCOpen.h"

void OPENSERVER_presentation();

int  main (int argc, char **argv)
{
  OPENSERVER_presentation();

  TCPIP_open_connect();

  while (true)
  {
    TCPIP_listen_mode();
    if(TCPIP_choose_mode()) break;
    TCPIP_close_mode();
    dprint("New Cycle"<<endl);
  }
  close(listening);

  return 0;
}

void OPENSERVER_presentation()
{
  cout << "------------------------------------" << endl;
  cout << "|         -> OpenServer <-         |" << endl;
  cout << "|       Comau C5G-Open eORL        |" << endl;
  cout << "|   CEFET-MG Unidade Divinópolis   |" << endl;
  cout << "------------------------------------" << endl << endl;
}