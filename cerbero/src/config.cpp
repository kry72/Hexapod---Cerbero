#include "config.h"

Adafruit_NeoPixel eyes(NUM_EYES, PIN_EYES, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ringBig(NUM_RING_BIG, PIN_RING_BIG, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leg01(NUM_LEG, PIN_LEG_01, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leg23(NUM_LEG, PIN_LEG_23, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leg45(NUM_LEG, PIN_LEG_45, NEO_GRB + NEO_KHZ800);

Adafruit_PWMServoDriver driver0 = Adafruit_PWMServoDriver(0x40, Wire);
Adafruit_PWMServoDriver driver1 = Adafruit_PWMServoDriver(0x41, Wire);

LegChannels legs[6] = {
  {2, 1, 0, 0},
  {6, 5, 4, 0},
  {13,14,15, 0},
  {2, 1, 0, 1},
  {9,10,11, 1},
  {13,14,15, 1}
};

LegCalib calibs[6];

bool legsOn    = true;
bool ringBigOn = true;
bool eyesOn    = true;
bool masterOn  = true;

uint8_t legsR = 0, legsG = 0, legsB = 255;
uint8_t ringR = 255, ringG = 255, ringB = 255;

String legsAnim = "rotazione";
String eyesAnim = "respiro";

BootState stato = BOOT_RING_BIANCO;
unsigned long statoTimer = 0;

float ringPos  = 0;
float eyePos8  = 0;
int   kittPos  = 0;
bool  kittDir  = true;
unsigned long lastKittMove = 0;
