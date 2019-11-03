#include <iostream>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>
#include <string>

using namespace std;
int clientSocket;

int TCPIP_listen_mode()
{
    #ifdef debug
        cerr << "----------------------------" << endl;
        cerr << "|    TCPIP_listen_mode()   |" << endl;
        cerr << "----------------------------" << endl << endl;

        cerr << "[TCPIP]  Create a socket" << endl;
    #endif
    int listening = socket(AF_INET, SOCK_STREAM, 0);
    if (listening == -1)
    {
        #ifdef debug
            cerr << "[TCPIP]  Can't create a socket! Quitting" << endl;
        #endif
        return -1;
    }
    
    #ifdef debug
        cerr << "[TCPIP]  Bind the ip address and port to a socket" << endl;
    #endif

    sockaddr_in hint;
    hint.sin_family = AF_INET;
    hint.sin_port = htons(54000);
    inet_pton(AF_INET, "0.0.0.0", &hint.sin_addr);
 
    bind(listening, (sockaddr*)&hint, sizeof(hint));
 
    #ifdef debug
        cerr << "[TCPIP]  Tell Winsock the socket is for listening" << endl;
    #endif
    listen(listening, SOMAXCONN);
 
    #ifdef debug
        cerr << "[TCPIP]  Wait for a connection" << endl;
    #endif
    sockaddr_in client;
    socklen_t clientSize = sizeof(client);
 
    clientSocket = accept(listening, (sockaddr*)&client, &clientSize);
 
    char host[NI_MAXHOST];      // Client's remote name
    char service[NI_MAXSERV];   // Service (i.e. port) the client is connect on
 
    memset(host, 0, NI_MAXHOST); // same as memset(host, 0, NI_MAXHOST);
    memset(service, 0, NI_MAXSERV);
 
    if (getnameinfo((sockaddr*)&client, sizeof(client), host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
    {
        #ifdef debug
            cout << host << "[TCPIP]  connected on port " << service << endl;
        #endif
    }
    else
    {
        inet_ntop(AF_INET, &client.sin_addr, host, NI_MAXHOST);
        #ifdef debug
            cout << host << "[TCPIP]  connected on port " << ntohs(client.sin_port) << endl;
        #endif
    }
    
    #ifdef debug
        cerr << "[TCPIP]  Close listening socket" << endl;
    #endif
    close(listening);
    return 0;
}

int TCPIP_close_mode()
{
    cerr << "----------------------------" << endl;
    cerr << "|    TCPIP_close_mode()    |" << endl;
    cerr << "----------------------------" << endl << endl;
    // Close the socket
    close(clientSocket);
 
    return 0;
}

int TCPIP_mirror_mode() //Test mode
{
    char buf[4096];
    memset(buf, 0, 4096);

    #ifdef debug
        cerr << "Wait for client to send data" << endl;
    #endif
    int bytesReceived = recv(clientSocket, buf, 4096, 0);
    if (bytesReceived == -1)
    {
        #ifdef debug
            cerr << "Error in recv(). \n Quitting..." << endl;
        #endif
        return 1;
    }

    if (bytesReceived == 0)
    {
        #ifdef debug
            cout << "Client disconnected..." << endl;
        #endif
        return 2;
    }

    cout << string(buf, 0, bytesReceived) << endl;

    #ifdef debug
        cerr << "Echo message back to client" << endl;
    #endif
    send(clientSocket, buf, bytesReceived + 1, 0);
    
    return 0;
}
