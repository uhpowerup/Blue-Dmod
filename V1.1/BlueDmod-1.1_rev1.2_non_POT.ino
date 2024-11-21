// Pin Definitions
const int Auin = A3;  // Audio Input
const int PLED = A1;  // PTT LED (LED1 on Board)
const int PTT = A7;   // PTT ON/OFF

// Variables
int threshold = 200;  // Default threshold value (can be changed manually)
unsigned long timer = 0;
const unsigned long debounceDelay = 1000;  // 1000 ms delay

void setup() {
  pinMode(Auin, INPUT);   // Configure Audio Input
  pinMode(PLED, OUTPUT);  // Configure LED Output
  pinMode(PTT, OUTPUT);   // Configure PTT Output
  
  digitalWrite(PLED, LOW); // Initial state
  digitalWrite(PTT, LOW);  // Initial state

  Serial.begin(9600);  // Initialize Serial communication
}

void loop() {
  int audioSignal = analogRead(Auin);  // Read audio input
  
  // Debug: Print the audio input value to the Serial Monitor
  Serial.print("Audio Input (Auin): ");
  Serial.println(audioSignal);

  // Check if the audio signal is above the threshold
  if (audioSignal > threshold) {
    digitalWrite(PLED, HIGH); // Turn LED ON
    digitalWrite(PTT, HIGH);  // Turn PTT ON
    timer = millis();         // Reset the timer
  } else if (millis() - timer > debounceDelay) {
    // If audio signal is below the threshold and timer expires
    digitalWrite(PLED, LOW); // Turn LED OFF
    digitalWrite(PTT, LOW);  // Turn PTT OFF
  }
  
  delay(100);  // Short delay to avoid flooding the Serial Monitor
}
