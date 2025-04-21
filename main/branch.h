#ifndef BRANCH_H
#define BRANCH_H

#include <Arduboy2.h>

const uint8_t PROGMEM smallBranch[] = {
7, 16,
0x01, 0x01, 0xc3, 0xff, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0x7f, 0xff, 0xff, 0x0c, 
};

const uint8_t PROGMEM largeBranch[] = {
7, 32,
0x01, 0x01, 0x03, 0xff, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0xf3, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x03, 
0x00, 0x00, 0x0c, 0xff, 0xff, 0xff, 0x00, 
};

const uint8_t PROGMEM smallBranchR[] = {
7, 16,
0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x30, 
0x80, 0x80, 0xc3, 0xff, 0xff, 0xff, 0x00, 
};

const uint8_t PROGMEM largeBranchR[] = {
7, 32,
0x00, 0x00, 0x30, 0xff, 0xff, 0xff, 0x00, 
0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0xc0, 
0x00, 0x00, 0x00, 0xcf, 0xff, 0xff, 0x00, 
0x80, 0x80, 0xc0, 0xff, 0xff, 0xff, 0x00, 
};

class Branch {
  private:
    int _x = 140;
    int _y = 3;
    int _length = 16;
    int _height = 7;
    bool _active = false;
    uint8_t *_currSprite;

  public:

    int getX() {
      return _x;
    };

    int getY() {
      return _y;
    };

    int getLength() {
      return _length;
    };

    int getHeight() {
      return _height;
    }

    bool getActive() {
      return _active;
    }

    void spawn() {
      _x = 140;
      _y = 3;
      _active = true;
      int rnd = random(10);

      if (rnd == 2) {
        _currSprite = largeBranch;
        _height = 32;
      }
      else {
        _currSprite = smallBranch;
      }

      Serial.println(String(rnd));

      
    };

    void update() {
      if (_active == true) {
        _x--;
        
        if (_x < -5) {
          _x = 140;
          _active = false;
        }
      }
    };

    void draw() {
      Sprites::drawOverwrite(_x, _y, _currSprite, 0);
    };
};

#endif