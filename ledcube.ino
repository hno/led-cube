#include <protothreads.h>

/*
  4x4x4 LED Cube
  Connection Setup: 
*/
const int column[4][4]={{1,0,2,3},
                        {4,5,6,7},
                        {A5,A4,8,9},
                        {13,12,11,10}
};
const int layer[4]={A2,A0,A1,A3};
bool cube[4][4][4];

#define LAYERON 0
#define LAYEROFF 1
#define COLUMNON 1
#define COLUMNOFF 0

const bool testCube[4][4][4] = {
  {{1,0,0,1},{0,0,0,0},{0,0,0,0},{1,0,0,1}},
  {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},  
  {{0,0,0,0},{0,1,1,0},{0,1,1,0},{0,0,0,0}},
  {{1,0,0,1},{0,0,0,0},{0,0,0,0},{1,0,0,1}},
};

pt ptDisplay;
int displayThread(struct pt *pt)
{
  PT_BEGIN(pt);
  static int x,y,z;
  for (;;) {
    for (y = 0; y < 4; y++) {
      for (x = 0; x < 4; x++) {
        for (z = 0; z < 4; z++) {
          digitalWrite(column[x][z], cube[y][x][z] ? COLUMNON : COLUMNOFF);
        }
      }
      digitalWrite(layer[y], LAYERON);
      PT_YIELD(pt);
      digitalWrite(layer[y], LAYEROFF);
    }
  }
  PT_END(pt);
}

pt ptEffects;
int effectsThread(struct pt *pt)
{
  PT_BEGIN(pt);
  memcpy(cube, testCube, sizeof(cube));
  PT_END(pt);
}

void setup()
{
  //setting rows to ouput
  for(int x = 0; x<4; x++)
  {
    for (int z = 0; z<4; z++) {
      pinMode(column[x][z], OUTPUT);
    }
  }
  //setting layers to output
  for(int i = 0; i<4; i++)
  {
    pinMode(layer[i], OUTPUT);
  }
  // Clear the cube
  memset(cube, 0, sizeof(cube));
  // Initialize threads
  PT_INIT(&ptDisplay);
  PT_INIT(&ptEffects);
}

 
void loop() {
  PT_SCHEDULE(displayThread(&ptDisplay));
  PT_SCHEDULE(effectsThread(&ptEffects));
}
