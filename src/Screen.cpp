#include "Screen.h"
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "WROVER_KIT_LCD.h"

#define min(X, Y) (((X) < (Y)) ? (X) : (Y))

WROVER_KIT_LCD tft;

#include "soc/soc.h"
#include "soc/rtc_cntl_reg.h"

void InitializeTFT()
{
    WRITE_PERI_REG(RTC_CNTL_BROWN_OUT_REG, 0); //disable brownout detector

    tft.begin();
    tft.setRotation(1);

    uint8_t x = 0;
    uint32_t id = tft.readId();
    if (id)
    {
        Serial.println("======= WROVER ST7789V Display Test ========");
    }
    else
    {
        Serial.println("======= WROVER ILI9341 Display Test ========");
    }
    Serial.println("============================================");
    Serial.printf("Display ID:      0x%06X\n", id);

    x = tft.readcommand8(WROVER_RDDST);
    Serial.print("Status:          0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(WROVER_RDDPM);
    Serial.print("Power Mode:      0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(WROVER_RDDMADCTL);
    Serial.print("MADCTL Mode:     0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(WROVER_RDDCOLMOD);
    Serial.print("Pixel Format:    0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(WROVER_RDDIM);
    Serial.print("Image Format:    0x");
    Serial.println(x, HEX);
    x = tft.readcommand8(WROVER_RDDSDR);
    Serial.print("Self Diagnostic: 0x");
    Serial.println(x, HEX);

    tft.setRotation(1);

    Serial.println(F("Done!"));
}

unsigned long testFillScreen()
{
    unsigned long start = micros();
    tft.fillScreen(WROVER_BLACK);
    yield();
    tft.fillScreen(WROVER_RED);
    yield();
    tft.fillScreen(WROVER_GREEN);
    yield();
    tft.fillScreen(WROVER_BLUE);
    yield();
    tft.fillScreen(WROVER_BLACK);
    yield();
    return micros() - start;
}

unsigned long testText()
{
    tft.fillScreen(WROVER_BLACK);
    unsigned long start = micros();
    tft.setCursor(0, 0);
    tft.setTextColor(WROVER_WHITE);
    tft.setTextSize(1);
    // tft.println(WiFi.localIP());
    tft.setTextColor(WROVER_YELLOW);
    tft.setTextSize(2);
    tft.setTextColor(WROVER_RED);
    tft.setTextSize(3);
    tft.println();
    tft.setTextColor(WROVER_GREEN);
    tft.setTextSize(4);
    tft.println("Gil is KAKA");
    tft.setTextSize(2);
    tft.println("haha");
    tft.setTextSize(1);
    tft.setTextColor(WROVER_YELLOW);
    tft.println("you are big big KAKA");
    tft.println("but i LOVE you anyway");
    tft.setTextSize(3);
    tft.setTextColor(WROVER_GREEN);
    tft.println("BUT");
    tft.println("I Still");
    tft.setTextSize(5);
    tft.setTextColor(WROVER_RED);
    tft.println("LOVE");
    tft.println("YOU");
    return micros() - start;
}

unsigned long testLines(uint16_t color)
{
    unsigned long start, t;
    int x1, y1, x2, y2,
        w = tft.width(),
        h = tft.height();

    tft.fillScreen(WROVER_BLACK);
    yield();

    x1 = y1 = 0;
    y2 = h - 1;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    x2 = w - 1;
    for (y2 = 0; y2 < h; y2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    t = micros() - start; // fillScreen doesn't count against timing

    yield();
    tft.fillScreen(WROVER_BLACK);
    yield();

    x1 = w - 1;
    y1 = 0;
    y2 = h - 1;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    x2 = 0;
    for (y2 = 0; y2 < h; y2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    t += micros() - start;

    yield();
    tft.fillScreen(WROVER_BLACK);
    yield();

    x1 = 0;
    y1 = h - 1;
    y2 = 0;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    x2 = w - 1;
    for (y2 = 0; y2 < h; y2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    t += micros() - start;

    yield();
    tft.fillScreen(WROVER_BLACK);
    yield();

    x1 = w - 1;
    y1 = h - 1;
    y2 = 0;
    start = micros();
    for (x2 = 0; x2 < w; x2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);
    x2 = 0;
    for (y2 = 0; y2 < h; y2 += 6)
        tft.drawLine(x1, y1, x2, y2, color);

    yield();
    return micros() - start;
}

unsigned long testFastLines(uint16_t color1, uint16_t color2)
{
    unsigned long start;
    int x, y, w = tft.width(), h = tft.height();

    tft.fillScreen(WROVER_BLACK);
    start = micros();
    for (y = 0; y < h; y += 5)
        tft.drawFastHLine(0, y, w, color1);
    for (x = 0; x < w; x += 5)
        tft.drawFastVLine(x, 0, h, color2);

    return micros() - start;
}

unsigned long testRects(uint16_t color)
{
    unsigned long start;
    int n, i, i2,
        cx = tft.width() / 2,
        cy = tft.height() / 2;

    tft.fillScreen(WROVER_BLACK);
    n = min(tft.width(), tft.height());
    start = micros();
    for (i = 2; i < n; i += 6)
    {
        i2 = i / 2;
        tft.drawRect(cx - i2, cy - i2, i, i, color);
    }

    return micros() - start;
}

unsigned long testFilledRects(uint16_t color1, uint16_t color2)
{
    unsigned long start, t = 0;
    int n, i, i2,
        cx = tft.width() / 2 - 1,
        cy = tft.height() / 2 - 1;

    tft.fillScreen(WROVER_BLACK);
    n = min(tft.width(), tft.height());
    for (i = n; i > 0; i -= 6)
    {
        i2 = i / 2;
        start = micros();
        tft.fillRect(cx - i2, cy - i2, i, i, color1);
        t += micros() - start;
        // Outlines are not included in timing results
        tft.drawRect(cx - i2, cy - i2, i, i, color2);
        yield();
    }

    return t;
}

unsigned long testFilledCircles(uint8_t radius, uint16_t color)
{
    unsigned long start;
    int x, y, w = tft.width(), h = tft.height(), r2 = radius * 2;

    tft.fillScreen(WROVER_BLACK);
    start = micros();
    for (x = radius; x < w; x += r2)
    {
        for (y = radius; y < h; y += r2)
        {
            tft.fillCircle(x, y, radius, color);
        }
    }

    return micros() - start;
}

unsigned long testCircles(uint8_t radius, uint16_t color)
{
    unsigned long start;
    int x, y, r2 = radius * 2,
              w = tft.width() + radius,
              h = tft.height() + radius;

    // Screen is not cleared for this one -- this is
    // intentional and does not affect the reported time.
    start = micros();
    for (x = 0; x < w; x += r2)
    {
        for (y = 0; y < h; y += r2)
        {
            tft.drawCircle(x, y, radius, color);
        }
    }

    return micros() - start;
}

unsigned long testTriangles()
{
    unsigned long start;
    int n, i, cx = tft.width() / 2 - 1,
              cy = tft.height() / 2 - 1;

    tft.fillScreen(WROVER_BLACK);
    n = min(cx, cy);
    start = micros();
    for (i = 0; i < n; i += 5)
    {
        tft.drawTriangle(
            cx, cy - i,     // peak
            cx - i, cy + i, // bottom left
            cx + i, cy + i, // bottom right
            tft.color565(i, i, i));
    }

    return micros() - start;
}

unsigned long testFilledTriangles()
{
    unsigned long start, t = 0;
    int i, cx = tft.width() / 2 - 1,
           cy = tft.height() / 2 - 1;

    tft.fillScreen(WROVER_BLACK);
    start = micros();
    for (i = min(cx, cy); i > 10; i -= 5)
    {
        start = micros();
        tft.fillTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                         tft.color565(0, i * 10, i * 10));
        t += micros() - start;
        tft.drawTriangle(cx, cy - i, cx - i, cy + i, cx + i, cy + i,
                         tft.color565(i * 10, i * 10, 0));
        yield();
    }

    return t;
}

unsigned long testRoundRects()
{
    unsigned long start;
    int w, i, i2,
        cx = tft.width() / 2 - 1,
        cy = tft.height() / 2 - 1;

    tft.fillScreen(WROVER_BLACK);
    w = min(tft.width(), tft.height());
    start = micros();
    for (i = 0; i < w; i += 6)
    {
        i2 = i / 2;
        tft.drawRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(i, 0, 0));
    }

    return micros() - start;
}

unsigned long testFilledRoundRects()
{
    unsigned long start;
    int i, i2,
        cx = tft.width() / 2 - 1,
        cy = tft.height() / 2 - 1;

    tft.fillScreen(WROVER_BLACK);
    start = micros();
    for (i = min(tft.width(), tft.height()); i > 20; i -= 6)
    {
        i2 = i / 2;
        tft.fillRoundRect(cx - i2, cy - i2, i, i, i / 8, tft.color565(0, i, 0));
        yield();
    }

    return micros() - start;
}

void PutText(String inText, int x, int y, int inSize, uint16_t inColor, uint16_t inBgColor)
{
    tft.setCursor(x, y);
    tft.setTextColor(inColor, inBgColor);
    tft.setTextSize(inSize);
    tft.println(inText);
}