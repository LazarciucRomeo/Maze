#include <Servo.h>


Servo ServoForX;
Servo ServoForY;
int InputServoX = 8;
int InputServoY = 9;
int sensor = A0;
int Buz = 11;
int Led = 6;
int ledFinish = 13;
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
unsigned long delayStart = 0;
bool delayRunning = false;
long tempo = 20000; // this will set overall tempo
int pause = 1000; // initializing the variable for pause between tones
int rest_count = 100;
int tone_ = 0;
int beat = 0;
long duration = 0; 

int yPosition[] = {
  100,
  100,
  150,
  120,
  170,
  130,
  130,
  80,
  150,
  150
}; //initializing the y axle for autonomous function
int xPosition[] = {
  40,
  10,
  20,
  70,
  0,
  20,
  60,
  20,
  20,
  60

}; //initializing the x axle for autonomous function
int melody[] = {
  'C',
  'b',
  'g',
  'C',
  'e',
  'e',
  'R',
  'C',
  'a',
  'g',
  'a',
  'C'
}; // initializing variables for playing melody
int beats[] = {
  16,
  16,
  16,
  8,
  8,
  16,
  32,
  16,
  16,
  16,
  8,
  8
}; // initializing the beat values 
int MAX_COUNT = sizeof(melody);

int readAxis(int thisAxis);
void controlServo(int ReadJoystickX, int ReadJoystickY);
void autonomous();
void playTone();
void finishCelabration(int photoresistor_value);

void setup() {
  Serial.begin(9600); //Begin Serial monitor of arduino ide
  pinMode(sensor, INPUT);
  pinMode(Buz, OUTPUT); //Arduino buzzer pin as output
  pinMode(Led, OUTPUT);
  pinMode(ledFinish, OUTPUT); //Arduino Led pin as output 
  
  ServoForX.attach(InputServoX);
  ServoForY.attach(InputServoY);
  CurrentXPosition = XStartPosition;
  CurrentYPosition = YStartPosition;
  ServoForX.write(CurrentXPosition);
  ServoForY.write(CurrentYPosition);
  delayStart = millis(); // start delay
  delayRunning = true;

  Serial.begin(9600);
}
void loop() {

  controlServo(readAxis(InputJoystickX), readAxis(InputJoystickY));
   
   if (delayRunning && ((millis() - delayStart) >= 10000) && CurrentXPosition == XStartPosition && CurrentYPosition == YStartPosition) {
    delayRunning = false;
    autonomous();
  }
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
void autonomous() {

  for (int i = 0; i < 10; i++) {

    ServoForX.write(xPosition[i]);
    ServoForY.write(yPosition[i]);
    delay(2000);
  }
}
void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { 
    while (elapsed_time < duration) {

      digitalWrite(Buz, HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(Buz, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  } else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { 
      delayMicroseconds(duration);
    }
  }
}
void finishCelabration(int photoresistor_value) {
  delay(10);
  if (photoresistor_value > 1) {
    digitalWrite(Buz, HIGH);
    digitalWrite(Led, HIGH);
    digitalWrite(ledFinish, LOW);
  } else {
    for (int i = 0; i < 12; i++) {
      photoresistor_value = analogRead(sensor);
      tone_ = melody[i];
      beat = beats[i];

      duration = beat * tempo; // Set up timing

      playTone();
      digitalWrite(ledFinish, HIGH);
      digitalWrite(Led, LOW);

      delay(pause / 10);

      digitalWrite(Led, HIGH);
      if (photoresistor_value > 1) {
        break;
      }
    }
  }
}
