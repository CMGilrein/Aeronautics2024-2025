#include <ESP32Servo.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
#include <Wire.h>
#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <Arduino.h>

TinyGPSPlus gps;
HardwareSerial mySerial(2);

const int rightServoPin = 2;  
const int leftServoPin = 4;  

Servo servoRight;
Servo servoLeft;

int angle1 = 90;  
int angle2 = 90;  

const int RXPin = 16;  
const int TXPin = 17;  

Adafruit_MPU6050 mpu;
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified();

void setup() {
  Serial.begin(115200);
  mySerial.begin(9600, SERIAL_8N1, RXPin, TXPin);

  servoRight.attach(rightServoPin);
  servoLeft.attach(leftServoPin);

  if (!mpu.begin()) {
    Serial.println("MPU6050 not detected!");
  } else {
    Serial.println("MPU6050 Initialized");
  }

  if (!mag.begin()) {
    Serial.println("HMC5883 not detected!");
  } else {
    Serial.println("HMC5883 Initialized");
  }

  if (!mySerial) {
    Serial.println("GPS Serial port not initialized correctly.");
  } else {
    Serial.println("GPS Serial port initialized.");
  }

  // Wait for GPS signal to stabilize
  //waitForGPS();

  // Initial Servo movement with 2-second delay
  moveServoLeft(90);
  delay(2000);  // 2 seconds delay
  moveServoRight(90);
  delay(2000);  // 2 seconds delay
  moveServoLeft(0);
  delay(2000);  // 2 seconds delay
  moveServoRight(180);
  delay(2000);  // 2 seconds delay
  moveServoLeft(90);
  delay(2000);  // 2 seconds delay
  moveServoRight(90);
  delay(2000);  // 2 seconds delay
  moveServoLeft(180);
  delay(2000);  // 2 seconds delay
  moveServoRight(90);
  delay(2000);  // 2 seconds delay
  moveServoLeft(90);
  delay(2000);  // 2 seconds delay
  moveServoRight(90);
  delay(2000);  // 2 seconds delay
}

void loop() { 
  Serial.println("Looping");

  double lat = readLatitude();
  double lon = readLongitude();
  
  if (lat != 0.0 && lon != 0.0) {
    Serial.print("GPS Coordinates: Latitude: ");
    Serial.print(lat, 6);
    Serial.print(", Longitude: ");
    Serial.println(lon, 6);
  } else {
    Serial.println("Waiting for GPS signal...");
  }

  double bearing = readBearing();
  double acceleration = readAcceleration();
  double gyro = readGyro();

  handleFlight(lat, lon, bearing, acceleration, gyro);

  delay(1000);  // Adjust loop rate if necessary
}

void handleFlight(double lat, double lon, double bearing, double acceleration, double gyro) {
  Serial.println("Handling Flight...");
  Serial.print("Latitude: ");
  Serial.println(lat);
  Serial.print("Longitude: ");
  Serial.println(lon);
  Serial.print("Bearing: ");
  Serial.println(bearing);
  Serial.print("Acceleration: ");
  Serial.println(acceleration);
  Serial.print("Gyro: ");
  Serial.println(gyro);
}

void moveServoRight(int angle) {
  if (angle >= 0 && angle <= 180) {
    servoRight.write(angle);
    angle1 = angle;
    Serial.print("Servo Right moved to: ");
    Serial.println(angle1);
  }
}

void moveServoLeft(int angle) {
  if (angle >= 0 && angle <= 180) {
    servoLeft.write(angle);
    angle2 = angle;
    Serial.print("Servo Left moved to: ");
    Serial.println(angle2);
  }
}

double readLatitude() {
  gps.encode(mySerial.read());
  if (gps.location.isUpdated()) {
    return gps.location.lat();
  }
  return 0.0;
}

double readLongitude() {
  gps.encode(mySerial.read());
  if (gps.location.isUpdated()) {
    return gps.location.lng();
  }
  return 0.0;
}

double readBearing() {
  sensors_event_t event;
  mag.getEvent(&event);
  return atan2(event.magnetic.y, event.magnetic.x) * 180 / PI;
}

double readAcceleration() {
  sensors_event_t accel;
  mpu.getAccelerometerSensor()->getEvent(&accel);
  return sqrt(accel.acceleration.x * accel.acceleration.x + accel.acceleration.y * accel.acceleration.y + accel.acceleration.z * accel.acceleration.z);
}

double readGyro() {
  sensors_event_t gyroEvent;
  mpu.getGyroSensor()->getEvent(&gyroEvent);
  return sqrt(gyroEvent.gyro.x * gyroEvent.gyro.x + gyroEvent.gyro.y * gyroEvent.gyro.y + gyroEvent.gyro.z * gyroEvent.gyro.z);
}

void waitForGPS() {
  while (gps.location.isUpdated() == false) {
    Serial.println("Waiting for GPS signal...");
    delay(1000);
  }
  Serial.println("GPS signal received.");
}
