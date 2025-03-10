/**
 * SPO2 Sensor Interface for Arduino Nano
 * 
 * This sketch interfaces with the DFRobot_BloodOxygen_S sensor
 * to read heart rate and blood oxygen levels.
 */

#include "DFRobot_BloodOxygen_S.h"
#include <Wire.h>
#include <LiquidCrystal.h>

// I2C configuration
#define I2C_ADDRESS 0x57

// Initialize I2C interface for the sensor
DFRobot_BloodOxygen_S_I2C max30102(&Wire, I2C_ADDRESS);

// Variables to store sensor readings
int heartRate = 0;
int spo2 = 0;
float temperature = 0.0;

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  Serial.println("DFRobot Blood Oxygen Sensor Test 23");
  
  // Initialize sensor
  while (!max30102.begin()) {
    Serial.println("Sensor initialization failed!");
    delay(1000);
  }
  
  // Start data collection
  max30102.sensorStartCollect();
  Serial.println("Sensor initialized. Taking measurements...");
  
  // Wait for sensor to stabilize
  delay(2000);
}

void blinkSensorLED(int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    // Turn LED on by starting collection
    max30102.sensorStartCollect();
    delay(delayTime);
    
    // Turn LED off by stopping collection
    max30102.sensorEndCollect();
    delay(delayTime);
  }
  
  // Make sure collection is on when done
  max30102.sensorStartCollect();
}


void loop() {
  // Get heart rate and SPO2 readings
  max30102.getHeartbeatSPO2();
  
  // Get temperature reading
  temperature = max30102.getTemperature_C();
  
  // Store readings in variables
  heartRate = max30102._sHeartbeatSPO2.Heartbeat;
  spo2 = max30102._sHeartbeatSPO2.SPO2;
  
  // Print readings to serial monitor
  Serial.print("Heart Rate: ");
  if (heartRate == -1) {
    Serial.println("No valid reading");
  } else {
    Serial.print(heartRate);
    Serial.println(" BPM");
  }
  
  Serial.print("SPO2: ");
  if (spo2 == -1) {
    Serial.println("No valid reading");
  } else {
    Serial.print(spo2);
    Serial.println("%");
  }
  
//   Serial.print("Temperature: ");
//   Serial.print(temperature);
//   Serial.println(" °C");
//   Serial.println();
  
//   // Display readings on LCD
//   lcd.clear();
  
//   // First row: Heart rate
//   lcd.setCursor(0, 0);
//   lcd.print("HR: ");
//   if (heartRate == -1) {
//     lcd.print("--");
//   } else {
//     lcd.print(heartRate);
//     lcd.print(" bpm");
//   }
  
//   // Second row: SPO2 and temperature
//   lcd.setCursor(0, 1);
//   lcd.print("SPO2: ");
//   if (spo2 == -1) {
//     lcd.print("--");
//   } else {
//     lcd.print(spo2);
//     lcd.print("%");
//   }
  
//   lcd.setCursor(9, 1);
//   lcd.print(temperature, 1);
//   lcd.print("C");

  blinkSensorLED(5, 1);

  Serial.println("test");
  
  // Wait before next reading
  delay(1000);
}


