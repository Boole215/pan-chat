
#pragma once

#include <string>
#include <cstring>
#include "../../structs/coord.h"

typedef struct coordinates coord;
namespace PanChat{

    class ServerClient{

    private:
      std::string userIP;

      coord location;

      std::string name;



    public:
      /*ServerClient constructor
       *@param cIP client IP address (String)
       *@param cLocation client location (x,y on grid/map)
       *@param cName Name of client (String)
       */
      ServerClient(std::string cIP, coord cLocation, std::string cName);
    };
}
