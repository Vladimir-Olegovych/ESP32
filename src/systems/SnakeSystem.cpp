#include <SnakeSystem.h>

void SnakeSystem::loop(uint8_t &command){
    switch (command) {
    case 1:
      y++;
      break;
    case 2:
      y--;
      break;
    case 3:
      x--;
      break;
    case 4:
      x++;
      break;
    }

    if(x < 0) x = 15;
    if(x > 15) x = 0;

    if(y < 0) y = 15;
    if(y > 15) y = 0;
}
Vector2 SnakeSystem::getPosition(){
  v.x = x; v.y = y;
  return v;
}
SnakeSystem::SnakeSystem(){

}

SnakeSystem::~SnakeSystem(){

}
