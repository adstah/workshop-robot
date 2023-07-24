const int d0Led = 16;

void fadeIn() {
  for (int i = 0; i <= 255; i++) {
    Serial.println(i);
    analogWrite(d0Led, i);
    delay(10);
  }
}

void fadeOut() {
  for (int i = 255; i >= 0; i--) {
    Serial.println(i);
    analogWrite(d0Led, i);
    delay(10);
  }
}

void setup() {
  pinMode(d0Led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  analogWrite(d0Led, 0);
  delay(1000);
  analogWrite(d0Led, 127);
  delay(1000);
  analogWrite(d0Led, 255);
  delay(1000);
  fadeIn();
  fadeOut();
}
