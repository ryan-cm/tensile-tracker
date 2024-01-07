#include "BluetoothSerial.h"

BluetoothSerial ESP_BT; // Object for Bluetooth

void setup() {
  Serial.begin(115200);
  ESP_BT.begin("ESP32_BT_Test"); // Name of your Bluetooth signal
  Serial.println("Bluetooth device is ready to pair");
}

void loop() {
  if (ESP_BT.available()) { // Check if we receive anything from Bluetooth
    Serial.write(ESP_BT.read()); // Send what we receive to the Serial Monitor
  }
  if (Serial.available()) { // Check if there is something to send to the Bluetooth device
    ESP_BT.write(Serial.read()); // Read from the Serial Monitor and send to Bluetooth
  }

  // Your code to read data and send via Bluetooth
  // Example: ESP_BT.println("Sensor Value: " + String(sensorValue));
}
