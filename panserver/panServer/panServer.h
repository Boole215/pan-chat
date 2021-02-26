#pragma once

#include <iostream>
#include <vector>
#include <cstring>


#include "../serverclient/serverClient.h"




namespace PanChat{

  class Server{
    // The server will use UDP, default port {};

  private:


    //IP of the server
    std::string serverIP;
    short port;
    //Buffer for receiving packets.
    char serverBuf[1025];
    //Length of the buffer
    int serverBufLen = 1024;
    //Radius that will be used to determine hearable dist
    int commRadius;

    std::vector<ServerClient> connectedClients;

    double distance(ServerClient thisClient, ServerClient otherClient);



  public:
    Server();
    //constructor creates a UDP socket that defaults to IPv4 and binds to port.
    Server(std::string sIP, short sPort);
    /*
     * Transmits new coords to clients.
     * (So that they can update their grid display with the new location(s))
     */
    void transmitLocations();
    /*
     * Transmits voice packets to the users that are able to hear them.
     */
    void transmitVoice();

    /*
     * Finds the clients that are close enough to hear the client "rCenter"
     * @param rCenter client to be used as the relative center
     * @return vector of serverClients that are close enough to hear rCenter
     */
    std::vector<ServerClient> nearbyUsers(ServerClient rCenter);

    /*
     * Performs actions for when a new client joins
     * @param newClient newClient to be added to connectedUsers,
     * and to be notified that they have successfully connected.
     */
    void onJoin(ServerClient newClient);

    /*
     * Lowers audio file volume based on distance from user emitting audio
     * @param sendeeUsers users that will receive audio packets
     * @return Nothing.
     */
    void binaurifyVoice(std::vector<ServerClient> sendeeUsers);
    /*
     *will possibly return a struct in the form [recipient (serverClient), audio (TBD)];
     *need to find a library that can modify audio files.
     */

  };


}
