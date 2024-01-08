#pragma once
#include <stdint.h>

struct Vector2 {
    short x = 0;
    short y = 0;
};

class SnakeSystem
{
private:
    short x = 0;
    short y = 0;
    Vector2 v;
public:
    void loop(uint8_t &command);
    Vector2 getPosition();
    SnakeSystem();
    ~SnakeSystem();
};