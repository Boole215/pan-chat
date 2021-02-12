#pragma once

namespace PanChat{


    /*sendVol is the % gain modification that's going to be made
     * to the speaking user's audio before it's sent to the nearbyUser
    */
    struct NearbyUser{
        serverClient user;
        int sendVol;
    };

}
