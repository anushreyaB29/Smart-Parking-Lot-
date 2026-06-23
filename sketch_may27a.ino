#include <Servo.h>

Servo gate;

// ENTRY Ultrasonic
const int entryTrig = 9;
const int entryEcho = 10;

// EXIT Ultrasonic
const int exitTrig = 7;
const int exitEcho = 8;

// Servo
const int servoPin = 6;

long duration;

int carsInside = 0;
const int maxSlots = 3;

bool gateBusy = false;

unsigned long lastTrigger = 0;
const int cooldown = 3000;

void setup() {

  Serial.begin(9600);

  pinMode(entryTrig, OUTPUT);
  pinMode(entryEcho, INPUT);

  pinMode(exitTrig, OUTPUT);
  pinMode(exitEcho, INPUT);

  gate.attach(servoPin);

  gate.write(0);

  Serial.println("SMART PARKING SYSTEM");
}

void loop() {

  int entryDistance = getDistance(entryTrig, entryEcho);
  int exitDistance = getDistance(exitTrig, exitEcho);

  int availableSlots = maxSlots - carsInside;

  Serial.print("Cars Inside: ");
  Serial.print(carsInside);

  Serial.print(" | Available: ");
  Serial.println(availableSlots);

  Serial.print("Entry: ");
  Serial.print(entryDistance);

  Serial.print(" cm | Exit: ");
  Serial.print(exitDistance);

  Serial.println(" cm");

  // Prevent false retriggering
  if (millis() - lastTrigger < cooldown) {
    delay(300);
    return;
  }

  // ================= ENTRY =================
  if (entryDistance > 0 &&
      entryDistance <= 20 &&
      !gateBusy) {

    gateBusy = true;

    if (carsInside < maxSlots) {

      Serial.println("Car Entering");

      openGate();
      closeGate();

      carsInside++;

      Serial.print("Cars Inside Now: ");
      Serial.println(carsInside);
    }

    else {

      Serial.println("PARKING FULL");
    }

    lastTrigger = millis();

    // Wait until car leaves sensor
    while (getDistance(entryTrig, entryEcho) <= 20) {
      delay(100);
    }

    gateBusy = false;
  }

  // ================= EXIT =================
  else if (exitDistance > 0 &&
           exitDistance <= 20 &&
           !gateBusy) {

    gateBusy = true;

    if (carsInside > 0) {

      Serial.println("Car Exiting");

      openGate();
      closeGate();

      carsInside--;

      Serial.print("Cars Inside Now: ");
      Serial.println(carsInside);
    }

    lastTrigger = millis();

    // Wait until car leaves sensor
    while (getDistance(exitTrig, exitEcho) <= 20) {
      delay(100);
    }

    gateBusy = false;
  }

  Serial.println("------------------------");

  delay(500);
}

// =====================================
// DISTANCE FUNCTION
// =====================================
int getDistance(int trigPin, int echoPin) {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);

  int distance = duration * 0.034 / 2;

  return distance;
}

// =====================================
// SMOOTH OPEN GATE
// =====================================
// =====================================
// OPEN GATE
// =====================================
void openGate() {

  Serial.println("Opening Gate");

  gate.attach(servoPin);

  for (int pos = 16; pos <= 90; pos += 2) {

    gate.write(pos);

    delay(10);
  }

  delay(2500);
}

// =====================================
// CLOSE GATE
// =====================================
void closeGate() {

  Serial.println("Closing Gate");

  for (int pos = 90; pos >= 16; pos -= 2) {

    gate.write(pos);

    delay(25);
  }

  // Stop servo signal
  gate.detach();
}