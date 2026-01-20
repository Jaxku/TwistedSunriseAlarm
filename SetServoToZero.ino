
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards


void setup() {
  myservo.attach(D2);  // attaches the servo on GIO2 to the servo object //ADJUST IF USING DIFFERENT PIN
}

void loop() {
  int pos;

  myservo.write(0);  // tell servo to go to position in variable 'pos'
}