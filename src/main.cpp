#include "SPI.h"
#include "Adafruit_GFX.h"
#include "WROVER_KIT_LCD.h"
#include "Screen.h"
#include "Server.h"

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

#include <WiFi.h>

void setup()
{
  Serial.begin(115200);

  Serial.println("Setup");

  InitializeTFT();

  setupServer();

  Serial.println(F("Done!"));
}

void loop(void)
{

  testText();

  while (1)
  {
    Serverloop();
  }
}

