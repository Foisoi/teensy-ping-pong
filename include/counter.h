#ifndef PINGPONG_COUNTER
#define PINGPONG_COUNTER

#include "primitives.h"

// WARNING!!!
// The whole code for displaying numbers is temporary. It should and it WILL be replaced with more effective approach of drawing (by using functions).

void display_one(uint16_t * fb, int x, int y, uint16_t color) {
    point(fb, x - 2, y, color);
    point(fb, x - 2, y - 1, color);
    point(fb, x, y - 1, color);
    point(fb, x, y - 2, color);
    point(fb, x, y - 3, color);
    for (int i = -4; i < 6; i++) {
        point(fb, x + 1, y + i, color);
    }
    for (int i = -1; i < 4; i++) {
        point(fb, x + i, y + 5, color);
    }
}

void display_seven(uint16_t * fb, int x, int y, uint16_t color) {
    for (int i = -1; i < 3; i++) {
        point(fb, x + i, y, color);
        point(fb, x + i, y - 4, color);
    }
    point(fb, x - 2, y - 4, color);
    point(fb, x + 3, y - 4, color);
    line(fb, x + 2, y - 4, x - 1, y + 5, color);
}

void display_eight(uint16_t * fb, int x, int y, uint16_t color) {
    for (int i = -1; i < 3; i++) {
        point(fb, x + i, y, color);
        point(fb, x + i, y + 5, color);
        point(fb, x + i, y - 4, color);
    }
    for (int i = -3; i < 0; i++) {
        point(fb, x + 3, y + i, color);
        point(fb, x - 2, y + i, color);
    }
    for (int i = 1; i < 5; i++) {
        point(fb, x + 3, y + i, color);
        point(fb, x - 2, y + i, color);
    }
}

void display_nine(uint16_t * fb, int x, int y, uint16_t color) {
    uint16_t tp1 = get_point(fb, x - 2, y + 1);
    uint16_t tp2 = get_point(fb, x - 2, y + 2);
    uint16_t tp3 = get_point(fb, x - 2, y + 3);

    display_eight(fb, x, y, color);
    point(fb, x - 2, y + 1, tp1);
    point(fb, x - 2, y + 2, tp2);
    point(fb, x - 2, y + 3, tp3);
}

void display_nought(uint16_t * fb, int x, int y, uint16_t color) {
    for (int i = -1; i < 3; i++) {
        point(fb, x + i, y - 4, color);
        point(fb, x + i, y + 5, color);
    }
    for (int i = -3; i < 5; i++) {
        point(fb, x - 2, y + i, color);
        point(fb, x + 3, y + i, color);
    }
}

void display_four(uint16_t * fb, int x, int y, uint16_t color) {
    for (int i = -2; i < 3; i++) {
        point(fb, x + i, y + 1, color);
    }
    point(fb, x - 2, y, color);
    point(fb, x - 1, y - 1, color);
    point(fb, x - 1, y - 2, color);
    point(fb, x, y - 3, color);
    point(fb, x, y - 4, color);
    point(fb, x + 3, y, color);
    point(fb, x + 1, y + 2, color);
    point(fb, x + 1, y + 3, color);
    point(fb, x + 1, y + 4, color);
    point(fb, x, y + 5, color);
    point(fb, x + 2, y + 5, color);
    point(fb, x + 1, y + 5, color);
    point(fb, x, y + 5, color);
}

void display_five(uint16_t * fb, int x, int y, uint16_t color) {
    for (int i = -1; i < 3; i++) {
        point(fb, x + i, y, color);
        point(fb, x + i, y - 4, color);
        point(fb, x + i, y + 5, color);
    }
    point(fb, x + 3, y - 4, color);
    point(fb, x - 2, y + 4, color);
    for (int i = -4; i < 1; i++) {
        point(fb, x - 1, y + i, color);
    }
    for (int i = 1; i < 5; i++) {
        point(fb, x + 3, y + i, color);
    }
}

void display_six(uint16_t * fb, int x, int y, uint16_t color) {
    for (int i = -2; i < 5; i++) {
        point(fb, x - 2, y + i, color);
    }
    point(fb, x - 1, y - 3, color);
    point(fb, x + 3, y - 3, color);
    for (int i = -1; i < 3; i++) {
        point(fb, x + i, y, color);
        point(fb, x + i, y + 5, color);
    }
    for (int i = 0; i < 4; i++) {
        point(fb, x + i, y - 4, color);
    }
    for (int i = 1; i < 5; i++) {
        point(fb, x + 3, y + i, color);
    }
}

void display_three(uint16_t * fb, int x, int y, uint16_t color) {
    point(fb, x + 2, y - 1, color);
    point(fb, x + 3, y - 2, color);
    point(fb, x + 3, y - 3, color);
    point(fb, x + 2, y - 4, color);
    point(fb, x + 1, y - 4, color);
    point(fb, x, y - 4, color);
    point(fb, x - 1, y - 3, color);

    point(fb, x + 1, y, color);
    point(fb, x + 1, y + 1, color);
    point(fb, x + 2, y + 1, color);
    point(fb, x + 3, y + 2, color);
    point(fb, x + 3, y + 3, color);
    point(fb, x + 2, y + 4, color);
    point(fb, x + 2, y + 5, color);
    point(fb, x + 1, y + 5, color);
    point(fb, x, y + 5, color);
    point(fb, x - 1, y + 5, color);
    point(fb, x - 2, y + 4, color);
}

void display_two(uint16_t * fb, int x, int y, uint16_t color) {
    point(fb, x - 2, y - 1, color);
    point(fb, x - 2, y - 2, color);
    point(fb, x - 1, y - 3, color);
    point(fb, x, y - 4, color);
    point(fb, x + 1, y - 4, color);
    point(fb, x + 2, y - 4, color);
    point(fb, x + 2, y - 3, color);
    point(fb, x + 3, y - 3, color);
    point(fb, x + 3, y - 2, color);
    point(fb, x + 3, y - 1, color);
    point(fb, x + 2, y, color);
    point(fb, x + 1, y + 1, color);
    point(fb, x + 1, y + 2, color);
    point(fb, x, y + 3, color);
    point(fb, x - 1, y + 4, color);
    point(fb, x - 2, y + 5, color);
    point(fb, x - 1, y + 5, color);
    point(fb, x, y + 5, color);
    point(fb, x + 1, y + 5, color);
    point(fb, x + 2, y + 5, color);
    point(fb, x + 3, y + 5, color);
}

void display_number(uint16_t * fb, int x, int y, int number, int length, uint16_t color = BLUE) {
    // debug: 
    // point(fb, x, y, rgb565(255, 255, 255));
    auto display_digit = [&](int digit) {
        if (digit == 1) display_one(fb, x, y, color);
        if (digit == 2) display_two(fb, x, y, color);
        if (digit == 3) display_three(fb, x, y, color);
        if (digit == 4) display_four(fb, x, y, color);
        if (digit == 5) display_five(fb, x, y, color);
        if (digit == 6) display_six(fb, x, y, color);
        if (digit == 7) display_seven(fb, x, y, color);
        if (digit == 8) display_eight(fb, x, y, color);
        if (digit == 9) display_nine(fb, x, y, color);
        if (digit == 0) display_nought(fb, x, y, color);
    };
    // int length = trunc(log10(number)) + 1;
    x += ((length - 1) * 10);
    while (number != 0) {
        display_digit(number % 10);
        x -= 10;
        number -= (number % 10);
        number /= 10;
    }
}

#endif