#include <ESP32Servo.h>

// Define servo pins
const int rightServoPin = 26;
const int leftServoPin = 25;

// Create Servo objects
Servo rightServo;
Servo leftServo;

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for Serial Monitor to open (optional)

  // Attach servos to their respective pins
  rightServo.attach(rightServoPin);
  leftServo.attach(leftServoPin);

  Serial.println("Type an angle (0-180) to move the servos:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n');
    input.trim();  // Remove any extra whitespace or newlines

    int angle = input.toInt();
    
    if (angle >= 0 && angle <= 180) {
      rightServo.write(angle);
      leftServo.write(angle);
      Serial.print("Servos set to ");
      Serial.print(angle);
      Serial.println(" degrees.");
    } else {
      Serial.println("Invalid input. Please enter a number between 0 and 180.");
    }
  }
}
