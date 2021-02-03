#pragma once
#include <stdio.h>
#include <winsock2.h>

#ifdef _WIN32
#   include <WinSock2.h>
#   include <Ws2tcpip.h>
#   include <string>
#   pragma comment(lib, "ws2_32.lib")
#else
    // TODO: look into changing socket import based on OS. 
#endif





namespace PanChat{

	class Server{
		// The server will use UDP, default port {};

		private:
        //constructor creates a UDP socket that defaults to IPv4.
		PanServer();
        sockaddr_in serverAddr;
        short port;
        vector<serverClient> connectedClients;

		int serverIP;
		int serverPort;
        
        
        
        public:
		void transmitLocations();

		void transmitVoice();
	
		//rCenter = relative center
		vector<serverClient> nearbyUsers(serverClient rCenter);

		//sendeeUsers = users that will receive audio packets
		//will possibly return a struct in the form [recipient (serverClient), audio (TBD)];
		vector<audioPacketTbd> binaurifyVoice(vector<serverclient> sendeeUsers);


	};


}