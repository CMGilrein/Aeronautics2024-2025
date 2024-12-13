#include <Wire.h>

// Define a lookup table for known I2C device addresses
struct I2CDevice {
  uint8_t address;
  const char* name;
};

// Add known devices to the table
I2CDevice knownDevices[] = {
  {0x1E, "HMC5883L Magnetometer"},
  {0x68, "MPU6050 Accelerometer/Gyro"},
  {0x76, "BMP280/BME280 Pressure Sensor"},
  {0x77, "BMP280/BME280 Pressure Sensor (alt addr)"},
  {0x3C, "SSD1306 OLED Display"},
  {0x57, "AT24C32 EEPROM"},
  // Add more devices as needed
};

const int numDevices = sizeof(knownDevices) / sizeof(knownDevices[0]);

void setup() {
  Serial.begin(115200);
  Wire.begin();
  Serial.println("I2C Scanner with Device Identification\n");
}

void loop() {
  Serial.println("Scanning...");

  for (uint8_t address = 1; address < 127; address++) {
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();

    if (error == 0) {
      Serial.print("Device found at 0x");
      Serial.print(address, HEX);

      // Check if the address matches any known device
      bool found = false;
      for (int i = 0; i < numDevices; i++) {
        if (knownDevices[i].address == address) {
          Serial.print(" (");
          Serial.print(knownDevices[i].name);
          Serial.print(")");
          found = true;
          break;
        }
      }

      if (!found) {
        Serial.print(" (Unknown Device)");
      }
      Serial.println();
    } else if (error == 4) {
      Serial.print("Error at address 0x");
      Serial.println(address, HEX);
    }
  }

  Serial.println("\nScan complete. Next scan in 5 seconds.\n");
  delay(5000);
}
