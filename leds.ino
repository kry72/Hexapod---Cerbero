#include "config.h"

Adafruit_NeoPixel eyes(NUM_EYES, PIN_EYES, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ringBig(NUM_RING_BIG, PIN_RING_BIG, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leg01(NUM_LEG, PIN_LEG_01, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leg23(NUM_LEG, PIN_LEG_23, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leg45(NUM_LEG, PIN_LEG_45, NEO_GRB + NEO_KHZ800);

bool legsOn    = true;
bool ringBigOn = true;
bool eyesOn    = true;
bool masterOn  = true;

uint8_t legsR = 0, legsG = 0, legsB = 255;
uint8_t ringR = 255, ringG = 255, ringB = 255;

String legsAnim = "rotazione";
String eyesAnim = "respiro";

float legsPhase = 0;
float ringPos = 0;
unsigned long ringColorTimer = 0;
int ringColorFase = 0;
int kittPos = 0;
bool kittDir = true;
unsigned long lastKittMove = 0;

void leds_init() {
  eyes.begin();    eyes.setBrightness(80);    eyes.show();
  ringBig.begin(); ringBig.setBrightness(60); ringBig.show();
  leg01.begin();   leg01.setBrightness(70);   leg01.show();
  leg23.begin();   leg23.setBrightness(70);   leg23.show();
  leg45.begin();   leg45.setBrightness(70);   leg45.show();
  ringColorTimer = millis();
}

void animaZampe(uint32_t t) {
  if (!legsOn || !masterOn) {
    leg01.clear(); leg23.clear(); leg45.clear();
    leg01.show(); leg23.show(); leg45.show();
    return;
  }
  if (legsAnim == "rotazione") {
    legsPhase += 0.25;
    if (legsPhase >= NUM_LEG) legsPhase = 0;
    for (int i = 0; i < NUM_LEG; i++) {
      float dist = fabs(i - legsPhase);
      if (dist > NUM_LEG/2) dist = NUM_LEG - dist;
      float fade = dist < 8 ? pow(1.0-(dist/8.0),2) : 0;
      leg01.setPixelColor(i, leg01.Color(legsR*fade, legsG*fade, legsB*fade));
      leg23.setPixelColor(i, leg23.Color(legsR*fade, legsG*fade, legsB*fade));
      leg45.setPixelColor(i, leg45.Color(legsR*fade, legsG*fade, legsB*fade));
    }
  } else if (legsAnim == "kitt") {
    if (millis() - lastKittMove > 30) {
      lastKittMove = millis();
      leg01.clear(); leg23.clear(); leg45.clear();
      for (int i = 0; i < 10; i++) {
        int idx = kittPos + i;
        if (idx >= 0 && idx < NUM_LEG) {
          float fade = pow(1.0-(i/10.0),2);
          leg01.setPixelColor(idx, leg01.Color(legsR*fade, legsG*fade, legsB*fade));
          leg23.setPixelColor(idx, leg23.Color(legsR*fade, legsG*fade, legsB*fade));
          leg45.setPixelColor(idx, leg45.Color(legsR*fade, legsG*fade, legsB*fade));
        }
      }
      if (kittDir) { kittPos++; if (kittPos >= NUM_LEG-10) kittDir=false; }
      else         { kittPos--; if (kittPos <= 0) kittDir=true; }
    }
  } else if (legsAnim == "wave") {
    for (int i = 0; i < NUM_LEG; i++) {
      float wave = (sin(i*0.4+t/400.0)+1.0)/2.0;
      uint8_t bright = 80 + wave*175;
      leg01.setPixelColor(i, leg01.Color(legsR*bright/255, legsG*bright/255, legsB*bright/255));
      leg23.setPixelColor(i, leg23.Color(legsR*bright/255, legsG*bright/255, legsB*bright/255));
      leg45.setPixelColor(i, leg45.Color(legsR*bright/255, legsG*bright/255, legsB*bright/255));
    }
  } else {
    float breath = (sin(t/1500.0)+1.0)/2.0;
    uint8_t b = 60 + breath*150;
    for (int i = 0; i < NUM_LEG; i++) {
      leg01.setPixelColor(i, leg01.Color(0,0,b));
      leg23.setPixelColor(i, leg23.Color(0,0,b));
      leg45.setPixelColor(i, leg45.Color(0,0,b));
    }
  }
  leg01.show(); leg23.show(); leg45.show();
}

void animaRing(uint32_t t) {
  if (!ringBigOn || !masterOn) { ringBig.clear(); ringBig.show(); return; }
  if (millis() - ringColorTimer > 5000) {
    ringColorFase = (ringColorFase+1)%3;
    ringColorTimer = millis();
  }
  ringPos += 0.5;
  if (ringPos >= NUM_RING_BIG) ringPos = 0;
  uint8_t r,g,b;
  switch (ringColorFase) {
    case 0: r=ringR; g=ringG; b=ringB; break;
    case 1: r=255;   g=0;     b=0;     break;
    case 2: r=0;     g=0;     b=255;   break;
  }
  ringBig.clear();
  for (int i = 0; i < 20; i++) {
    float fade = pow(1.0-(i/20.0),2);
    int idx = ((int)ringPos+i)%NUM_RING_BIG;
    ringBig.setPixelColor(idx, ringBig.Color(r*fade,g*fade,b*fade));
  }
  ringBig.show();
}

void animaOcchio(uint32_t t) {
  if (!eyesOn || !masterOn) { eyes.clear(); eyes.show(); return; }
  float breath = (sin(t/1500.0)+1.0)/2.0;
  if (eyesAnim == "respiro") {
    uint8_t b = 30 + breath*200;
    for (int i = 0; i < 12; i++) eyes.setPixelColor(i, eyes.Color(0,0,b));
    uint8_t b2 = 20 + breath*150;
    for (int i = 12; i < 20; i++) eyes.setPixelColor(i, eyes.Color(0,b2/3,b2));
    uint8_t bc = 80 + breath*175;
    eyes.setPixelColor(20, eyes.Color(bc/4,bc/4,bc));
  } else if (eyesAnim == "pulsar") {
    float pulse = pow((sin(t/400.0)+1.0)/2.0,3);
    uint8_t p = pulse*255;
    for (int i = 0; i < 12; i++) eyes.setPixelColor(i, eyes.Color(p/4,p/4,p));
    for (int i = 12; i < 20; i++) eyes.setPixelColor(i, eyes.Color(0,p/3,p));
    eyes.setPixelColor(20, eyes.Color(p,p,p));
  } else {
    uint8_t o = 150 + breath*105;
    for (int i = 0; i < 12; i++) eyes.setPixelColor(i, eyes.Color(o,o/3,0));
    for (int i = 12; i < 20; i++) eyes.setPixelColor(i, eyes.Color(o/2,o/6,0));
    eyes.setPixelColor(20, eyes.Color(255,180,0));
  }
  eyes.show();
}
