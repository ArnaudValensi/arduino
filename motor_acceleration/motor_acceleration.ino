#define MOTOR_LEFT		0
#define MOTOR_RIGHT		1
#define MAX_SPEED		255
#define MIN_SPEED		40
#define ACCELERATION_DELAY	10

// #define CMD_LEFT_START		'd'
// #define CMD_RIGHT_START		'g'
// #define CMD_LEFT_STOP		's'
// #define CMD_RIGHT_STOP		'h'
// #define CMD_STOP		' '
// #define CMD_FORWARD		'r'
// #define CMD_BACKWARD		'f'


// #define ENABLE_A		5
// #define ENABLE_B		6
#define INA_1			5
#define INA_2			6
#define INB_1			9
#define INB_2			10

#define DIR_STOP		0
#define DIR_FORWARD		1
#define DIR_BACKWARD		2
#define DIR_LEFT		3
#define DIR_RIGHT		4

//--------------------------------------------------------
// TYPE DEFINITION
//--------------------------------------------------------
struct Direction
{
  int in[4];
};

struct DirectionMap
{
  char      key;
  Direction dir;
};

typedef struct {
  Direction	dirSpeed;
} t_motor;

//--------------------------------------------------------
// INIT VARIABLE
//--------------------------------------------------------
Direction forward  = { { 1, 0, 1, 0 } };
Direction backward = { { 0, 1, 0, 1 } };
Direction left     = { { 0, 1, 1, 0 } };
Direction right    = { { 1, 0, 0, 1 } };
Direction stand    = { { 0, 0, 0, 0 } };

DirectionMap dirMap[] =
{
  { 'f', stand },
  { 'w', forward },
  { 's', backward },
  { 'a', left },
  { 'd', right },
  { 0, NULL }
};

Direction *dir;

t_motor motor;

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
void setup() {
  Serial.begin(9600);
  // pinMode(ENABLE_A, OUTPUT);
  // pinMode(ENABLE_B, OUTPUT);
  pinMode(INA_1, OUTPUT);
  pinMode(INA_2, OUTPUT);
  pinMode(INB_1, OUTPUT);
  pinMode(INB_2, OUTPUT);

  // analogWrite(ENABLE_A, 255);
  // analogWrite(ENABLE_B, 255);
}

void loop() {
  int			buffer;
  struct Direction	*dir;

  if (Serial.available() > 0) {
    buffer = Serial.read();

    if ((dir = getDir((char) buffer)) != NULL)
      startMotor(*dir);
  }
  run();
}

//--------------------------------------------------------
// MOTOR CONTROL
//--------------------------------------------------------
void run() {
  acceleration();
}

void startMotor(struct Direction &dir) {
  motor.dirSpeed = dir;
  for (int i = 0; i < 4; ++i) {
    if (motor.dirSpeed.in[i] == 1)
      motor.dirSpeed.in[i] = MIN_SPEED + 1;
  }
}

void acceleration() {
  for (int i = 0; i < 4; ++i) {
    if (motor.dirSpeed.in[i] > 0 && motor.dirSpeed.in[i] < 254)
      (motor.dirSpeed.in[i])++;
  }
  move(motor.dirSpeed);
  delay(ACCELERATION_DELAY);
}

void move(struct Direction &dir)
{
  analogWrite(INA_1, dir.in[0]);
  analogWrite(INA_2, dir.in[1]);
  analogWrite(INB_1, dir.in[2]);
  analogWrite(INB_2, dir.in[3]);
}
