#define STRING_IP_CNTRL        "192.168.29.2"
#define STRING_SYS_ID          "CNTRLC5G_2213436"

#include <stdlib.h>
#include <stdio.h>
#include "/opt/inc/eORL.h"

int loop (){}

int  startCRCOpen (void)
{ 
    printf("Connection to %s: %s.c5g\n",STRING_IP_CNTRL, STRING_SYS_ID);

    printf("\n[F] ORLOPEN_initialize_controller\n");
    if( (ORLOPEN_initialize_controller(STRING_IP_CNTRL,STRING_SYS_ID,ORL_SILENT,ORL_CNTRL01)))
    {
        printf("error ORL_initialize_robot\n");
        exit(0);
    }
    else
        printf("%s: %s.c5g OK\n",STRING_IP_CNTRL, STRING_SYS_ID);
    
    printf("\n[F] ORLOPEN_set_period\n");
    ORLOPEN_set_period(ORL_16_0_MILLIS, ORL_VERBOSE, ORL_CNTRL01);
    
    printf("\n[F] ORLOPEN_SetCallBackFunction\n");
    ORLOPEN_SetCallBackFunction (&loop, ORL_SILENT, ORL_CNTRL01);
    
    printf("\n[F] ORLOPEN_StartCommunication\n");
    if (ORLOPEN_StartCommunication(ORL_SILENT))
    {
        printf("\n[F] ORLOPEN_GetPowerlinkState\n");
        ORLOPEN_GetPowerlinkState(ORL_SILENT);
        exit(0);
    }
    return 0;
}

int stopCRCOpen ()
{
    printf("\n[F] ORLOPEN_StopCommunication\n");
    ORLOPEN_StopCommunication(ORL_SILENT);
    
    printf("\n[F] ORL_terminate_controller\n");
    ORL_terminate_controller(ORL_SILENT,ORL_CNTRL01);
    return 0;
}