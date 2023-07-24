const int d0Led = 16;

void setup() {
  pinMode(d0Led, OUTPUT);
}

void loop() {
  digitalWrite(d0Led, HIGH);
  delay(1000);
  digitalWrite(d0Led, LOW);
  delay(500);
}
