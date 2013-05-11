#define MOTOR_LEFT	5
#define MOTOR_RIGHT	6
#define MAX_SPEED	255
#define MIN_SPEED	40
#define CMD_LEFT_START	'a'
#define CMD_RIGHT_START	'b'
#define CMD_LEFT_STOP	'c'
#define CMD_RIGHT_STOP	'd'

//-------------------------------------
// Motor control
int i_left = 0;
int i_right = 0;
boolean isLeftAcceleration = false;
boolean isRightAcceleration = false;

void run() {
  acceleration(MOTOR_LEFT);
  acceleration(MOTOR_RIGHT);
}

void startMotor(int motor) {
  if (motor == MOTOR_LEFT) {
    isLeftAcceleration = true;
    acceleration(motor);
  }
  else if (motor == MOTOR_RIGHT) {
    isRightAcceleration = true;
    acceleration(motor);
  }
}

void acceleration(int motor) {
  if (isLeftAcceleration && motor == MOTOR_LEFT) {
    analogWrite(motor, i_left);
    i_left++;
    if (i_left >= MAX_SPEED)
      isLeftAcceleration = false;
  }
  else if (isRightAcceleration && motor == MOTOR_RIGHT) {
    analogWrite(motor, i_right);
    i_right++;
    if (i_right >= MAX_SPEED)
      isRightAcceleration = false;
  }
  delay(10);
}

//-------------------------------------
//
void setup() {
  pinMode(MOTOR_LEFT, OUTPUT);
  pinMode(MOTOR_RIGHT, OUTPUT);
}

void loop() {
  int buffer;

  if (Serial.available() > 0) {
    buffer = Serial.read();

    switch(buffer) {
    case CMD_LEFT_START:
      startMotor(CMD_LEFT_START);
    case CMD_RIGHT_START:
      startMotor(CMD_RIGHT_START);
    case CMD_LEFT_STOP:
      analogWrite(MOTOR_LEFT, 0);
    case CMD_RIGHT_STOP:
      analogWrite(MOTOR_RIGHT, 0);
    }
  }
  run();
}
