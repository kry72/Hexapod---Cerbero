#include "config.h"

void setup() {
  Serial.begin(115200);
  servo_init();
  leds_init();
  wifi_init();
}

void loop() {
  uint32_t t = millis();
  ws.cleanupClients();
  animaZampe(t);
  animaRing(t);
  animaOcchio(t);
  delay(18);
}
