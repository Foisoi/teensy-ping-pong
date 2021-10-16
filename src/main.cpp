#include <Arduino.h>
#include "ILI9341_T4.h"
#include "board.h"

#define PIN_SCK 13
#define PIN_MISO 12
#define PIN_MOSI 11
#define PIN_DC 10
#define PIN_CS 9
#define PIN_RESET 6
#define PIN_BACKLIGHT 255
#define PIN_TOUCH_IRQ 255
#define PIN_TOUCH_CS 255

#define SPI_SPEED 60000000


ILI9341_T4::ILI9341Driver tft(PIN_CS, PIN_DC, PIN_SCK, PIN_MOSI, PIN_MISO, PIN_RESET, PIN_TOUCH_CS, PIN_TOUCH_IRQ);

// 2 diff buffers with about 6K memory each
ILI9341_T4::DiffBuffStatic <6000> diff1;
ILI9341_T4::DiffBuffStatic <6000> diff2;

uint16_t internal_fb[HEIGHT * WIDTH]; // used by the library for buffering
uint16_t main_fb[HEIGHT * WIDTH]; // the main framebuffer we draw onto.

void clear(uint16_t * fb, uint16_t color = 0) {
    for (int i = 0; i < HEIGHT * WIDTH; i++) fb[i] = color;
}

void setup() {
    Serial.begin(9600);

    tft.output(&Serial);

    while (!tft.begin(SPI_SPEED)) {
        Serial.println("Initialization error...");
        delay(1000);
    }

    tft.setRotation(-1);

    tft.setFramebuffers(internal_fb);

    tft.setDiffBuffers(&diff1, &diff2);
    tft.setDiffGap(4);

    tft.setRefreshRate(120);
    tft.setVSyncSpacing(2);

    if (PIN_BACKLIGHT != 255) {
        pinMode(PIN_BACKLIGHT, OUTPUT);
        digitalWrite(PIN_BACKLIGHT, HIGH);
    }
    pinMode(20, INPUT);
    pinMode(21, INPUT);
}

void render() {
    for (int i_s = 0; i_s < 5; i_s++) {
        strike_effect(main_fb, strikes[i_s]);
    }
    board(main_fb);
    plates(main_fb, analogRead(20));
    ball(main_fb);
}

void loop() {
    clear(main_fb);
    render();
    tft.update(main_fb);
}
