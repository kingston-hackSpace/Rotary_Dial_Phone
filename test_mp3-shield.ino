#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>

const int switchPin = A0;   // hook switch
const int ledPin = A1;
const int in1 = 4;
const int in2 = 5;

SdFat sd;
SFEMP3Shield MP3player;

bool ringActive = false;
bool wasRingActive = false;

unsigned long ringTimer = 0;
int ringStep = 0;
const unsigned long ringPattern[] = {400, 200, 400, 2000};
bool ringBurstActive = false;

unsigned long acTimer = 0;
unsigned long acHalfPeriodMicros = 400;
const unsigned long pitchA = 400;
const unsigned long pitchB = 350;
unsigned long warbleTimer = 0;
const unsigned long warbleInterval = 25;
bool warbleState = false;
bool acPolarity = false;

bool wasHandsetLifted = false;

void setup() {
  pinMode(switchPin, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  stopBell();
  digitalWrite(ledPin, LOW);

  Serial.begin(9600);
  if (!sd.begin(9, SPI_HALF_SPEED)) sd.initErrorHalt();
  sd.chdir("/");
  MP3player.begin();
  MP3player.setVolume(10, 10);
}

void loop() {
  bool switchPressed = (digitalRead(switchPin) == HIGH);  // single read, single source of truth

  updateRing(switchPressed);
  checkHandsetAudio(switchPressed);
}

void updateRing(bool switchPressed) {
  ringActive = switchPressed;   // ring whenever the switch is pressed

  if (ringActive && !wasRingActive) {
    digitalWrite(ledPin, HIGH);
    ringStep = 0;
    ringTimer = millis();
    ringBurstActive = true;
  }
  if (!ringActive && wasRingActive) {
    digitalWrite(ledPin, LOW);
    stopBell();
    ringBurstActive = false;
  }
  wasRingActive = ringActive;

  if (!ringActive) return;

  if (millis() - ringTimer >= ringPattern[ringStep]) {
    ringTimer = millis();
    ringStep = (ringStep + 1) % 4;
    ringBurstActive = (ringStep % 2 == 0);
    if (!ringBurstActive) stopBell();
  }

  if (ringBurstActive) {
    updateWarble();
    driveBellAC();
  }
}

void checkHandsetAudio(bool switchPressed) {
  bool handsetLifted = !switchPressed;

  if (handsetLifted && !wasHandsetLifted) {
    
    MP3player.playMP3("track001.mp3");
  }
  if (!handsetLifted && wasHandsetLifted) {
    
    MP3player.stopTrack();
  }

  wasHandsetLifted = handsetLifted;
}

void updateWarble() {
  if (millis() - warbleTimer >= warbleInterval) {
    warbleTimer = millis();
    warbleState = !warbleState;
    if (warbleState == true) {
      acHalfPeriodMicros = pitchA;
    } else {
      acHalfPeriodMicros = pitchB;
    }
  }
}

void driveBellAC() {
  if (micros() - acTimer >= acHalfPeriodMicros) {
    acTimer = micros();
    acPolarity = !acPolarity;
    if (acPolarity == true) {
      digitalWrite(in1, HIGH);
      digitalWrite(in2, LOW);
    } else {
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
    }
  }
}

void stopBell() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
}
