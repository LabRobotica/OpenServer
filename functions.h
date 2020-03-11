#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

#define debug
#ifdef debug
    #define dprint(x) cerr<<x<<endl
#else
    #define dprint(x)
#endif

void OPENSERVER_presentation()
{
    cout << "\t\t*----------------------------------*") << endl;
    cout << "\t\t|         -> OpenServer <-         |") << endl;
    cout << "\t\t|       Comau C5G-Open eORL        |") << endl;
    cout << "\t\t|   CEFET-MG Unidade Divinópolis   |") << endl;
    cout << "\t\t*----------------------------------*") << endl << endl;
}