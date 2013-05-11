#include <MeetAndroid.h>

#define ENABLE_A  5
#define ENABLE_B  6
#define INA_1     10
#define INA_2     11
#define INB_1     12
#define INB_2     13

//--------------------------------------------------------
// TYPE DEFINITION
//--------------------------------------------------------
struct Direction
{
  int ina_1;
  int ina_2;
  int inb_1;
  int inb_2;
};

struct DirectionMap
{
  char      key;
  Direction dir;
};

//--------------------------------------------------------
// INIT VARIABLE
//--------------------------------------------------------
Direction forward  = { HIGH, LOW, HIGH, LOW };
Direction backward = { LOW, HIGH, LOW, HIGH };
Direction left     = { LOW, HIGH, HIGH, LOW };
Direction right    = { HIGH, LOW, LOW, HIGH };
Direction stop     = { HIGH, HIGH, HIGH, HIGH};

struct DirectionMap dirMap[] =
{
  { 'f', stop },
  { 'w', forward },
  { 's', backward },
  { 'a', left },
  { 'd', right },
  { 0, NULL }
};

char buf;
struct Direction *dir;

MeetAndroid meetAndroid;

//--------------------------------------------------------
// MAP FUNCTION
//--------------------------------------------------------
struct Direction *getDir(char c)
{
  int i = 0;
  while (dirMap[i].key != 0)
  {
    if (dirMap[i].key == c)
      return &dirMap[i].dir;
    ++i;
  }
  return NULL;
}


//--------------------------------------------------------
// ARDUINO FUNCTIONS
//--------------------------------------------------------
void setup()
{
  // set the digital pin as output:
  pinMode(ENABLE_A, OUTPUT);
  pinMode(ENABLE_B, OUTPUT);
  pinMode(INA_1, OUTPUT);
  pinMode(INA_2, OUTPUT);
  pinMode(INB_1, OUTPUT);
  pinMode(INB_2, OUTPUT);

  Serial.begin(57600);
  // Serial.begin(9600);

  analogWrite(ENABLE_A, 255);
  analogWrite(ENABLE_B, 255);

  // meetAndroid.registerFunction(test, 'A');
  meetAndroid.registerFunction(avancer, 'a');
  meetAndroid.registerFunction(reculer, 'r');
  meetAndroid.registerFunction(droite, 'd');
  meetAndroid.registerFunction(gauche, 'g');
}

void loop()
{
  // move(dirMap[1].dir);
  meetAndroid.receive();


  // while (Serial.available() > 0)
  // {
  //   buf = Serial.read();
  //   Serial.print(buf);

  //   if ((dir = getDir(buf)) != NULL)
  //     move(*dir);
  //   else
  //     Serial.print("Bad key\n");
  // }
}

//--------------------------------------------------------
// MOTOR CONTROL
//--------------------------------------------------------
void move(struct Direction &dir)
{
  digitalWrite(INA_1, dir.ina_1);
  digitalWrite(INA_2, dir.ina_2);
  digitalWrite(INB_1, dir.inb_1);
  digitalWrite(INB_2, dir.inb_2);
}

void test(byte flag, byte numOfValues)
{
  move(dirMap[1].dir);

  // Serial.print("byte: ");
  // Serial.print(flag);
  // Serial.print("\nvalue: ");
  // Serial.print(numOfValues);
}

void avancer(byte flag, byte numOfValues)
{
  if(meetAndroid.getInt() == 0)
    move(dirMap[0].dir);
  else if(meetAndroid.getInt() > 0)
    move(dirMap[1].dir);
}

void reculer(byte flag, byte numOfValues)
{
  if(meetAndroid.getInt() == 0)
    move(dirMap[0].dir);
  else if(meetAndroid.getInt() > 0)
    move(dirMap[2].dir);
}

void gauche(byte flag, byte numOfValues)
{
  if(meetAndroid.getInt() == 0)
    move(dirMap[0].dir);
  else if(meetAndroid.getInt() > 0)
    move(dirMap[3].dir);
}

void droite(byte flag, byte numOfValues)
{
  if(meetAndroid.getInt() == 0)
    move(dirMap[0].dir);
  else if(meetAndroid.getInt() > 0)
    move(dirMap[4].dir);
}
