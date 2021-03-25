#include <iostream>
#include <string>
#include <vector>
#include <ncurses.h>
#include <sstream>
#include <cstring>

struct User{
  int x;
  int y;
  std::string name;
  int IDN;
};
typedef struct User User;

class Game{
public:
  Game(std::string height, std::string width)
    :height_(std::stoi(height)),
     width_(std::stoi(width)),
     myIDN_(0)
  {

    initscr();
    curs_set(0);
    keypad(stdscr, TRUE);
    refreshOutput();

  }

  std::string addUser(User newUser){
    newUser.x = width_/2;
    newUser.y = height_/2;
    newUser.IDN = userVect.size();
    userVect.push_back(newUser);
    refreshOutput();
    return std::to_string(newUser.IDN);
  }
  //for a packet in the form:
  // ["posi",anIDN,"CTM", newX, "-", newY, , "-", anIDN2, "-", newX2, "-", newY2, ..., "-", anIDNN, "-", newXN, "-", newYN]
  // where "-" will be used as a way to determine where each entry starts/stops
  // and the "posi" will be used to identify the packet as one for position updating
  // voice updates will be appended with "comm".
  void interpretPacket(char* recv_buffer_, int recv_len_){
    std::string interpretStart;
    for(int i = 0; i < 4; i++){
      interpretStart.push_back(recv_buffer_[i]);
    }
    //std::cout << interpretStart << std::endl;
    switch (interpretStart == "comm"){
    case 0:
      positionUpdate(recv_buffer_, recv_len_);
      refreshOutput();
      break;
    case 1:
      playComms(recv_buffer_, recv_len_);
      refreshOutput();
      break;
    }
  }



private:
  int height_;
  int width_;
  std::vector<User> userVect;
  int myIDN_;

  void positionUpdate(char* recv_buffer_, int recv_len_){
    // do this
    //std::cout << "I am in position Update" << std::endl;
    std::string processBuff = "";
    int place = 0;
    int cIDN;
    int cX;
    int cY;


    for(int i = 4; i < recv_len_; i++){
      if(recv_buffer_[i] != '-'){
	processBuff.push_back(recv_buffer_[i]);
	//std::cout << processBuff << std::endl;
      } else{
	switch(place%3){
	case 0:
	  //std::cout << "I'm in case 0" << std::endl;
	  cIDN = std::stoi(processBuff);
	  processBuff = "";
	  place++;
	  break;
	case 1:
	  //std::cout << "I'm in case 1" << std::endl;
	  cX = std::stoi(processBuff);
	  processBuff = "";
	  place++;
	  break;
	case 2:
	  //std::cout << "I'm in case 2" << std::endl;
	  cY = std::stoi(processBuff);
	  processBuff = "";
	  //std::cout << "IDN, newX, newY: (" << cIDN << ", " << cX << ", " << cY << ")" << std::endl;
	  updateLocation(cIDN, cX, cY);
	  place++;
	  break;
	}
      }
    }
  }

  void playComms(char* recv_buffer_, int recv_len_){
    // do this
  }

  void updateLocation(int IDN, int newX, int newY){
    //printf("(%d,%d,%d)", IDN, newX, newY);
    if(newX != 0 || newX != width_ - 1 || newY != 0 || newY != height_- 1){
      userVect.at(IDN).x = newX;
      userVect.at(IDN).y = newY;
    }

  }

  void refreshOutput(){
    std::stringstream s;
    for(int y = 0; y < height_; y++){
      for(int x = 0; x < width_; x++){
	std::string userHere = aUserLoc(x,y);
	if(userHere != "--"){
	  s << userHere.at(0);
	} else if(y == 0 || y == height_-1){
	  s << "-";
	} else if(x == 0 || x == width_-1){
	  s << "|";
	} else{
	  s << ".";
	}
      }
      s << "\n";
    }
    std::string outputStr = s.str();
    const char* char_arr = outputStr.c_str();
    //std::cout << "Printing new output" << std::endl;
    erase();
    mvprintw(0,0, char_arr);
    refresh();
  }

  std::string aUserLoc(int x, int y){
    std::string output = "";
    for(User crnt : userVect){
      if(crnt.x == x && crnt.y == y){
	//std::cout << "User loc is (" << x << "," << y << ")" << std::endl;
	output.push_back(crnt.name.at(0));
	return output;
      }
    }

    return "--";
  }
};



std::string packetMaker(int IDN, int newx, int newy){
  std::string retString = "posi";
  retString += std::to_string(IDN);
  retString += "-";
  retString += std::to_string(newx);
  retString += "-";
  retString += std::to_string(newy);
  retString += "-";
  //std::cout << "newy as a char" << retString.at(8) << std::endl;
  //std::cout << "Created packet: "<< retString << std::endl;
  return retString;

}

void copyStringTo(char* charBuf, const char* cStr){
  int i = 0;
  char crntChar = cStr[0];
  while(crntChar != '\0'){
    charBuf[i] = crntChar;
    i++;
    crntChar = cStr[i];
  }
}

int main(int argc, char* argv[]){

  User thisUser;
  thisUser.x = 5;
  thisUser.y = 10;
  // inputName will be set to Andrew for testing purposes
  std::string inputName = "Andrew";
  //std::cout << "Inputted name is " << inputName << std::endl;
  thisUser.name = inputName;
  thisUser.IDN = 0;
  int width = 10;
  int height = 20;

  Game currentSession("20","10");
  std::string userIDN = currentSession.addUser(thisUser);
  std::string mockPkt;
  char* mockbuf;
  while(true){
    switch(getch()){

    case KEY_LEFT:
      if(thisUser.x-1 > 0){
	//std::cout << "Key_Left pressed" << std::endl;
	mockPkt = packetMaker(thisUser.IDN, thisUser.x-1, thisUser.y);
	//std::cout << "Packet created" << std::endl;
	//std::cout << "mockPkt size" << mockPkt.size() << std::endl;
	mockbuf = new char[mockPkt.size()];
	copyStringTo(mockbuf, mockPkt.c_str());
	//strncpy(mockbuf,mockPkt.c_str(),mockPkt.size());
	//std::cout << "Copied to mockbuf" << std::endl;
	const char* conBuf = mockPkt.c_str();
	//for(int i = 0; i < mockPkt.size();i++){
	  //std::cout << conBuf[i] << std::endl;
	//}
	//std::cout << "I make it past the print loop" << std::endl;

	currentSession.interpretPacket(mockbuf, mockPkt.size());
	thisUser.x = thisUser.x-1;
	delete[] mockbuf;
      }
      break;

    case KEY_RIGHT:
      if(thisUser.x+1 < width-1){
	//std::cout << "Key_Right pressed" << std::endl;
	mockPkt = packetMaker(thisUser.IDN, thisUser.x+1, thisUser.y);
	mockbuf = new char[mockPkt.size()];
	copyStringTo(mockbuf,mockPkt.c_str());

	currentSession.interpretPacket(mockbuf, mockPkt.size());
	thisUser.x = thisUser.x+1;
	delete[] mockbuf;
      }
      break;

    case KEY_UP:
      if(thisUser.y-1 > 0){
	mockPkt =  packetMaker(thisUser.IDN, thisUser.x, thisUser.y-1);
	mockbuf = new char[mockPkt.size()];

	copyStringTo(mockbuf, mockPkt.c_str());

	currentSession.interpretPacket(mockbuf, mockPkt.size());
	thisUser.y = thisUser.y-1;
	delete[] mockbuf;
      }
      break;

    case KEY_DOWN:
      if(thisUser.y+1 < height-1){
	mockPkt = packetMaker(thisUser.IDN, thisUser.x, thisUser.y+1);
	mockbuf = new char[mockPkt.size()];

	copyStringTo(mockbuf,mockPkt.c_str());

	currentSession.interpretPacket(mockbuf, mockPkt.size());
	thisUser.y = thisUser.y+1;
	delete[] mockbuf;
      }
      break;
    case 'Q':
      goto exit;
    }
  }
 exit:
  endwin();


  return 0;

}
