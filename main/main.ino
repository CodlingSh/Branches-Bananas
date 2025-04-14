#include "player.h"
#include <Arduboy2.h>

Arduboy2 ab;
Player player;

const uint8_t PROGMEM vine[] = {
8, 4,
0x07, 0x07, 0x07, 0x07, 0x07, 0x07, 0x0f, 0x07, 
};

const uint8_t PROGMEM vineR[] = {
8, 4,
0x0e, 0x0e, 0x0f, 0x0e, 0x0e, 0x0e, 0x0e, 0x0e, 
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
      ab.println(player.getY());
      if (ab.justPressed(LEFT_BUTTON)) {
        player.jump();
      };
      player.update();
      break;
  }

  Serial.write(ab.getBuffer(), 128 * 64 / 8);
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
  
  if (animFrame < 8) {
    animFrame++;
  } else {
    animFrame = 0;
  }

  for (int i = 0; i <= 128; i += 8) {
    Sprites::drawOverwrite(i - animFrame, 0, vine, 0);
    Sprites::drawOverwrite(i - animFrame, 60, vineR, 0);
  }
}


