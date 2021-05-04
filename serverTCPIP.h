#ifndef SERVERTCPIP_H
#define SERVERTCPIP_H

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <string>
#include <cstring>
#include <memory>

int clientSocket;
int listening;

#define val 100000

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
 
    memset(host, 0, NI_MAXHOST);
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
        void init();
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
        
        /*
        /////////TEMPORARIO/////////////
        angleListen->value[0]=10.2;
        angleListen->value[1]=15.0;
        angleListen->value[2]=13.501;
        angleListen->value[3]=10.0;
        angleListen->value[4]=10.0;
        angleListen->value[5]=10.0;
        /////////TEMPORARIO/////////////
        */

        switch (buf[0])
        {
            case 't': //teste mode
                send(clientSocket, "j 5000 5000 5000 5000 5000 5000", 31, 0);
                break;
            
            case 'm': //mirror mode
                dprint("Mirror MODE");
                send(clientSocket, buf, bytesReceived + 1, 0);
                break;

            case 'l': //Listen mode
            {
                auto a1 = angleListen;
                std::string buffer;
                #define val 100000
                buffer  = std::to_string( (int) (a1->value[0]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[1]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[2]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[3]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[4]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[5]*val));

                for(int i=0; i<buffer.size(); i++)  buf[i] = buffer[i];
                cout << buf << endl;
                send(clientSocket, buf,300/* strlen(buf) + 1*/, 0);
                break;
            }
            case 'g': //Listen mode
            {
                auto a1 = angleListen;
                send(clientSocket, reinterpret_cast<char*>(a1.get()), 100/*sizeof(a1.get())*/, 0);                
                break;
            }
            case 'h': //Listen mode
            {
                double test=2.00;
                memset(buf, 0, 4096);
                mempcpy(buf, &test, 8);
                send(clientSocket, buf, 8, 0);
                //send(clientSocket, reinterpret_cast<char*>(test),20, 0);                
                break;
            }
            case 'i': //Listen mode
            {
                auto a1 = angleListen;
                memset(buf, 0, 4096);
                mempcpy(buf, a1.get(),52 /*sizeof(a1.get())*/ );
                send(clientSocket, buf, 52/*strlen(buf)*/, 0);
                
                break;
            }
            case 'c': //Close conection
                return 0;

            case 'p': //Pos Absolute Axis
            {
                //Primeiramente pegar os angulos no ponteiro inteligente e os enviar para a rede
                auto a1 = angleListen;
                std::string buffer;
                buffer  = std::to_string( (int) (a1->value[0]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[1]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[2]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[3]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[4]*val));
                buffer += " ";
                buffer += std::to_string( (int) (a1->value[5]*val));
                for(int i=0; i<buffer.size()+1; i++)  buf[i] = buffer[i];
                cout << "AQUI " << buf << endl;
                send(clientSocket, buf,buffer.size()+1/* strlen(buf) + 1*/, 0);

                //Depois pegar os angulos que foram salvos anteriormente e colocar no ponteiro inteligente
                auto sx_joint_pos = std::shared_ptr <ORL_joint_value>        (new ORL_joint_value);
                char resposta[] = "15500000 15500000 15500000 15500000 15500000                 ";
                for(int k=2;k<bytesReceived;k++) resposta[k-2]=buf[k];
                std::string::size_type sz;
                char * pedaco;//string pedaco;
                
                try
                {
                    pedaco = strtok (resposta," ");
                    sx_joint_pos->value[0] = ((double)std::stoi(pedaco,&sz))/val;
                    pedaco = strtok (NULL, " ");
                    sx_joint_pos->value[1] = ((double)std::stoi(pedaco,&sz))/val;
                    pedaco = strtok (NULL, " ");
                    sx_joint_pos->value[2] = ((double)std::stoi(pedaco,&sz))/val;
                    pedaco = strtok (NULL, " ");
                    sx_joint_pos->value[3] = ((double)std::stoi(pedaco,&sz))/val;
                    pedaco = strtok (NULL, " ");
                    sx_joint_pos->value[4] = ((double)std::stoi(pedaco,&sz))/val;
                    pedaco = strtok (NULL, " ");
                    sx_joint_pos->value[5] = ((double)std::stoi(pedaco,&sz))/val;
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                    cout << resposta << endl;
                }
                
                
                angleWriten = sx_joint_pos;
                break;
            }

            default: //Mirror mode
                send(clientSocket, buf, bytesReceived + 1, 0);
                break;
        }
    }
    
    return 0;
}

#endif