// Blue Dmod V1.1 rev 1.2 //
// https://uhpowerup.com/ //
// Use at your own risk //


// Pin Assignments
const int PotPin = A6; // Potentiometer pin
const int Auin = A3;   // Audio input pin
const int PTT = A7;    // PTT
const int PLED = A1;    // PTT LED (LED1 on board)

// Variables
int threshold = 200;        // Threshold value, adjust as needed
unsigned long timerDuration = 0; // Duration to keep PTT HIGH
unsigned long lastHighTime = 0;  // Timestamp when PTT was last set HIGH

void setup() {
  pinMode(PotPin, INPUT);
  pinMode(Auin, INPUT);
  pinMode(PTT, OUTPUT);
  pinMode(PLED, OUTPUT);
  digitalWrite(PTT, LOW); // Initialize PTT to LOW
  digitalWrite(PLED, LOW); // Initialize PTT LED to Low
  Serial.begin(9600); // Optional: For debugging
}

void loop() {
  // Read potentiometer value and map to 10ms to 1000ms
  int potValue = analogRead(PotPin);
  timerDuration = map(potValue, 0, 1023, 10, 1000);

  // Read audio signal
  int audioSignal = analogRead(Auin);

  // Check if audio signal exceeds threshold
  if (audioSignal > threshold) {
    digitalWrite(PTT, HIGH);         // Set PTT HIGH
    digitalWrite(PLED, HIGH);         // Set PLED HIGH
    lastHighTime = millis();         // Record the current time
  }

  // Check if timer has expired
  if (millis() - lastHighTime > timerDuration) {
    digitalWrite(PTT, LOW);          // Set PTT LOW
    digitalWrite(PLED, LOW);          // Set PLED LOW
  }

  // Optional: Debugging
  Serial.print("Audio Signal: ");
  Serial.print(audioSignal);
  Serial.print(" | Threshold: ");
  Serial.print(threshold);
  Serial.print(" | Timer: ");
  Serial.println(timerDuration);
  
  delay(10); // Small delay for stability
}
