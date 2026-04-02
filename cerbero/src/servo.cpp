#include "config.h"

void servo_init() {
  Wire.begin(SDA_PIN, SCL_PIN);
  driver0.begin(); driver0.setOscillatorFrequency(27000000); driver0.setPWMFreq(50);
  driver1.begin(); driver1.setOscillatorFrequency(27000000); driver1.setPWMFreq(50);

  calibs[0].coxaCentro   = 90;
  calibs[0].femurCentro  = 90;
  calibs[0].tibiaCentro  = 90;
  calibs[0].ciclo0Femur  = 160;
  calibs[0].ciclo0Tibia  = 105;
  calibs[0].ciclo1FemurC = 175;
  calibs[0].ciclo1FemurA = 145;
}

void moveServo(uint8_t driverIdx, uint8_t ch, int gradi) {
  int pwm = map(gradi, 0, 180, SERVO_MIN, SERVO_MAX);
  if (driverIdx == 0) driver0.setPWM(ch, 0, pwm);
  else                driver1.setPWM(ch, 0, pwm);
}

void moveLeg(int legIdx, int coxa, int femur, int tibia) {
  LegChannels& lc = legs[legIdx];
  moveServo(lc.driver, lc.coxa,  coxa);
  moveServo(lc.driver, lc.femur, femur);
  moveServo(lc.driver, lc.tibia, tibia);
}
