#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>

// Define UUIDs for BLE service and characteristic
#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

// Create a BLE Characteristic
BLECharacteristic *pCharacteristic;

void setup() {
  Serial.begin(115200);
  // Initialize BLE and set it up as a server
  BLEDevice::init("ESP32 BLE Server");
  BLEServer *pServer = BLEDevice::createServer();

  // Create the BLE Service
  BLEService *pService = pServer->createService(SERVICE_UUID);

  // Create a BLE Characteristic
  pCharacteristic = pService->createCharacteristic(
                      CHARACTERISTIC_UUID,
                      BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_NOTIFY
                    );

  // Start the service
  pService->start();

  // Start advertising the service
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->addServiceUUID(SERVICE_UUID);
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  // functions that help with iPhone connections issue
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();

  Serial.println("BLE service started. Waiting for clients to connect.");
}

void loop() {
  // Read the analog value
  uint sensorValue = getSensorData();

  // Convert sensor reading to a string
  char valueStr[10];
  itoa(sensorValue, valueStr, 10);

  // Update the BLE characteristic
  pCharacteristic->setValue(valueStr);
  pCharacteristic->notify();

  delay(1000); // Delay between readings
}

uint getSensorData() {
  static uint sensorValue = 0; // Initialize the static variable
  sensorValue++;               // Increment the value each time the function is called
  return sensorValue;          // Return the incremented value
}
