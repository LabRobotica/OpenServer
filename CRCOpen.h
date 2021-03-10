#ifndef CRCOPEN_H
#define CRCOPEN_H

#include <memory>

#define STRING_IP_CNTRL        "192.168.29.2"
#define STRING_SYS_ID          "CNTRLC5G_2213436"

extern "C"
{
    #include "eORL.h"
}

auto angle = std::shared_ptr <ORL_joint_value>        (new ORL_joint_value);
auto posi  = std::shared_ptr <ORL_cartesian_position> (new ORL_cartesian_position);

/*
int loop (int a)
{
    auto sx_joint_pos = std::shared_ptr <ORL_joint_value>        (new ORL_joint_value);
    auto sx_cart_pos  = std::shared_ptr <ORL_cartesian_position> (new ORL_cartesian_position);

    ORLOPEN_get_pos_measured (sx_joint_pos.get(), sx_cart_pos.get(), 0, ORL_SILENT, ORL_CNTRL01, 0);

    angle = sx_joint_pos;
    posi  = sx_cart_pos;
}

int  startCRCOpen (void)
{ 
    dprint("Try connection to" << STRING_IP_CNTRL << ": " << STRING_SYS_ID << ".c5g\n");

    dprint("\n[F] ORLOPEN_initialize_controller\n");
    if( ORLOPEN_initialize_controller(STRING_IP_CNTRL, STRING_SYS_ID, ORL_SILENT, ORL_CNTRL01) )
    {
        dprint("error ORL_initialize_robot\n");
        exit(0);
    }
    else
        printf("%s: %s.c5g OK\n", STRING_IP_CNTRL, STRING_SYS_ID);
        dprint("The connection to" << STRING_IP_CNTRL << ": " << STRING_SYS_ID << ".c5g is OK!\n");
    
    dprint("\n[F] ORLOPEN_set_period\n");
    ORLOPEN_set_period(ORL_16_0_MILLIS, ORL_VERBOSE, ORL_CNTRL01);
    
    dprint("\n[F] ORLOPEN_SetCallBackFunction\n");
    ORLOPEN_SetCallBackFunction (&loop, ORL_SILENT, ORL_CNTRL01);
    
    dprint("\n[F] ORLOPEN_StartCommunication\n");
    if (ORLOPEN_StartCommunication(ORL_SILENT))
    {
        dprint("\n[F] ORLOPEN_GetPowerlinkState\n");
        ORLOPEN_GetPowerlinkState(ORL_SILENT);
        exit(0);
    }
    return 0;
}

int stopCRCOpen ()
{
    dprint("\n[F] ORLOPEN_StopCommunication\n");
    ORLOPEN_StopCommunication(ORL_SILENT);
    
    dprint("\n[F] ORL_terminate_controller\n");
    ORL_terminate_controller(ORL_SILENT,ORL_CNTRL01);
    return 0;
}
*/
#endif