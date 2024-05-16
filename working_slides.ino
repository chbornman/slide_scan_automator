/**
 * This example turns the ESP32 into a Bluetooth LE mouse that scrolls down every 2 seconds.
 */
#include <BleMouse.h>
#include <Arduino.h>

// Define GPIO pins
#define SLIDE_ADVANCE_PIN 2    // GPIO pin connected to the relay for advancing slides

// Adjustable delays (in milliseconds)
#define DELAY_AFTER_SHUTTER 1000  // Delay before taking a photo
#define DELAY_AFTER_ADVANCE 2500   // Delay after taking a photo before advancing the slide
#define RELAY_ON_TIME 250        // Time in ms the relay stays on to advance the slide
#define DELAY_NO_BT_RECHECK 1000

BleMouse bleMouse;

void setup() {
  // Initialize the serial communication
  Serial.begin(115200);

  // Configure GPIO pins
  pinMode(SLIDE_ADVANCE_PIN, OUTPUT);

  // Ensure shutter and relay are in the off position at startup
  digitalWrite(SLIDE_ADVANCE_PIN, LOW);

  Serial.println("Starting BLE work!");
  bleMouse.begin();

  Serial.println("Setup complete, waiting for start...");
}

void loop() {

  if(bleMouse.isConnected()) {
    // Advance the slide
    Serial.println("System is running. Advancing the slide...");
    digitalWrite(SLIDE_ADVANCE_PIN, HIGH);
    delay(RELAY_ON_TIME);  // Relay on time to advance the slide
    digitalWrite(SLIDE_ADVANCE_PIN, LOW);
    delay(DELAY_AFTER_ADVANCE);  

    // Trigger camera shutter
    Serial.println("Triggering camera shutter...");
    bleMouse.click();
    delay(DELAY_AFTER_SHUTTER);
  }
  else
  {
    Serial.println("Bluetooth not connected");
    delay(DELAY_NO_BT_RECHECK);
  }
}
