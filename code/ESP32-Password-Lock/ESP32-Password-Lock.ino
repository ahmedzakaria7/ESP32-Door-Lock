#include "BluetoothSerial.h"

BluetoothSerial SerialBT;

// Pin connected to Base
const int lockPin = 2;

// Hold password input
String Data;

// Right Password
String Master = "1234";

void setup() {
  SerialBT.begin("ESP32-Bluetooth");
  pinMode(lockPin, OUTPUT);
}

void loop() {

  if (SerialBT.available()) {
    //Read Password
    while (SerialBT.available()) {
      char c = SerialBT.read();
      Data += c;
    }

    if (Data == Master) {
      // Correct Password
      SerialBT.print("Access Granted");
      // Activate TIP Transistor for 5 seconds
      digitalWrite(lockPin, HIGH);
      delay(1000);
      digitalWrite(lockPin, LOW);
    } else {
      // Incorrect Password
      SerialBT.print("Wrong Password");
      delay(1000);
    }
  }
  //Reset
  Data = "";
}
