using namespace std;

#define debug                //Enables debug mode (Comment to disable)

#include "functions.h"
#include "CRCOpen.h"
#include "serverTCPIP.h"

int  main (int argc, char **argv)
{
  OPENSERVER_presentation(); //Print the presentation on the screen
  //startCRCOpen();            //Start communicating with the CRC
  TCPIP_open_connect();      //Open the connection TCP/IP

  while (true)
  {
    TCPIP_listen_mode();     //Wait in listen mode for someone to connect
    if(TCPIP_choose_mode())  //Main function: perform actions according to the user's choice
      break;                 //If it returns TRUE exit the structure
    else
      dprint("New Cicle");   //If it returns FALSE restart the process
    TCPIP_close_mode();      //Before restart the process, close the connection
  }

  close(listening);          //End the TCP/IP connection
  //stopCRCOpen();             //End the CRC connection

  return 0;                  //Return that was successful
}
