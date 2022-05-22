#include <Servo.h>

#define TOUCH_PIN     0
#define MOTOR_PIN     2

#define DOWN        63
#define UP          123
#define NEUTRAL     93

Servo motor;
uint8_t cycle = 0;
boolean raising = false;

void setup(void) {
  Serial.begin(115200);
  delay(100);
  digitalWrite(MOTOR_PIN, LOW);
  motor.attach(MOTOR_PIN);
  delay(100);
  for (uint8_t i = 0; i < 50; i++) {
    motor.write(UP);
    delay(500);
  }
  cycle = 0;
  motor.write(NEUTRAL);
}

void loop(void) {
  static uint32_t _t = 0;
  digitalWrite(MOTOR_PIN, LOW);
  if (!digitalRead(TOUCH_PIN)) {
    if ((cycle > 10) && (cycle < 30)) {
      for (uint8_t i = 0; i < 50; i++) {
        motor.write(UP);
        delay(500);
      }
      cycle = 0;
    } else {
      motor.write(DOWN);
    }
    delay(500);
    motor.write(NEUTRAL);
  }
  if ((millis() - _t) > 600000) {
    if (cycle <= 30) {
      motor.write(DOWN);
      delay(500);
      cycle++;
    }
    _t = millis();
  }
}
