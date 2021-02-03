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

	class Client{

	private:
		char* serverAddr;
		short port;
        sockaddr_in ClientAddr;
		
		//user location in grid
		coord location;
		
		string username;

    public:
        Client(char* serverIP);
		//routine that awaits data from server
		void awaitData();

		//sends new coords to server
		void sendCoord();

		//sends audio input to server
		void sendComms();

        //generic send method
        void sendPkt(char* sendBuf);
        

	};

}