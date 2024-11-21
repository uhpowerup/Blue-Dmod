// Blue Dmod //
// https://uhpowerup.com/ //
// Author: 2E0UMR //
// use at your own risk //
const int audioPin = A1;  // Audio input pin
const int RPin = A3;     // Relay pin
const int threshold = 200;  // Adjust based on your audio signal

bool RState = false;      // Tracks Relay state
unsigned long offTimer = 0; // Tracks time to turn off the Relay
const int offDelay = 1000;  // 3-second delay in milliseconds

void setup() {
  pinMode(RPin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int audioValue = analogRead(audioPin);  // Read audio signal
  Serial.println(audioValue);            // Debugging: Print the value

  if (audioValue > threshold) {          // Audio signal exceeds threshold
    digitalWrite(RPin, HIGH);          // Turn Relay on immediately
    RState = true;                     // Update Relay state
    offTimer = 0;                        // Reset off timer
  } else if (RState && offTimer == 0) { // Start the 3-second timer
    offTimer = millis();                 // Record the current time
  }

  if (RState && offTimer > 0 && millis() - offTimer >= offDelay) {
    digitalWrite(RPin, LOW);           // Turn Relay off after 3 seconds
    RState = false;                    // Update Relay state
    offTimer = 0;                        // Reset off timer
  }
}
