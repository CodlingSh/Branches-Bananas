#ifndef PLAYER_H
#define PLAYER_H

#include <Arduboy2.h>

// SPRITES
const unsigned char PROGMEM monkeyR[] = {
  16, 16,
  0xc0, 0x20, 0x10, 0x0e, 0x01, 0x0d, 0x15, 0x12, 0x08, 0x08, 0x24, 0x14, 0x14, 0x24, 0x08, 0xf0, 
  0x7f, 0x80, 0x80, 0xfc, 0x04, 0x7c, 0xc0, 0xfc, 0x02, 0x04, 0x08, 0x09, 0x05, 0x04, 0x02, 0x01,
};

const uint8_t PROGMEM monkey[] = {
  16, 16,
  0xfe, 0x01, 0x01, 0x3f, 0x20, 0x3e, 0x03, 0x3f, 0x40, 0x20, 0x10, 0x90, 0xa0, 0x20, 0x40, 0x80, 
  0x03, 0x04, 0x08, 0x70, 0x80, 0xb0, 0xa8, 0x48, 0x10, 0x10, 0x24, 0x28, 0x28, 0x24, 0x10, 0x0f, 
};

// Jumping sprite
const uint8_t PROGMEM monkeyJump[] = {
  16, 16,
  0xe0, 0x10, 0x08, 0x04, 0x04, 0x04, 0x08, 0x08, 0x04, 0x02, 0x41, 0x89, 0x8a, 0x42, 0x04, 0xf8, 
  0x7f, 0x80, 0x80, 0xfe, 0x02, 0x0e, 0x10, 0x26, 0x49, 0x91, 0x62, 0x02, 0x02, 0x02, 0x01, 0x00, 
};

const uint8_t PROGMEM monkeyJumpR[] = {
  16, 16,
  0xfe, 0x01, 0x01, 0x7f, 0x40, 0x70, 0x08, 0x64, 0x92, 0x89, 0x45, 0x42, 0x40, 0x40, 0x80, 0x00, 
  0x07, 0x08, 0x10, 0x20, 0x20, 0x20, 0x10, 0x10, 0x20, 0x40, 0x82, 0x91, 0x51, 0x42, 0x20, 0x1f, 
};

class Player {
  private:
    int _x = 5;
    int _y = 0;
    float gravityDelta = 0.125;
    bool airborn = false;
    bool onRight = false;
    bool falling = false;
    uint8_t *currSprite = monkey; 
  
  public:

    int getX() {
      return _x;
    }
    
    int getY() {
      return _y;
    }

    void jump() {
      if (!airborn) {
        if (onRight) {
          currSprite = monkeyJump;
        }
        else {
          currSprite = monkeyJumpR;
        }
        airborn = true;
      }
    }

    void fall() {
      falling = true;
    }

    void reset() {
      _x = 5;
      _y = 0;
      gravityDelta = 0.125;
      airborn = false;
      onRight = false;
      falling = false;
      currSprite = monkey; 
    }

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
      }

      // Reset sprite when not airborn
      if (!airborn) {
        if (onRight) {
          currSprite = monkeyR;
        }
        else {
          currSprite = monkey;
        }  
      }

      // Fall when hit
      if (falling) {
        _x -= gravityDelta;
        if (onRight) {
          _y -= 2;
        }
        else if (!onRight) {
          _y += 2;
        }

        if (gravityDelta < 5) gravityDelta += gravityDelta;
        if (_x < -50) falling = false;
      }
    }

    void draw() {
      // Draw player
      Sprites::drawOverwrite(_x, _y, currSprite, 0);
    }
};

#endif