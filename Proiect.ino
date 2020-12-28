#include <Servo.h>


Servo ServoForX;
Servo ServoForY;
int InputServoX = 8;
int InputServoY = 9;
int InputJoystickX = A2;
int InputJoystickY = A1;
int ReadJoystickX = 0;
int ReadJoystickY = 0;
int XStartPosition = 32;
int YStartPosition = 140;
int CurrentXPosition;
int CurrentYPosition;
int range = 12;
int center = range / 2;
int threshold = range / 4;

int readAxis(int thisAxis);
void controlServo(int ReadJoystickX, int ReadJoystickY);

void setup() {
  Serial.begin(9600); //Begin Serial monitor of arduino ide
 

  ServoForX.attach(InputServoX);
  ServoForY.attach(InputServoY);
  CurrentXPosition = XStartPosition;
  CurrentYPosition = YStartPosition;
  ServoForX.write(CurrentXPosition);
  ServoForY.write(CurrentYPosition);


  Serial.begin(9600);
}
void loop() {

  controlServo(readAxis(InputJoystickX), readAxis(InputJoystickY));
  
} //End Loop

//reading the coordinates from the servomotors
int readAxis(int thisAxis) {

  int reading = analogRead(thisAxis);
  reading = map(reading, 0, 1023, 0, range);
  int distance = reading - center;
  if (abs(distance) < threshold) {
    distance = 0;
  }

  return distance;
}
//control servomotors with joystick
void controlServo(int ReadJoystickX, int ReadJoystickY) {

  if (ReadJoystickX > 0) {
    CurrentXPosition += 2;
    ServoForX.write(CurrentXPosition);
    delay(10 * ReadJoystickX);
  }
  if (ReadJoystickX < 0) {
    CurrentXPosition -= 2;
    ServoForX.write(CurrentXPosition);
    delay(10 * ReadJoystickX);
  }
  if (ReadJoystickY > 0) {
    CurrentYPosition += 2;
    ServoForY.write(CurrentYPosition);
    delay(10 *  ReadJoystickY);
  }
  if (ReadJoystickY < 0) {
    CurrentYPosition -= 2;
    ServoForY.write(CurrentYPosition);
    delay(10 *  ReadJoystickY);
  }

  if (CurrentXPosition > XStartPosition + 20) {
    CurrentXPosition = XStartPosition + 20;
  }
  if (CurrentXPosition < XStartPosition - 20) {
    CurrentXPosition = XStartPosition - 20;
  }
  if (CurrentYPosition > YStartPosition + 20) {
    CurrentYPosition = YStartPosition + 20;
  }
  if (CurrentYPosition < YStartPosition - 20) {
    CurrentYPosition = YStartPosition - 20;
  }
}