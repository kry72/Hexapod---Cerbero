#include "config.h"

Adafruit_PWMServoDriver driver0 = Adafruit_PWMServoDriver(0x40, Wire);
Adafruit_PWMServoDriver driver1 = Adafruit_PWMServoDriver(0x41, Wire);

LegChannels legs[6] = {
  {2, 1, 0, 0},   // RF
  {6, 5, 4, 0},   // LF
  {13,14,15, 0},  // LB
  {2, 1, 0, 1},   // RB
  {9,10,11, 1},   // RM
  {13,14,15, 1}   // LM
};

LegCalib calibs[6];

void servo_init() {
  Wire.begin(SDA_PIN, SCL_PIN);
  driver0.begin(); driver0.setOscillatorFrequency(27000000); driver0.setPWMFreq(50);
  driver1.begin(); driver1.setOscillatorFrequency(27000000); driver1.setPWMFreq(50);

  // RF già calibrata
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
