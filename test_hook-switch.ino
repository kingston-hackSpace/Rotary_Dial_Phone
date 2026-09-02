const int switchPin = A0;   // hook switch
const int ledPin = A1;      // test LED

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  int switchState = digitalRead(switchPin);

  if (switchState == LOW) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
}
