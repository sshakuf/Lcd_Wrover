#ifndef SCREEN_H
#define SCREEN_H

#include "SPI.h"
#include "Adafruit_GFX.h"
#include "WROVER_KIT_LCD.h"

extern WROVER_KIT_LCD tft;

unsigned long testText();
unsigned long testFillScreen();
unsigned long testLines(uint16_t color);
unsigned long testFastLines(uint16_t color1, uint16_t color2);
unsigned long testRects(uint16_t color);
unsigned long testFilledRects(uint16_t color1, uint16_t color2);
unsigned long testFilledCircles(uint8_t radius, uint16_t color);
unsigned long testCircles(uint8_t radius, uint16_t color);
unsigned long testTriangles();
unsigned long testFilledTriangles();
unsigned long testRoundRects();
unsigned long testFilledRoundRects();

void InitializeTFT();

#endif