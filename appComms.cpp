#include <irrKlang.h>
#include <iostream>
#include <stdio.h>
using namespace irrklang;


int main(){
  ISoundEngine* engine = createIrrKlangDevice();
  if(!engine){
    return 0;
  }
  std::cout << "Hello world!\n";

  char i = 0;

  while(i != 'q'){
    std::cout << "Press any key to play some sound, press 'q' to quit.\n";

    //play sound
    engine->play2D("./media/getout.ogg", true);

    std::cin >> i;
  }
  engine->drop();

  return 0;
}
