#pragma once

#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// ===== PIN LED =====
#define PIN_EYES      5
#define PIN_RING_BIG  6
#define PIN_LEG_23    7
#define PIN_LEG_01    8
#define PIN_LEG_45    9

// ===== NUM LED =====
#define NUM_EYES      21
#define NUM_RING_BIG  60
#define NUM_LEG       26

// ===== PIN I2C SERVO =====
#define SDA_PIN       11
#define SCL_PIN       12
#define SERVO_MIN     102
#define SERVO_MAX     512

// ===== WiFi =====
#define AP_SSID "Cerbero"
#define AP_PASS "cerbero2024"

// ===== STRUTTURE =====
struct LegChannels {
  uint8_t coxa, femur, tibia;
  uint8_t driver;
};

struct LegCalib {
  int coxaCentro   = 90;
  int femurCentro  = 90;
  int tibiaCentro  = 90;
  int ciclo0Femur  = 160;
  int ciclo0Tibia  = 105;
  int ciclo1FemurC = 175;
  int ciclo1FemurA = 145;
};

// ===== OGGETTI GLOBALI =====
extern Adafruit_NeoPixel eyes;
extern Adafruit_NeoPixel ringBig;
extern Adafruit_NeoPixel leg01;
extern Adafruit_NeoPixel leg23;
extern Adafruit_NeoPixel leg45;

extern Adafruit_PWMServoDriver driver0;
extern Adafruit_PWMServoDriver driver1;

extern LegChannels legs[6];
extern LegCalib calibs[6];

// ===== STATO LED =====
extern bool legsOn;
extern bool ringBigOn;
extern bool eyesOn;
extern bool masterOn;

extern uint8_t legsR, legsG, legsB;
extern uint8_t ringR, ringG, ringB;

extern String legsAnim;
extern String eyesAnim;
