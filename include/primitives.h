#ifndef PINGPONG_PRIMITIVES_H
#define PINGPONG_PRIMITIVES_H

#include <Arduino.h>

#define WIDTH 320
#define HEIGHT 240

#define RED rgb565(214, 34, 70)
#define BLUE rgb565(14, 124, 123)
#define WHITE 65500

struct dot { int x; int y; };

uint16_t rgb565(uint8_t r, uint8_t g, uint8_t b) {
    return (uint16_t) (((r >> 3) & 0x1f) << 11 | ((g >> 2) & 0x3f) << 5 | ((b >> 3) & 0x1f));
}

void point(uint16_t * fb, int x, int y, uint16_t color = 255) {
    int coordinate = (WIDTH * y) + x;
    if (coordinate < (HEIGHT * WIDTH) && x > -1 && y > -1) fb[coordinate] = color;
}

uint16_t get_point(uint16_t * fb, int x, int y) {
    int coordinate = (WIDTH * y) + x;
    if (coordinate < (HEIGHT * WIDTH) && x > -1 && y > -1) return fb[coordinate];
    return 0;
}

void rectangle(uint16_t * fb, int x, int y, int w, int h, uint16_t color = 255) {
    for (int xi = x; xi <= x + w; xi++) {
        point(fb, xi, y, color);
        point(fb, xi, y + h, color);
    }
    for (int yi = y; yi <= y + h; yi++) {
        point(fb, x, yi, color);
        point(fb, x + w, yi, color);
    }
}

void filled_rectangle(uint16_t * fb, int x, int y, int w, int h, uint16_t color = 255) {
    for (int i = x; i <= x + w; i++) {
        rectangle(fb, x, y, i - x, h, color);
    }
}

void octant(uint16_t * fb, int x, int y, int xc, int yc, uint16_t color = 255) {
    point(fb, xc + x, y + yc, color);
    point(fb, xc - x,y + yc, color);
    point(fb, x + xc, -y + yc, color);
    point(fb, -x + xc, -y + yc, color);
    point(fb, y + xc, x + yc, color);
    point(fb, y + xc, -x + yc, color);
    point(fb, -y + xc, x + yc, color);
    point(fb, -y + xc, -x + yc, color);
}

void circle(uint16_t * fb, int xc, int yc, int radius, uint16_t color = 255) {
    int pk, x, y;
    pk = 3 - 2 * radius;
    x = 0;
    y = radius;
    octant(fb, x, y, xc, yc, color);
    while (x < y) {
        if (pk <= 0) {
            pk += ((4 * x) + 6);
            octant(fb, ++x, y, xc, yc, color);
        } else {
            pk += ((4 * (x - y)) + 10);
            octant(fb, ++x, --y, xc, yc, color);
        }
    }
}

void filled_circle(uint16_t * fb, int xc, int yc, int radius, uint16_t color = 255) {
    int radius_sqr = radius * radius;
    for (int x = -radius; x < radius; x++) {
        int hh = (int) sqrt(radius_sqr - x * x);
        int rx = xc + x;
        int ph = yc + hh;

        for (int y = yc - hh; y < ph; y++) point(fb, rx, y, color);
    }
}

void line(uint16_t * fb, int x0, int y0, int x1, int y1, uint16_t color = 255) {
    int dx = abs(x1 - x0);
    int sx = x0 < x1 ? 1 : -1;
    int dy = -abs(y1 - y0);
    int sy = y0 < y1 ? 1 : -1;
    int err = dx + dy;

    while (true) {
        point(fb, x0, y0, color);
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            x0 += sx;
        }
        if (e2 <= dx) {
            err += dx;
            y0 += sy;
        }
    }
}

#endif