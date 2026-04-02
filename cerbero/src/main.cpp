#include "config.h"
#include <math.h>

void setup() {
  Serial.begin(115200);
  servo_init();
  leds_init();
  setupWiFi();
  statoTimer = millis();
}

void loop() {
  uint32_t t = millis();
  unsigned long elapsed = t - statoTimer;

  ws.cleanupClients();

  if (stato == RUNNING) {
    runWebappAnimations(t);
    delay(18);
    return;
  }

  switch (stato) {
    case BOOT_RING_BIANCO:
      animRing(255,255,255,0.6);
      leg01.clear(); leg23.clear(); leg45.clear(); eyes.clear();
      if (elapsed >= 6000) { stato=BOOT_RING_ROSSO; statoTimer=t; ringPos=0; }
      break;

    case BOOT_RING_ROSSO:
      animRing(255,0,0,0.6);
      leg01.clear(); leg23.clear(); leg45.clear(); eyes.clear();
      if (elapsed >= 6000) { stato=BOOT_RING_ARANCIONE; statoTimer=t; ringPos=0; }
      break;

    case BOOT_RING_ARANCIONE:
      animRing(255,80,0,0.6);
      leg01.clear(); leg23.clear(); leg45.clear(); eyes.clear();
      if (elapsed >= 6000) { stato=BOOT_RING_BLU; statoTimer=t; ringPos=0; }
      break;

    case BOOT_RING_BLU:
      animRing(0,0,255,0.6);
      leg01.clear(); leg23.clear(); leg45.clear(); eyes.clear();
      if (elapsed >= 6000) { stato=BOOT_ZAMPE_ROTAZIONE; statoTimer=t; }
      break;

    case BOOT_ZAMPE_ROTAZIONE:
      animRing(0,0,255,0.3);
      animZampeRotazione(t);
      eyes.clear();
      if (elapsed >= 15000) { stato=BOOT_ZAMPE_KITT; statoTimer=t; kittPos=0; kittDir=true; }
      break;

    case BOOT_ZAMPE_KITT:
      animRing(0,0,255,0.3);
      animZampeKitt(t);
      animOcchio(t,
        elapsed > 8000,
        elapsed > 12000,
        constrain((elapsed-12000)/2000.0f,0.0f,1.0f)
      );
      if (elapsed >= 16000) { stato=BOOT_ZAMPE_WAVE; statoTimer=t; }
      break;

    case BOOT_ZAMPE_WAVE:
      animRing(0,0,255,0.3);
      animZampeWave(t);
      animOcchio(t,true,true,1.0f);
      if (elapsed >= 7000) { stato=BOOT_ZAMPE_IDLE; statoTimer=t; }
      break;

    case BOOT_ZAMPE_IDLE: {
      animRing(0,0,255,0.3);
      float progress = constrain(elapsed/2000.0f,0.0f,1.0f);
      uint8_t b = 180*progress;
      uint8_t g = 20*progress;
      for (int i = 0; i < NUM_LEG; i++) {
        leg01.setPixelColor(i, leg01.Color(0,g,b));
        leg23.setPixelColor(i, leg23.Color(0,g,b));
        leg45.setPixelColor(i, leg45.Color(0,g,b));
      }
      animOcchio(t,true,true,1.0f);
      if (elapsed >= 3000) { stato=BOOT_FINALE; statoTimer=t; }
      break;
    }

    case BOOT_FINALE:
      animRing(0,0,255,0.3);
      setZampeBlu();
      setOcchioBlu();
      if (elapsed >= 2000) { stato=RUNNING; }
      break;

    default: break;
  }

  ringBig.show();
  leg01.show(); leg23.show(); leg45.show();
  eyes.show();
  delay(18);
}
