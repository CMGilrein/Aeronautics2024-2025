#include <Wire.h>
#include <HMC5883L.h>

HMC5883L compass;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  
  // Initialize the magnetometer
  if (!compass.begin()) {
    Serial.println("Couldn't find the HMC5883L magnetometer");
    while (1);
  }
}

void loop() {
  // Read magnetometer values
  Vector magnetometer = compass.readNormalize();
  
  // Output the magnetometer readings to Serial Monitor
  Serial.print("X: "); Serial.print(magnetometer.XAxis); Serial.print(" ");
  Serial.print("Y: "); Serial.print(magnetometer.YAxis); Serial.print(" ");
  Serial.print("Z: "); Serial.println(magnetometer.ZAxis);
  
  delay(500);  // Small delay
}
