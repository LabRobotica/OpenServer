#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>


#ifdef debug                         //If debug mode is active
    #define dprint(x)   cout<<x<<endl  //Substitute for this expression
#else                                //If not active
    #define dprint(x)                //Replace with nothing
#endif

void OPENSERVER_presentation()       //Print the program presentation on the screen
{                                    //regardless of whether the debug is active
    cout << "\t\t*----------------------------------*" << endl;
    cout << "\t\t|         -> OpenServer <-         |" << endl;
    cout << "\t\t|       Comau C5G-Open eORL        |" << endl;
    cout << "\t\t|   CEFET-MG Unidade Divinópolis   |" << endl;
    cout << "\t\t*----------------------------------*" << endl << endl;
}

#endif