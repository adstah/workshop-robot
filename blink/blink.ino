void setup() {
  pinMode(LED_BUILTIN, OUTPUT);  // Initialize the LED_BUILTIN pin as an output
}


void loop() {
  digitalWrite(LED_BUILTIN, LOW);  // Set output to LOW / 0
  delay(500);                      // Stop the program for 1 second
  digitalWrite(LED_BUILTIN, HIGH);  // Set output to HIGH / 1
  delay(1000);                      // Stop the program for 2 seconds
}
