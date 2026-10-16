#include <SPI.h>
#include <SdFat.h>
#include <SFEMP3Shield.h>

// ---------- Pins ----------
const int switchPin = A0;   // hook switch
const int ledPin    = A1;
const int in1       = 4;    // H-bridge input 1
const int in2       = 5;    // H-bridge input 2

SdFat sd;
SFEMP3Shield MP3player;

// ---------- Cycle timing ----------
// Ring for 10 seconds, then wait 15min (silence) until next ring
const unsigned long RING_DURATION = 10000; //10seconds
const unsigned long WAIT_DURATION = 900000;// every 15 min
// For testing, try: WAIT_DURATION = 5000; // 5 seconds

enum PhoneState { RINGING, WAITING, OFF_HOOK };
PhoneState state;
unsigned long phaseStart = 0;   // when the current ringing/waiting phase began

// ---------- Ring cadence (UK style: ring, pause, ring, long pause) ----------
const unsigned long ringPattern[] = {400, 200, 400, 2000};
unsigned long ringTimer = 0;
int ringStep = 0;
bool ringBurstActive = false;

// ---------- Bell drive (fake AC through the H-bridge) ----------
unsigned long acTimer = 0;
unsigned long acHalfPeriodMicros = 400;
const unsigned long pitchA = 400;
const unsigned long pitchB = 350;
unsigned long warbleTimer = 0;
const unsigned long warbleInterval = 25;
bool warbleState = false;
bool acPolarity = false;

// =====================================================================

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

  // Start the cycle with a ring as soon as the phone is powered on
  if (isHandsetDown()) {
    startRinging();
  } else {
    pickUp();
  }
}

void loop() {
  bool handsetDown = isHandsetDown();

  // --- Pick up / hang up always take priority ---
  if (!handsetDown && state != OFF_HOOK) {
    pickUp();
    return;
  }
  if (handsetDown && state == OFF_HOOK) {
    hangUp();
    return;
  }

  // --- Timed cycle ---
  unsigned long elapsed = millis() - phaseStart;

  if (state == RINGING) {
    if (elapsed >= RING_DURATION) {
      stopRinging();
      startWaiting();          // nobody answered: go quiet for 15 min
    } else {
      updateRingCadence();
    }
  }
  else if (state == WAITING) {
    if (elapsed >= WAIT_DURATION) {
      startRinging();          // 15 min are up: ring again
    }
  }
}

// =====================================================================
// State changes

bool isHandsetDown() {
  return digitalRead(switchPin) == HIGH;  // flip to LOW if your switch works the other way
}

void startRinging() {
  state = RINGING;
  phaseStart = millis();
  digitalWrite(ledPin, HIGH);
  ringStep = 0;
  ringTimer = millis();
  ringBurstActive = true;
  Serial.println("Ringing");
}

void stopRinging() {
  digitalWrite(ledPin, LOW);
  stopBell();
  ringBurstActive = false;
}

void startWaiting() {
  state = WAITING;
  phaseStart = millis();
  Serial.println("Waiting 15 min");
}

void pickUp() {
  stopRinging();
  state = OFF_HOOK;
  MP3player.playMP3("track001.mp3");
  Serial.println("Picked up");
}

void hangUp() {
  MP3player.stopTrack();
  startWaiting();              // timers reset: a fresh 30 min wait starts now
  Serial.println("Hung up");
}

// =====================================================================
// Bell sound

void updateRingCadence() {
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

void updateWarble() {
  if (millis() - warbleTimer >= warbleInterval) {
    warbleTimer = millis();
    warbleState = !warbleState;
    acHalfPeriodMicros = warbleState ? pitchA : pitchB;
  }
}

void driveBellAC() {
  if (micros() - acTimer >= acHalfPeriodMicros) {
    acTimer = micros();
    acPolarity = !acPolarity;
    if (acPolarity) {
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
