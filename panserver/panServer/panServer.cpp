#include "panServer.h"

#define BUFLEN 512 //TODO: Look into why we define bufflen

#define PORT 8888 //Server listening port

PanChat::Server(){
    
    SOCKET serverSocker = INVALID_SOCKET;
    
    // socket(socket_family, socket_type, protocol(ipv4/ipv6))
    serverSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    
    if(serverSocket == INVALID_SOCKET){
        printf("socket failed with error %d\n", WSAGetLastError());
        return 1;
    }
    struct sockaddr_in serverAddr;
    short port = 27015;
    
    // Bind the socket to addr and port
    serverAddr.sin_family = AF_INET;
    // We have to do htons so that the port # is readable 
    // to the server. 16-bit short int to network ordered 16 bit int.
    //(networks use endian(?), winsock uses big endian)
    serverAddr.sin_port = htons(port);
    // inet_addr is basically htons for a string ipaddress
    // converts an ipv4 literal string to a network ordered
    // 32 bit integer.  
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    
    // IIRC (SOCKADDR *) is in parantheses because the * is low in the order of 
    // operations, so that line returns a SOCKADDR pointer which points at 
    // serverAddr;
    if(bind(serverSocket, (SOCKADDR *) & serverAddr, sizeof(serverAddr))){
        printf("bind failed with error %d\n", WSAGetLastError());
        return 1;
    }
    
    int bytes_received;
    char serverBuf[1025];
    int serverBufLen = 1024;
    
    //Keep a separate address struck to store sender information
    
    struct sockaddr_in SenderAddr;
    int SenderAddrSize = sizeof(SenderAddr);
    
    printf("Receiving datagraoms on %s\n", "127.0.0.1:27015");
    
    bytes_received = rexvfrom(serverSocket, serverBuf, 0 /* no flags */, (SOCKADDR *)  & SenderAddr, &SenderAddrSize);
    
    if (bytes_received == SOCKET_ERROR){
        printf("recvfrom failed with error %d\n", WSAGetLastError());
    }
    
    serverBuf[bytes_received] = '\0'
        
    char sendBuf[] = {'h', 'e', 'l', 'l', 'o', '\0'}
    
    int sendBufLen = (int)(sizeof(sendBuf) - 1);
    
    int sendResult = sendto(serverSocket, 
                            sendBuf, sendBufLen, 0, (SOCKADDR *) & SenderAddr, SenderAddrSize);
    
    if(sendResult == SOCKET_ERROR){
        printf("Sending back response got an error: %d\n", WSAGetLastError());
    }
}