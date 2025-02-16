// Define the transistor control pin
const int transistorPin = 15;

void setup() {
  // Initialize the serial monitor
  Serial.begin(115200);
  while (!Serial) {
    ; // Wait for the serial port to connect (useful for native USB boards)
  }
  
  // Set pin 15 as an output
  pinMode(transistorPin, OUTPUT);
  Serial.println("Setup complete. Starting the loop...");
}

void loop() {
  // Turn the transistor on
  digitalWrite(transistorPin, HIGH);
  Serial.println("Transistor ON (pin 15 HIGH)");
  delay(10000); // Wait for 1 second (1000 milliseconds)

  // Turn the transistor off
  digitalWrite(transistorPin, LOW);
  Serial.println("Transistor OFF (pin 15 LOW)");
  delay(1000); // Wait for 1 second (1000 milliseconds)
}
