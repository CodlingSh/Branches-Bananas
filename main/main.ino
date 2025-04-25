#include "player.h"
#include "branch.h"
#include <Arduboy2.h>

#define MAX_BRANCHES 6

Arduboy2 ab;
Player player;
Branch branches[MAX_BRANCHES];
bool animate = true;
int state;

// TREE SPRITES
const uint8_t PROGMEM tree[] = {
8, 3,
0x05, 0x05, 0x06, 0x06, 0x05, 0x05, 0x06, 0x06, 
};

const uint8_t PROGMEM treeR[] = {
8, 3,
0x03, 0x03, 0x05, 0x05, 0x03, 0x03, 0x05, 0x05, 
};

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
  static int spawnTimer = 0;

  // Check for next frame
  if (!ab.nextFrame()) {
    return;
  }

  ab.pollButtons();
  ab.clear();

  // Game State switch
  switch (state) {
    case 0:
      // TITLE SCREEN
      titlescreen();
      break;
    case 1:
      // GAME PLAY
      draw_vines(animFrame);
      // Branch Spawn logic
      spawnTimer++;
      if (spawnTimer == 32) {
        spawnBranch();
        spawnTimer = 0;
      }
      ab.setCursor(100, 30);
      ab.println(player.getY());
      if (ab.justPressed(LEFT_BUTTON)) {
        player.jump();
      }
      if (ab.justPressed(A_BUTTON)) {
        branches[0].spawn();
      }
      for (int i = 0; i < 6; i++) {
        if (branches[i].getActive()) {
          if (animate) branches[i].update();
          branches[i].draw();
        }
      }
      if (animate) player.update();
      player.draw();
      if (branchCollisionCheck()) {
        //player.fall();
        animate = false;
      }
      if (player.getX() < -50) {
        state = 2;
      }
      break;
    case 2:
      // GAME OVER
      ab.println("GAME OVER");
      if (ab.justPressed(A_BUTTON)) {
        resetGame();
      }
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
  if (animate) {
    if (animFrame < 7) {
      animFrame++;
    } else {
      animFrame = 0;
    }
  }
  
  for (int i = 0; i <= 128; i += 8) {
    Sprites::drawOverwrite(i - animFrame, 0, tree, 0);
    Sprites::drawOverwrite(i - animFrame, 61, treeR, 0);
  }
}

bool branchCollisionCheck() {
  for (int i = 0; i < MAX_BRANCHES; i++) {
    if (branches[i].getActive()) {
      if (player.getX() < branches[i].getX() + branches[i].getHeight() &&
          player.getX() + 16 > branches[i].getX() + 3 &&
          player.getY() < branches[i].getY() + branches[i].getLength() &&
          player.getY() + 16 > branches[i].getY()) 
      { 
        Serial.println("Player X:" + String(player.getX()));
        Serial.println("Player Y:" + String(player.getY()));
        Serial.println("Branch X:" + String(branches[i].getX()));
        Serial.println("Branch Y:" + String(branches[i].getY()));
        Serial.println("----------------------");
        ab.setRGBled(100,0,0);
        return true;
      }
    }
  }

  return false;
}

void resetGame() {
  player.reset();
  for (int i = 0; i < MAX_BRANCHES; i++) {
    branches[i].reset();
  }
  animate = true;
  state = 1;
}

int spawnBranch() {
  for (int i = 0; i < MAX_BRANCHES; i++) {
    if (!branches[i].getActive()) {
      branches[i].spawn();
      Serial.println("Spawned branch " + String(i));
      return 0;   
    }
  }
}


