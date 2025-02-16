#include <ESP32Servo.h>

// Define servo pins
const int starboardServoPin = 26;  // Right servo (starboard)
const int portServoPin = 25;       // Left servo (port)

// Create Servo objects
Servo starboardServo;
Servo portServo;

void setup() {
  Serial.begin(115200);
  while (!Serial);  // Wait for Serial Monitor to open (optional)

  // Attach servos to their respective pins
  starboardServo.attach(starboardServoPin);
  portServo.attach(portServoPin);

  Serial.println("Type one of the following commands: l, r, s, u, d");
}

void loop() {
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();  // Remove any extra whitespace or newlines
    command.toLowerCase();  // Convert to lowercase for easier comparison

    if (command == "l") {
      bankLeft();
    } else if (command == "r") {
      bankRight();
    } else if (command == "s") {
      stable();
    } else if (command == "u") {
      up();
    } else if (command == "d") {
      down();
    } else {
      Serial.println("Invalid command. Please type: l (bank left), r (bank right), s (stable) u (up), d (down)");
    }
  }
}

// Function to bank left
void bankLeft() {
  starboardServo.write(120);  // Adjust this angle to deflect starboard down
  portServo.write(120);        // Adjust this angle to deflect port up
  Serial.println("Banking left...");
}

// Function to bank right
void bankRight() {
  starboardServo.write(60);   // Adjust this angle to deflect starboard up
  portServo.write(60);       // Adjust this angle to deflect port down
  Serial.println("Banking right...");
}

// Function to keep stable (neutral position)
void stable() {
  starboardServo.write(90);   // Neutral position for starboard
  portServo.write(90);        // Neutral position for port
  Serial.println("Stable position...");
}


// Function to (up position)
void up() {
  starboardServo.write(60);   // Neutral position for starboard
  portServo.write(120);        // Neutral position for port
  Serial.println("Up position...");
}

// Function to (down position)
void down() {
  starboardServo.write(120);   // Neutral position for starboard
  portServo.write(60);        // Neutral position for port
  Serial.println("down position...");
}