#include "serverClient.h"
#include "../../structs/coord.h"

//Maybe turn this into a struct?
PanChat::ServerClient::ServerClient(std::string cIP, coord cLocation, std::string cName){
  userIP = cIP;
  location.x = cLocation.x;
  location.y = cLocation.y;
  name = cName;

}
