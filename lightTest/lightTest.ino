#include <Servo.h>
int d = 1000;
bool light = false;
int servo_pin = 10;
Servo myServo;


void moveServo(int angle) {
  myServo.write(angle);
  delay(d);
}

void blink(){
  digitalWrite(3, !light);
  light = !light
}

void setup() {
  pinMode(light_pin, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  Serial.println("Test");
  blink(light_pin);
  moveServo(90);
  moveServo(0);
}
