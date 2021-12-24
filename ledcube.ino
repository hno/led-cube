/*
  4x4x4 LED Cube
  Connection Setup: 
*/
const int column[16]={1,0,2,3,
                        4,5,6,7,
                        A5,A4,8,9,
                        13,12,11,10};
const int xy[4][4] = {
                        {1,0,2,3},
                        {4,5,6,7},
                        {A5,A4,8,9},
                        {13,12,11,10}
};
const int layer[4]={A2,A0,A1,A3};

int time = 250;

#define LAYERON 0
#define LAYEROFF 1
#define COLUMNON 1
#define COLUMNOFF 0

void setup()
{
  //setting rows to ouput
  for(int i = 0; i<16; i++)
  {
    pinMode(column[i], OUTPUT);
  }
  //setting layers to output
  for(int i = 0; i<4; i++)
  {
    pinMode(layer[i], OUTPUT);
  }
  //seeding random for random pattern
  randomSeed(analogRead(10));
}
//xxxxxxxxxxxxxxxxxxxxFUNCTION LOOPxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

void loop()
{
  oneByOne();
  turnEverythingOff();//turn all off
  flickerOn();
  turnEverythingOn();//turn all on
  delay(time);
  turnOnAndOffAllByLayerUpAndDownNotTimed();
  layerstompUpAndDown();
  turnOnAndOffAllByColumnSideways();
  delay(time);
  aroundEdgeDown();
  turnEverythingOff();
  randomflicker();
  randomRain();
  diagonalRectangle();
  goThroughAllLedsOneAtATime();
  propeller();
  spiralInAndOut();
  flickerOff();
  turnEverythingOff();
  delay(2000);
}


//xxxxxxxxxxxxxxxxxxxxFUNCTIONSxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
//xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx

///////////////////////////////////////////////////////////Repeat an effect N times
void repeat(int n, void (*fn)())
{
  for (int i = 0; i < n; i++)
    fn();
}

///////////////////////////////////////////////////////////Test one led at a time
void oneByOne()
{
  turnEverythingOff();
  for (int i = 0; i < 4; i++) {
    digitalWrite(layer[i], LAYERON);
    for (int x = 0; x < 16; x++) {
      digitalWrite(column[x], COLUMNON);
      delay(50);
      digitalWrite(column[x], COLUMNOFF);
    }
    digitalWrite(layer[i], LAYEROFF);
  }
}

///////////////////////////////////////////////////////////turn all off
void turnEverythingOff()
 {
   for(int i = 0; i<16; i++)
   {
     digitalWrite(column[i], COLUMNOFF);
   }
   for(int i = 0; i<4; i++)
   {
     digitalWrite(layer[i], LAYEROFF);
   }
 }
 
////////////////////////////////////////////////////////////turn all on
void turnEverythingOn()
{
  for(int i = 0; i<16; i++)
  {
    digitalWrite(column[i], COLUMNON);
  }
  //turning on layers
  for(int i = 0; i<4; i++)
  {
    digitalWrite(layer[i], LAYERON);
  }
}
///////////////////////////////////////////////////////turn columns off
void turnColumnsOff()
{
  for(int i = 0; i<16; i++)
  {
    digitalWrite(column[i], COLUMNOFF);
  }
}
/////////////////////////////////////////////////////////////flicker on
void flickerOn()
{
  int i = 150;
  while(i != 0)
  {
    turnEverythingOn();
    delay(i);
    turnEverythingOff();
    delay(i);
    i-= 5;
  }
}
//////////////turn everything on and off by layer up and down NOT TIMED
void turnOnAndOffAllByLayerUpAndDownNotTimed()
{
  int x = 75;
  for(int i = 5; i != 0; i--)
  {
    turnEverythingOn();
    for(int i = 4; i!=0; i--)
    {
      digitalWrite(layer[i-1], LAYEROFF);
      delay(x);
    }
    for(int i = 0; i<4; i++)
    {
      digitalWrite(layer[i], LAYERON);
      delay(x);
    }
      for(int i = 0; i<4; i++)
    {
      digitalWrite(layer[i], LAYEROFF);
      delay(x);
    }
    for(int i = 4; i!=0; i--)
    {
      digitalWrite(layer[i-1], LAYERON);
      delay(x);
    }
  }
}
//////////////////////////turn everything on and off by column sideways
void turnOnAndOffAllByColumnSideways()
{
  int t = 75;
  turnEverythingOff();
  //turn on layers
  for(int i = 0; i<4; i++)
  {
    digitalWrite(layer[i], LAYERON);
  }
  for(int y = 0; y<3; y++)
  {
    //turn on 0-3
    for(int i = 0; i<4; i++)
    {
      digitalWrite(column[i], COLUMNON);
      delay(t);
    }
    //turn on 4-7
    for(int i = 4; i<8; i++)
    {
      digitalWrite(column[i], COLUMNON);
      delay(t);
    }
    //turn on 8-11
    for(int i = 8; i<12; i++)
    {
      digitalWrite(column[i], COLUMNON);
      delay(t);
    }
    //turn on 12-15
    for(int i = 12; i<16; i++)
    {
      digitalWrite(column[i], COLUMNON);
      delay(t);
    }
    //turn off 0-3
    for(int i = 0; i<4; i++)
    {
      digitalWrite(column[i], COLUMNOFF);
      delay(t);
    }
    //turn off 4-7
    for(int i = 4; i<8; i++)
    {
      digitalWrite(column[i], COLUMNOFF);
      delay(t);
    }
    //turn off 8-11
    for(int i = 8; i<12; i++)
    {
      digitalWrite(column[i], COLUMNOFF);
      delay(t);
    }
    //turn off 12-15
    for(int i = 12; i<16; i++)
    {
      digitalWrite(column[i], COLUMNOFF);
      delay(t);
    }
    //turn on 12-15
    for(int i = 12; i<16; i++)
    {
      digitalWrite(column[i], COLUMNON);
      delay(t);
    }
    //turn on 8-11
    for(int i = 8; i<12; i++)
    {
      digitalWrite(column[i], COLUMNON);
      delay(t);
    }
    //turn on 4-7
    for(int i = 4; i<8; i++)
    {
      digitalWrite(column[i], COLUMNON);
      delay(t);
    }
    //turn on 0-3
    for(int i = 0; i<4; i++)
    {
      digitalWrite(column[i], COLUMNON);
      delay(t);
    }
    //turn off 12-15
    for(int i = 12; i<16; i++)
    {
      digitalWrite(column[i], COLUMNOFF);
      delay(t);
    }
    //turn off 8-11
    for(int i = 8; i<12; i++)
    {
      digitalWrite(column[i], COLUMNOFF);
      delay(t);
    }
    //turn off 4-7
    for(int i = 4; i<8; i++)
    {
      digitalWrite(column[i], COLUMNOFF);
      delay(t);
    }
    //turn off 0-3
    for(int i = 0; i<4; i++)
    {
      digitalWrite(column[i], COLUMNOFF);
      delay(t);
    }
  }
}

/////////////////////////////////////////up and down single layer stomp
void layerstompUpAndDown()
{
  int x = 75;
  for(int i = 0; i<4; i++)
  {
    digitalWrite(layer[i], LAYEROFF);
  }
  for(int y = 0; y<5; y++)
  {
    for(int count = 0; count<1; count++)
    { 
      for(int i = 0; i<4; i++)
      {
        digitalWrite(layer[i], LAYERON);
        delay(x);
        digitalWrite(layer[i], LAYEROFF);
      }
      for(int i = 4; i !=0; i--)
      {
        digitalWrite(layer[i-1], LAYERON);
        delay(x);
        digitalWrite(layer[i-1], LAYEROFF);
      }
    }
    for(int i = 0; i<4; i++)
    {
      digitalWrite(layer[i], LAYERON);
      delay(x);
    }
    for(int i = 4; i!=0; i--)
    {
      digitalWrite(layer[i-1], LAYEROFF);
      delay(x);
    }
  }
}
////////////////////////////////////////////////////////////flicker off
void flickerOff()
{
  turnEverythingOn();
  for(int i = 0; i!= 150; i+=5)
  {
    turnEverythingOff();
    delay(i+50);
    turnEverythingOn();
    delay(i);
  }
}

// 0 1 2 3
// 4 5 6 7
// 8 9 10 11
// 12 13 14 15

// 0 4 8 12 13 14 15 11 7 3 2 1
///////////////////////////////////////////around edge of the cube down
void aroundEdgeDown()
{
  for(int x = 200; x != 0; x -=50)
  {
    turnEverythingOff();
    for(int i = 4; i != 0; i--)
    {
      digitalWrite(layer[i-1], LAYERON);
      digitalWrite(column[5], COLUMNON);
      digitalWrite(column[6], COLUMNON);
      digitalWrite(column[9], COLUMNON);
      digitalWrite(column[10], COLUMNON);
      
      digitalWrite(column[0], COLUMNON);
      delay(x);
      digitalWrite(column[0], COLUMNOFF);
      digitalWrite(column[4], COLUMNON);
      delay(x);
      digitalWrite(column[4], COLUMNOFF);
      digitalWrite(column[8], COLUMNON);
      delay(x);
      digitalWrite(column[8], COLUMNOFF);
      digitalWrite(column[12], COLUMNON);
      delay(x);
      digitalWrite(column[12], COLUMNOFF);
      digitalWrite(column[13], COLUMNON);
      delay(x);
      digitalWrite(column[13], COLUMNOFF);
      digitalWrite(column[14], COLUMNON);
      delay(x);
      digitalWrite(column[14], COLUMNOFF);
      digitalWrite(column[15], COLUMNON);
      delay(x);
      digitalWrite(column[15], COLUMNOFF);
      digitalWrite(column[11], COLUMNON);
      delay(x);
      digitalWrite(column[11], COLUMNOFF);
      digitalWrite(column[7], COLUMNON);
      delay(x);
      digitalWrite(column[7], COLUMNOFF);
      digitalWrite(column[3], COLUMNON);
      delay(x);
      digitalWrite(column[3], COLUMNOFF);
      digitalWrite(column[2], COLUMNON);
      delay(x);
      digitalWrite(column[2], COLUMNOFF);
      digitalWrite(column[1], COLUMNON);
      delay(x);
      digitalWrite(column[1], COLUMNOFF);
    }
  }
}
/////////////////////////////////////////////////////////random flicker
void randomflicker()
{
  turnEverythingOff();
  int x = 10;
  for(int i = 0; i !=750; i+=2)
  {
  int randomLayer = random(0,4);
  int randomColumn = random(0,16);
  
  digitalWrite(layer[randomLayer], LAYERON);
  digitalWrite(column[randomColumn], COLUMNON);
  delay(x);
  digitalWrite(layer[randomLayer], LAYEROFF);
  digitalWrite(column[randomColumn], COLUMNOFF);
  delay(x); 
  }
}
////////////////////////////////////////////////////////////random rain
void randomRain()
{
  turnEverythingOff();
  int x = 30;
  int x0 = 50;
  for(int i = 0; i!=60; i+=2)
  {
    int randomColumn = random(0,16);
    digitalWrite(column[randomColumn], COLUMNON);
    digitalWrite(layer[0], LAYERON);
    delay(x0);
    digitalWrite(layer[0], LAYEROFF);
    digitalWrite(layer[1], LAYERON);
    delay(x);
    digitalWrite(layer[1], LAYEROFF);
    digitalWrite(layer[2], LAYERON);
    delay(x);
    digitalWrite(layer[2], LAYEROFF);
    digitalWrite(layer[3], LAYERON);
    delay(x0);
    digitalWrite(layer[3], LAYEROFF);
    digitalWrite(column[randomColumn], COLUMNOFF);
  }
}
/////////////////////////////////////////////////////diagonal rectangle
void diagonalRectangle()
{
  int x = 350;
  turnEverythingOff();
  for(int count = 0; count<5; count++)
  {
    //top left
    for(int i = 0; i<8; i++)
    {
      digitalWrite(column[i], COLUMNON);
    }
    digitalWrite(layer[3], LAYERON);
    digitalWrite(layer[2], LAYERON);
    delay(x);
    turnEverythingOff();
    //middle middle
    for(int i = 4; i<12; i++)
    {
      digitalWrite(column[i], COLUMNON);
    }
    digitalWrite(layer[1], LAYERON);
    digitalWrite(layer[2], LAYERON);
    delay(x);
    turnEverythingOff();
    //bottom right
    for(int i = 8; i<16; i++)
    {
      digitalWrite(column[i], COLUMNON);
    }
    digitalWrite(layer[0], LAYERON);
    digitalWrite(layer[1], LAYERON);
    delay(x);
    turnEverythingOff();
    //bottom middle
    for(int i = 4; i<12; i++)
    {
      digitalWrite(column[i], COLUMNON);
    }
    digitalWrite(layer[0], LAYERON);
    digitalWrite(layer[1], LAYERON);
    delay(x);
    turnEverythingOff();
    //bottom left
    for(int i = 0; i<8; i++)
    {
      digitalWrite(column[i], COLUMNON);
    }
    digitalWrite(layer[0], LAYERON);
    digitalWrite(layer[1], LAYERON);
    delay(x);
    turnEverythingOff();
    //middle middle
    for(int i = 4; i<12; i++)
    {
      digitalWrite(column[i], COLUMNON);
    }
    digitalWrite(layer[1], LAYERON);
    digitalWrite(layer[2], LAYERON);
    delay(x);
    turnEverythingOff();
    //top right
    for(int i = 8; i<16; i++)
    {
      digitalWrite(column[i], COLUMNON);
    }
    digitalWrite(layer[2], LAYERON);
    digitalWrite(layer[3], LAYERON);
    delay(x);
    turnEverythingOff();
    //top middle
    for(int i = 4; i<12; i++)
    {
      digitalWrite(column[i], COLUMNON);
    }
    digitalWrite(layer[2], LAYERON);
    digitalWrite(layer[3], LAYERON);
    delay(x);
    turnEverythingOff();
  }
  //top left
  for(int i = 0; i<8; i++)
  {
    digitalWrite(column[i], COLUMNON);
  }
  digitalWrite(layer[3], LAYERON);
  digitalWrite(layer[2], LAYERON);
  delay(x);
  turnEverythingOff();
}
//////////////////////////////////////////////////////////////propeller
void propeller()
{
  turnEverythingOff();
  int x = 90;
  for(int y = 4; y>0; y--)
  {
    for(int i = 0; i<6; i++)
    {
      //turn on layer
      digitalWrite(layer[y-1], LAYERON);
      //a1
      turnColumnsOff();
      digitalWrite(column[0], COLUMNON);
      digitalWrite(column[5], COLUMNON);
      digitalWrite(column[10], COLUMNON);
      digitalWrite(column[15], COLUMNON);
      delay(x);
      //b1
      turnColumnsOff();
      digitalWrite(column[4], COLUMNON);
      digitalWrite(column[5], COLUMNON);
      digitalWrite(column[10], COLUMNON);
      digitalWrite(column[11], COLUMNON);
      delay(x);
      //c1
      turnColumnsOff();
      digitalWrite(column[6], COLUMNON);
      digitalWrite(column[7], COLUMNON);
      digitalWrite(column[8], COLUMNON);
      digitalWrite(column[9], COLUMNON);
      delay(x);
      //d1
      turnColumnsOff();
      digitalWrite(column[3], COLUMNON);
      digitalWrite(column[6], COLUMNON);
      digitalWrite(column[9], COLUMNON);
      digitalWrite(column[12], COLUMNON);
      delay(x);
      //d2
      turnColumnsOff();
      digitalWrite(column[2], COLUMNON);
      digitalWrite(column[6], COLUMNON);
      digitalWrite(column[9], COLUMNON);
      digitalWrite(column[13], COLUMNON);
      delay(x);
      //d3
      turnColumnsOff();
      digitalWrite(column[1], COLUMNON);
      digitalWrite(column[5], COLUMNON);
      digitalWrite(column[10], COLUMNON);
      digitalWrite(column[14], COLUMNON);
      delay(x);
    }
  }
  //d4
  turnColumnsOff();
  digitalWrite(column[0], COLUMNON);
  digitalWrite(column[5], COLUMNON);
  digitalWrite(column[10], COLUMNON);
  digitalWrite(column[15], COLUMNON);
  delay(x);
}
//////////////////////////////////////////////////////spiral in and out
void spiralInAndOut()
{
  turnEverythingOn();
  int x = 60;
  for(int i = 0; i<6; i++)
  {
    //spiral in clockwise
    digitalWrite(column[0], COLUMNOFF);
    delay(x);
    digitalWrite(column[1], COLUMNOFF);
    delay(x);
    digitalWrite(column[2], COLUMNOFF);
    delay(x);
    digitalWrite(column[3], COLUMNOFF);
    delay(x);
    digitalWrite(column[7], COLUMNOFF);
    delay(x);
    digitalWrite(column[11], COLUMNOFF);
    delay(x);
    digitalWrite(column[15], COLUMNOFF);
    delay(x);
    digitalWrite(column[14], COLUMNOFF);
    delay(x);
    digitalWrite(column[13], COLUMNOFF);
    delay(x);
    digitalWrite(column[12], COLUMNOFF);
    delay(x);
    digitalWrite(column[8], COLUMNOFF);
    delay(x);
    digitalWrite(column[4], COLUMNOFF);
    delay(x);
    digitalWrite(column[5], COLUMNOFF);
    delay(x);
    digitalWrite(column[6], COLUMNOFF);
    delay(x);
    digitalWrite(column[10], COLUMNOFF);
    delay(x);
    digitalWrite(column[9], COLUMNOFF);
    delay(x);
    ///////////////////////////////////////spiral out counter clockwise
    digitalWrite(column[9], COLUMNON);
    delay(x);
    digitalWrite(column[10], COLUMNON);
    delay(x);
    digitalWrite(column[6], COLUMNON);
    delay(x);
    digitalWrite(column[5], COLUMNON);
    delay(x);
    digitalWrite(column[4], COLUMNON);
    delay(x);
    digitalWrite(column[8], COLUMNON);
    delay(x);
    digitalWrite(column[12], COLUMNON);
    delay(x);
    digitalWrite(column[13], COLUMNON);
    delay(x);
    digitalWrite(column[14], COLUMNON);
    delay(x);
    digitalWrite(column[15], COLUMNON);
    delay(x);
    digitalWrite(column[11], COLUMNON);
    delay(x);
    digitalWrite(column[7], COLUMNON);
    delay(x);
    digitalWrite(column[3], COLUMNON);
    delay(x);
    digitalWrite(column[2], COLUMNON);
    delay(x);
    digitalWrite(column[1], COLUMNON);
    delay(x);
    digitalWrite(column[0], COLUMNON);
    delay(x);
    ///////////////////////////////////////spiral in counter clock wise
    digitalWrite(column[0], COLUMNOFF);
    delay(x);
    digitalWrite(column[4], COLUMNOFF);
    delay(x);
    digitalWrite(column[8], COLUMNOFF);
    delay(x);
    digitalWrite(column[12], COLUMNOFF);
    delay(x);
    digitalWrite(column[13], COLUMNOFF);
    delay(x);
    digitalWrite(column[14], COLUMNOFF);
    delay(x);
    digitalWrite(column[15], COLUMNOFF);
    delay(x);
    digitalWrite(column[11], COLUMNOFF);
    delay(x);
    digitalWrite(column[7], COLUMNOFF);
    delay(x);
    digitalWrite(column[3], COLUMNOFF);
    delay(x);
    digitalWrite(column[2], COLUMNOFF);
    delay(x);
    digitalWrite(column[1], COLUMNOFF);
    delay(x);
    digitalWrite(column[5], COLUMNOFF);
    delay(x);
    digitalWrite(column[9], COLUMNOFF);
    delay(x);
    digitalWrite(column[10], COLUMNOFF);
    delay(x);
    digitalWrite(column[6], COLUMNOFF);
    delay(x);
    //////////////////////////////////////////////spiral out clock wise
    digitalWrite(column[6], COLUMNON);
    delay(x);
    digitalWrite(column[10], COLUMNON);
    delay(x);
    digitalWrite(column[9], COLUMNON);
    delay(x);
    digitalWrite(column[5], COLUMNON);
    delay(x);
    digitalWrite(column[1], COLUMNON);
    delay(x);
    digitalWrite(column[2], COLUMNON);
    delay(x);
    digitalWrite(column[3], COLUMNON);
    delay(x);
    digitalWrite(column[7], COLUMNON);
    delay(x);
    digitalWrite(column[11], COLUMNON);
    delay(x);
    digitalWrite(column[15], COLUMNON);
    delay(x);
    digitalWrite(column[14], COLUMNON);
    delay(x);
    digitalWrite(column[13], COLUMNON);
    delay(x);
    digitalWrite(column[12], COLUMNON);
    delay(x);
    digitalWrite(column[8], COLUMNON);
    delay(x);
    digitalWrite(column[4], COLUMNON);
    delay(x);
    digitalWrite(column[0], COLUMNON);
    delay(x);
  }
}
//////////////////////////////////////go through all leds one at a time
void goThroughAllLedsOneAtATime()
{
  int x = 15;
  turnEverythingOff();
  for(int y = 0; y<5; y++)
  {
    //0-3
    for(int count = 4; count != 0; count--)
    {
      digitalWrite(layer[count-1], LAYERON);
      for(int i = 0; i<4; i++)
      {
        digitalWrite(column[i], COLUMNON);
        delay(x);
        digitalWrite(column[i], LAYERON);
        delay(x);
      }
    digitalWrite(layer[count-1], LAYEROFF);
    }
    //4-7
    for(int count = 0; count < 4; count++)
    {
      digitalWrite(layer[count], LAYERON);
      for(int i = 4; i<8; i++)
      {
        digitalWrite(column[i], COLUMNON);
        delay(x);
        digitalWrite(column[i], COLUMNOFF);
        delay(x);
      }
    digitalWrite(layer[count], LAYEROFF);
    }
    //8-11
    for(int count = 4; count != 0; count--)
    {
      digitalWrite(layer[count-1], LAYERON);
      for(int i = 8; i<12; i++)
      {
        digitalWrite(column[i], COLUMNON);
        delay(x);
        digitalWrite(column[i], COLUMNOFF);
        delay(x);
      }
    digitalWrite(layer[count-1], LAYEROFF);
    }
    //12-15
    for(int count = 0; count < 4; count++)
    {
      digitalWrite(layer[count], LAYERON);
      for(int i = 12; i<16; i++)
      {
        digitalWrite(column[i], COLUMNON);
        delay(x);
        digitalWrite(column[i], COLUMNOFF);
        delay(x);
      }
    digitalWrite(layer[count], LAYEROFF);
    }
  }
}
