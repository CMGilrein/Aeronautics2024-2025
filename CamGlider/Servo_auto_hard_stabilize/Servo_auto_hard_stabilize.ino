#include <Wire.h>
#include <MPU6050.h>
#include <math.h>  // For atan2 and sqrt
#include <ESP32Servo.h>

MPU6050 mpu;
#define SDA_PIN 21
#define SCL_PIN 22

// Define servos
Servo starboardServo;
Servo portServo;

// Pin assignments for servos
#define STARBOARD_SERVO_PIN 26
#define PORT_SERVO_PIN 25

// Global variables
int16_t ax, ay, az, gx, gy, gz;

void setup() {
  Serial.begin(115200);
  Wire.begin(SDA_PIN, SCL_PIN);
  mpu.initialize();

  starboardServo.attach(STARBOARD_SERVO_PIN);
  portServo.attach(PORT_SERVO_PIN);

  stable();  // Set servos to neutral at startup

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connection successful.");
  } else {
    Serial.println("MPU6050 connection failed. Check your wiring.");
    while (1);
  }
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);

  // Calculate pitch and roll
  float pitch = atan2(ay, sqrt(ax * ax + az * az)) * 180 / M_PI;
  float roll = atan2(-ax, az) * 180 / M_PI;

  Serial.print("Pitch: ");
  Serial.print(pitch, 1);
  Serial.print("° | Roll: ");
  Serial.print(roll, 1);
  Serial.println("°");

  // Control logic
  if (pitch > 15) {
    up();  // Pitch exceeds +15° (nose up)
  } else if (pitch < -15) {
    down();  // Pitch below -15° (nose down)
  } else if (roll > 15) {
    bankRight();  // Roll exceeds +15° (right bank)
  } else if (roll < -15) {
    bankLeft();  // Roll below -15° (left bank)
  } else {
    stable();  // Stay stable if within ±15° range
  }

  delay(75);  // Delay to avoid flooding the serial monitor
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


