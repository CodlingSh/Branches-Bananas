#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>

const unsigned char PROGMEM monkey[] =
    {
      // width, height,
      16, 16,
      // FRAME 00
      0xc0, 0x20, 0x10, 0x0e, 0x01, 0x0d, 0x15, 0x12, 0x08, 0x08, 0x24, 0x14, 0x14, 0x24, 0x08, 0xf0, 
      0x7f, 0x80, 0x80, 0xfc, 0x04, 0x7c, 0xc0, 0xfc, 0x02, 0x04, 0x08, 0x09, 0x05, 0x04, 0x02, 0x01,
    };

class Player {
  private:
    int _x = 5;
    int _y = 48;
    bool airborn = false;
    bool onRight = true;
  
  public:

    int getX() {
      return _x;
    };
    
    int getY() {
      return _y;
    };

    void jump() {
      if (!airborn) {
        airborn = true;
      }
    };

    void update() {
      if (airborn) {
        if (onRight) {
          _y -= 4;
        }
        else if (!onRight) {
          _y += 4;
        }

        if (_y == 0 || _y == 48) {
          airborn = false;
          onRight = !onRight;
        }
      };

      // Draw player
      Sprites::drawOverwrite(_x, _y, monkey, 0);
    };

};

#endif