#define USE_TIMER_1 true

#include <TimerInterrupt.h>

/*
  4x4x4 LED Cube
  Connection Setup:
*/
const int column[4][4] = {{1, 0, 2, 3},
  {4, 5, 6, 7},
  {A5, A4, 8, 9},
  {13, 12, 11, 10}
};
const int layer[4] = {A2, A0, A1, A3};
bool cube[4][4][4];

#define LAYERON 0
#define LAYEROFF 1
#define COLUMNON 1
#define COLUMNOFF 0

void displayIRQ()
{
  static int y = 4 - 1;
  digitalWrite(layer[y], LAYEROFF);
#if 1
  y = y < 4 - 1 ? y + 1 : 0;
#else
  y += 1;
  if (y > 4 - 1)
    y = 0;
#endif
  for (int x = 0; x < 4; x++) {
    for (int z = 0; z < 4; z++) {
      digitalWrite(column[x][z], cube[y][x][z] ? COLUMNON : COLUMNOFF);
    }
  }
  digitalWrite(layer[y], LAYERON);
}

void setup()
{
  //setting layers to output
  for (int y = 0; y < 4; y++)
  {
    pinMode(layer[y], OUTPUT);
    digitalWrite(layer[y], LAYEROFF);
  }
  //setting rows to ouput
  for (int x = 0; x < 4; x++)
  {
    for (int z = 0; z < 4; z++) {
      pinMode(column[x][z], OUTPUT);
      digitalWrite(column[x][z], COLUMNOFF);
    }
  }
  // Clear the cube
  clear();

  ITimer1.init();
  ITimer1.attachInterrupt(100.0 * 4, displayIRQ);
}

void clear()
{
  memset(cube, 0, sizeof(cube));
}

void line(int x, int y, int z, int x2, int y2, int z2)
{
  int dx = abs(x2 - x);
  int xs = x2 > x ? 1 : -1;
  int dy = abs(y2 - y);
  int ys = y2 > y ? 1 : -1;
  int dz = abs(z2 - z);
  int zs = z2 > z ? 1 : -1;

  cube[y][x][z] = 1;
  if (dx >= dy && dx >= dz) {
    int py = 2 * dy - dx;
    int pz = 2 * dz - dx;
    while (x != x2) {
      x += xs;
      if (py >= 0) {
        y += ys;
        py -= 2 * dx;
      }
      if (pz >= 0) {
        z += zs;
        pz -= 2 * dx;
      }
      py += 2 * dy;
      pz += 2 * dz;
      cube[y][x][z] = 1;
    }
  }
  else if (dy >= dx && dy >= dz) {
    int px = 2 * dx - dy;
    int pz = 2 * dz - dy;
    while (y != y2) {
      y += ys;
      if (px >= 0) {
        x += xs;
        px -= 2 * dy;
      }
      if (pz >= 0) {
        z += zs;
        pz -= 2 * dy;
      }
      px += 2 * dx;
      pz += 2 * dz;
      cube[y][x][z] = 1;
    }
  }
  else {
    int py = 2 * dy - dz;
    int px = 2 * dx - dz;
    while (z != z2) {
      z += zs;
      if (py >= 0) {
        y += ys;
        py -= 2 * dz;
      }
      if (px >= 0) {
        x += xs;
        px -= 2 * dz;
      }
      py += 2 * dy;
      px += 2 * dx;
      cube[y][x][z] = 1;
    }
  }
}

void box(int x1, int y1, int z1, int x2, int y2, int z2)
{
  line(x1, y1, z1, x2, y1, z1);
  line(x2, y1, z1, x2, y2, z1);
  line(x2, y2, z1, x1, y2, z1);
  line(x1, y2, z1, x1, y1, z1);
  line(x1, y1, z1, x1, y1, z2);
  line(x2, y1, z1, x2, y1, z2);
  line(x2, y2, z1, x2, y2, z2);
  line(x1, y2, z1, x1, y2, z2);
  line(x1, y1, z2, x2, y1, z2);
  line(x2, y1, z2, x2, y2, z2);
  line(x2, y2, z2, x1, y2, z2);
  line(x1, y2, z2, x1, y1, z2);
}

void draw_char(const bool *data, int z)
{
  for (int x = 0; x < 4; x++) {
    for (int y = 0; y < 4; y++) {
      cube[y][x][z] = data[x+y*4];
    }
  }
}

const bool char_gottfrid[][16] = {
    {0,0,0,0,
     0,0,0,0,
     0,0,0,0,
     0,0,0,0},
    {0,1,1,0,
     1,0,0,0,
     1,0,1,1,
     0,1,1,0},
    {0,1,1,0,
     1,0,0,1,
     1,0,0,1,
     0,1,1,0},
    {1,1,1,1,
     0,1,1,0,
     0,1,1,0,
     0,1,1,0},
    {1,1,1,1,
     0,1,1,0,
     0,1,1,0,
     0,1,1,0},
    {1,1,1,1,
     1,0,0,0,
     1,1,1,1,
     1,0,0,0},
    {1,1,1,0,
     1,0,0,1,
     1,1,1,0,
     1,0,0,1},
    {0,1,1,0,
     0,1,1,0,
     0,1,1,0,
     0,1,1,0},
    {1,1,1,0,
     1,0,0,1,
     1,0,0,1,
     1,1,1,0},
    {0,0,0,0,
     0,0,0,0,
     0,0,0,0,
     0,0,0,0},
};

void gottfrid()
{
  clear();
  int z = 0;
  clear();
  delay(300);
  for (int i = 0; i < 8; i++) {
    draw_char(char_gottfrid[i+1], z);
    delay(1000);
    clear();
    delay(10);
  }
  clear();
  delay(300);
}

void scroll_gottfrid()
{
  clear();
  for (int i = 0; i < 8; i++) {
    for (int z = 0; z < 4; z++) {
      clear();
      draw_char(char_gottfrid[i+1], 3-z);
      delay(200);
    }
  }
}

void repeat(int n, void (*fn)())
{
  while (n-- > 0)
    fn();
}

void angled_lineY(int a, int y)
{
  while (a >= 6)
    a -= 6;
  if (a < 4) {
    int d = a;
    line(d, y, 0,  3 - d, y, 3);
  } else {
    int d = a - 3;
    line(3, y, d,  0, y, 3 - d);
  }
}

void propellerY()
{

  for (int a = 0; a < 6; a++) {
    clear();
    for (int y = 0; y < 4; y++) {
      angled_lineY(a + y, y);
    }
    delay(100);
  }
}

void angled_lineZ(int a, int z)
{
  while (a >= 6)
    a -= 6;
  if (a < 4) {
    int d = a;
    line(d, 0, z,  3 - d, 3, z);
  } else {
    int d = a - 3;
    line(3, d, z,  0, 3 - d, z);
  }
}

void propellerZ()
{

  for (int a = 0; a < 6; a++) {
    clear();
    for (int z = 0; z < 4; z++) {
      angled_lineZ(a, z);
    }
    delay(100);
  }
}

void angled_lineX(int a, int x)
{
  while (a >= 6)
    a -= 6;
  if (a < 4) {
    int d = a;
    line(x, d, 0,  x, 3 - d, 3);
  } else {
    int d = a - 3;
    line(x, 3, d,  x, 0, 3 - d);
  }
}

void propellerX()
{

  for (int a = 0; a < 6; a++) {
    clear();
    for (int z = 0; z < 4; z++) {
      angled_lineX(a, z);
    }
    delay(100);
  }
}

void cross()
{
  clear();
  line(0, 0, 0, 3, 3, 3);
  line(0, 3, 0, 3, 0, 3);
  line(3, 0, 0, 0, 3, 3);
  line(3, 3, 0, 0, 0, 3);
}

void shrink_box()
{
  for (int y = 0; y < 4; y++) {
    clear();
    box(0, y, 0, 3, 3, 3);
    delay(100);
  }
  for (int y = 3; y >= 0; y--) {
    clear();
    box(0, y, 0, 3, 3, 3);
    delay(100);
  }
  for (int y = 3; y >= 0; y--) {
    clear();
    box(0, 0, 0, 3, y, 3);
    delay(100);
  }
  for (int y = 0; y < 4; y++) {
    clear();
    box(0, 0, 0, 3, y, 3);
    delay(100);
  }
}

void flood()
{
  for (int i = 0; i < 500; i++)
  {
    cube[rand() & 3][rand() & 3][rand() & 3] = 1;
    delay(10);
  }    
  memset(cube, 1, sizeof(cube));
}
void decay()
{
  for (int i = 0; i < 500; i++)
  {
    cube[rand() & 3][rand() & 3][rand() & 3] = 0;
    delay(10);
  }
  clear();
}

void random_flashes()
{
  for (int i = 1000; i > 0; i -= (i >> 6)+1)
  {
    clear();
    cube[rand() & 3][rand() & 3][rand() & 3] = 1;
    delay(i);
  }
  clear(); 
}

void random_xor()
{
  for (int i = 0; i < 300; i++) {
    cube[rand() & 3][rand() & 3][rand() & 3] ^= 1;
    delay(60);
  }
}

void loop() {
  gottfrid();
  scroll_gottfrid();
  cross();
  delay(1000);
  clear();
  box(0, 0, 0, 3, 3, 3);
  delay(1000);
  repeat(4, shrink_box);
  repeat(5, propellerY);
  repeat(5, propellerZ);
  repeat(5, propellerX);
  clear();
  flood();
  delay(1000);
  random_xor();
  decay();
  random_flashes();
}
