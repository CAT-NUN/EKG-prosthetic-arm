#include <ESP32Servo.h>
#include <HardwareSerial.h>

Servo myservo1;
Servo myservo2;
bool serial2Initialized = false; // Variable to track if Serial2 is initialized
const int RXD = 16;
const int TXD = 17;

void setup() {
  Serial.begin(115200); // Initialize serial communication for debugging
  Serial.println("Initializing...");
  myservo1.attach(18); // Attaching myservo1 to pin D18
  myservo2.attach(19); // Attaching myservo2 to pin D19
  
  pinMode(RXD, INPUT);
  pinMode(TXD, INPUT);
  
  Serial2.begin(9600, SERIAL_8N1, RXD, TXD); // Initialize Serial2 (UART) communication for HC-05 with RXD = 17, TXD = 16
}

void loop() {
  if (!serial2Initialized) {
    // If Serial2 is not yet initialized, check if RXD and TXD pins are connected
    if (digitalRead(RXD) == HIGH && digitalRead(TXD) == HIGH) {
      // RXD and TXD pins are connected, initialize Serial2
      Serial.println("Serial2 initializing...");
      serial2Initialized = true; // Set the flag to indicate that Serial2 is initialized
      Serial.println("Serial2 initialized!");
    } else {
      Serial.println("RXD and TXD pins not connected."); // Print error message if RXD and TXD pins are not connected
    }
  } else {
    // Serial2 is initialized, proceed with normal operation
    if (Serial2.available() > 0) {
      // Read serial input from HC-05
      char command = Serial2.read();
      Serial.println("Received command from HC-05: " + String(command));

      // Move myservo1 and myservo2 based on received command
      if (command == '1') {
        Serial.println("Command '1' received, moving myservo1 to position 90 and myservo2 to position 180...");
        myservo1.write(90);
        myservo2.write(180);
      } else if (command == '2') {
        Serial.println("Command '2' received, moving myservo1 to position 0 and myservo2 to position 90...");
        myservo1.write(0);
        myservo2.write(90);
      }
    }
  }
}
