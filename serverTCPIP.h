#ifndef SERVERTCPIP_H
#define SERVERTCPIP_H

#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>
#include <cstring>
#include "CRCOpen.h"



using namespace std;

int clientSocket;
int listening;

int TCPIP_open_connect() 
{
    dprint("----------------------------");
    dprint("|    TCPIP_open_connect()  |");
    dprint("----------------------------");
    dprint("[TCPIP]  Create a socket");

    listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        dprint("[TCPIP]  Can't create a socket! Quitting");
        return -1;
    }

    dprint("[TCPIP]  Bind the ip address and port to a socket");

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 
    dprint("[TCPIP]  Tell Winsock the socket is for listening");

    listen(listening, SOMAXCONN);
    
    return 0;
}

int TCPIP_listen_mode()
{
    dprint("----------------------------");
    dprint("|    TCPIP_listen_mode()   |");
    dprint("----------------------------");

    dprint("[TCPIP]  Wait for a connection");

    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);

    
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        dprint("[TCPIP]  Connected on IP: " << host);
        dprint("[TCPIP]  Connected on port: " << service);
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        dprint("[TCPIP]  Connected on IP: " << host);
        dprint("[TCPIP]  Connected on port: " << ntohs(client.sin_port));
    }
    
    
    return 0;
}

int TCPIP_close_mode()
{
    dprint("----------------------------");
    dprint("|    TCPIP_close_mode()    |");
    dprint("----------------------------");
    
    close(clientSocket);// Close the socket
 
    return 0;
}

int TCPIP_mirror_mode() //Test mode
{
    char buf[4096];
    memset(buf, 0, 4096);
    dprint("Wait for client to send data");

    int bytesReceived = recv(clientSocket, buf, 4096, 0);
    if (bytesReceived == -1)
    {    
        dprint("Error in recv(). \n Quitting...");
        return 1;
    }
    if (bytesReceived == 0)
    {
        dprint("Client disconnected...");
        return 2;
    }

    dprint(string(buf, 0, bytesReceived));
    dprint("Echo message back to client");
    send(clientSocket, buf, bytesReceived + 1, 0);
    
    return 0;
}

int TCPIP_choose_mode() //Test mode
{
    char buf[4096];

    dprint("----------------------------");
    dprint("|    TCPIP_choose_mode()   |");
    dprint("----------------------------");
    dprint("");

    while (true)
    {
        memset(buf, 0, 4096);

        dprint("Wait for client to send data");

        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if (bytesReceived == -1)
        {
            dprint("Error in recv(). \n Quitting...");
            return 1;
        }

        if (bytesReceived == 0)
        {
            dprint("Client disconnected...");
            return 2;
        }

        dprint("CLIENT> " << string(buf, 0, bytesReceived));
        
        switch (buf[0])
        {
            case 't': //teste mode
                send(clientSocket, "j 5000 5000 5000 5000 5000 5000", 31, 0);
                break;
            
            case 'm': //mirror mode
                send(clientSocket, buf, bytesReceived + 1, 0);
                break;

            case 'l': //Listen mode
            {
                auto a1 = angle;
                std::string buffer;
                buffer  = std::to_string( (int) (a1->value[0]*1000));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[1]*1000));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[2]*1000));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[3]*1000));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[4]*1000));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[5]*1000));

                for(int i=0; i<buffer.size(); i++)  buf[i] = buffer[i];
                
                send(clientSocket, buf, strlen(buf) + 1, 0);
                break;
            }
            case 'g': //Listen mode
            {
                memset(buf, 0, 4096);
                auto a1 = angle;
                memset(buf, a1, a1.size());
                
                send(clientSocket, buf, strlen(buf) + 1, 0);
                break;
            }

            case 'c': //Close conection
                return 1;

            default: //error mode
                send(clientSocket, buf, bytesReceived + 1, 0);
                break;
        }
    }
    
    return 0;
}

#endif