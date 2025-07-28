#include <Servo.h>

Servo lidServo;

const int irSensorPin = 2;     // FC-51 OUT pin connected to D2
const int servoPin = 9;        // Servo signal pin connected to D9

int objectDetected = LOW;
unsigned long lastOpenTime = 0;
bool lidOpen = false;

void setup() {
  pinMode(irSensorPin, INPUT);
  lidServo.attach(servoPin);
  lidServo.write(0); // Start with lid closed
  Serial.begin(9600);
}

void loop() {
  objectDetected = digitalRead(irSensorPin);

  if (objectDetected == LOW && !lidOpen) {
    // Object is near (FC-51 gives LOW when something is detected)
    Serial.println("Object Detected - Opening Lid");
    lidServo.write(90);     // Open lid
    lidOpen = true;
    lastOpenTime = millis();
  }

  // Close lid after 3 seconds
  if (lidOpen && millis() - lastOpenTime >= 3000) {
    Serial.println("Closing Lid");
    lidServo.write(0);      // Close lid
    lidOpen = false;
  }
}
