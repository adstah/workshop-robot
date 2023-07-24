const int d5in1 = 14;
const int d6in2 = 12;

const int d4enAandB = 2;

void accelerate() {
  digitalWrite(d5in1, HIGH);
  digitalWrite(d6in2, LOW);
  for (int i = 0; i < 255; i++) {
    analogWrite(d4enAandB, i);
    delay(25);
  }
}

void setup() {
  pinMode(d5in1, OUTPUT);
  pinMode(d6in2, OUTPUT);
}

void loop() {
  // clockwise
  digitalWrite(d5in1, HIGH);
  digitalWrite(d6in2, LOW);
  delay(1500);

  // hard stop
  digitalWrite(d5in1, HIGH);
  digitalWrite(d6in2, HIGH);
  delay(1500);

  // counterclockwise
  digitalWrite(d5in1, LOW);
  digitalWrite(d6in2, HIGH);
  delay(1500);

  // soft stop
  digitalWrite(d5in1, LOW);
  digitalWrite(d6in2, LOW);
  delay(1500);

  accelerate();
}
