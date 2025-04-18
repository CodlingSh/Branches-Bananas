#include "player.h"
#include "branch.h"
#include <Arduboy2.h>

Arduboy2 ab;
Player player;
Branch branches[6];

const uint8_t PROGMEM tree[] = {
8, 3,
0x06, 0x07, 0x05, 0x05, 0x05, 0x07, 0x07, 0x06, 
};

const uint8_t PROGMEM treeR[] = {
8, 3,
0x03, 0x07, 0x05, 0x05, 0x07, 0x07, 0x03, 0x03, 
};



int state;

void setup() {
  // put your setup code here, to run once:
  ab.begin();
  Serial.begin(9600);
  ab.clear();
  state = 0; 
  ab.setFrameRate(60);
}

void loop() {
  static int animFrame = 0;

  // Check for next frame
  if (!ab.nextFrame()) {
    return;
  }

  ab.pollButtons();
  ab.clear();

  // Game State switch
  switch (state) {
    case 0:
      titlescreen();
      break;
    case 1:
      
      draw_vines(animFrame);
      ab.setCursor(100, 30);
      ab.println(branches[0].getX());
      if (ab.justPressed(LEFT_BUTTON)) {
        player.jump();
      };
      if (ab.justPressed(A_BUTTON)) {
        branches[0].spawn();
      }
      for (int i = 0; i < 6; i++) {
        if (branches[i].getActive()) {
          branches[i].update();
        }
      }
      player.update();
      break;
  }

  ab.display();
}

void titlescreen() {
  ab.setCursor(0, 0);
  ab.println("Press the A button!");
  if (ab.justPressed(A_BUTTON)) {
    ab.initRandomSeed();
    state = 1;
  } 
}

void draw_vines(int &animFrame) {
  
  if (animFrame < 7) {
    animFrame++;
  } else {
    animFrame = 0;
  }

  for (int i = 0; i <= 128; i += 8) {
    Sprites::drawOverwrite(i - animFrame, 0, tree, 0);
    Sprites::drawOverwrite(i - animFrame, 61, treeR, 0);
  }
}


