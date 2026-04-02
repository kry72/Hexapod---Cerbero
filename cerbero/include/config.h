#pragma once
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// ===== WiFi =====
#define AP_SSID "Cerbero"
#define AP_PASS "cerbero2024"

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

// ===== SERVO =====
#define SDA_PIN   11
#define SCL_PIN   12
#define SERVO_MIN 102
#define SERVO_MAX 512

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

// ===== BOOT STATE =====
enum BootState {
  BOOT_RING_BIANCO,
  BOOT_RING_ROSSO,
  BOOT_RING_ARANCIONE,
  BOOT_RING_BLU,
  BOOT_ZAMPE_ROTAZIONE,
  BOOT_ZAMPE_KITT,
  BOOT_ZAMPE_WAVE,
  BOOT_ZAMPE_IDLE,
  BOOT_FINALE,
  RUNNING
};

// ===== EXTERN =====
extern Adafruit_NeoPixel eyes;
extern Adafruit_NeoPixel ringBig;
extern Adafruit_NeoPixel leg01;
extern Adafruit_NeoPixel leg23;
extern Adafruit_NeoPixel leg45;

extern Adafruit_PWMServoDriver driver0;
extern Adafruit_PWMServoDriver driver1;

extern LegChannels legs[6];
extern LegCalib calibs[6];

extern bool legsOn, ringBigOn, eyesOn, masterOn;
extern uint8_t legsR, legsG, legsB;
extern uint8_t ringR, ringG, ringB;
extern String legsAnim, eyesAnim;

extern BootState stato;
extern unsigned long statoTimer;
extern float ringPos;
extern float eyePos8;
extern int kittPos;
extern bool kittDir;
extern unsigned long lastKittMove;

extern AsyncWebSocket ws;

void moveServo(uint8_t driverIdx, uint8_t ch, int gradi);
void moveLeg(int legIdx, int coxa, int femur, int tibia);
void setupWiFi();
void leds_init();
void servo_init();
void animRing(uint8_t r, uint8_t g, uint8_t b, float speed);
void animZampeRotazione(uint32_t t);
void animZampeKitt(uint32_t t);
void animZampeWave(uint32_t t);
void setZampeBlu();
void animOcchio(uint32_t t, bool show8, bool showCentrale, float centraleFade);
void setOcchioBlu();
void runWebappAnimations(uint32_t t);
