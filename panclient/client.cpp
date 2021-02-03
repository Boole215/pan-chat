#include "client.h"

PanChat::Client(char* serverIP){
    char SendBuf[1024];
    int BufLen = (int)(sizeof(SendBuf)-1);
    
    struct sockaddr_in ClientAddr;
    int clientAddrSize =(int)sizeof(ClientAddr);

    short port = 27015;
    const char* local_host = serverIP;
    
    ClientAddr.sin_family = AF_INET;
    ClientAddr.sin_port = htons(port);
    ClientAddr.sin_addr.s_addr = inet_addr(localhost);
    
    //the following is the code to send to a server;
    int clientResult = sendto(SendSocket, 
                              SendBuf, BufLen, 0, (SOCKADDR *) & ClientAddr, clientAddrSize);
};