#define MOTOR_LEFT		0
#define MOTOR_RIGHT		1
#define PIN_MOTOR_LEFT		5
#define PIN_MOTOR_RIGHT		6
#define MAX_SPEED		255
#define MIN_SPEED		40
#define CMD_LEFT_START		'a'
#define CMD_RIGHT_START		'b'
#define CMD_LEFT_STOP		'c'
#define CMD_RIGHT_STOP		'd'
#define ACCELERATION_DELAY	10

//-------------------------------------
// Motor control

typedef struct {
  bool	inAcceleration;
  int	speed;
  int	pin;
} t_motor;

t_motor motor[] = {
  { false, 0, PIN_MOTOR_LEFT  },
  { false, 0, PIN_MOTOR_RIGHT }
};

void run() {
  acceleration(MOTOR_LEFT);
  acceleration(MOTOR_RIGHT);
}

void startMotor(int motorNum) {
  if (motorNum == MOTOR_LEFT || motorNum == MOTOR_RIGHT) {

    Serial.print("Starting motor: ");
    Serial.println(motorNum);

    motor[motorNum].inAcceleration = true;
    motor[motorNum].speed = MIN_SPEED;
  }
}

void acceleration(int motorNum) {
  if (motorNum != MOTOR_LEFT && motorNum != MOTOR_RIGHT)
    return;

  for (int i = 0; i < 2; ++i) {
    if (motor[i].inAcceleration) {
      motor[i].speed++;
      analogWrite(motor[motorNum].pin, motor[motorNum].speed);
      if (motor[i].speed >= MAX_SPEED)
	motor[i].inAcceleration = false;
    }
  }

  delay(ACCELERATION_DELAY);
}

//-------------------------------------
//
void setup() {
  Serial.begin(9600);
  pinMode(PIN_MOTOR_LEFT, OUTPUT);
  pinMode(PIN_MOTOR_RIGHT, OUTPUT);
}

void loop() {
  char buffer;

  if (Serial.available() > 0) {
    buffer = Serial.read();

    switch(buffer) {
    case CMD_LEFT_START:
      // analogWrite(PIN_MOTOR_LEFT, 100);
      startMotor(MOTOR_LEFT);
      break;
    case CMD_RIGHT_START:
      // analogWrite(PIN_MOTOR_RIGHT, 100);
      startMotor(MOTOR_RIGHT);
      break;
    case CMD_LEFT_STOP:
      analogWrite(MOTOR_LEFT, 0);
      break;
    case CMD_RIGHT_STOP:
      analogWrite(MOTOR_RIGHT, 0);
      break;
    }
  }
  run();
}
