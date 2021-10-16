#ifndef PINGPONG_BOARD
#define PINGPONG_BOARD

#include <Arduino.h>
#include "primitives.h"
#include "counter.h"

#define WIDTH 320
#define HEIGHT 240

// these variables are neccessary for ball drawing
int ball_x = (WIDTH - 6) / 2;
int ball_y = (HEIGHT - 6) / 2;
float ball_acceleration = 2.4;
int ball_trajectory_iter = 0;
dot ball_trajectory[6] = { dot {1, 1}, dot {1, 1}, dot {1, 1}, dot {1, 1}, dot {1, 1}, dot {1, 1} };

// these are for plates
int plate_2_position = -1;
int plate_1_position = -1;
int plate_1_score = 0;
int plate_2_score = 0;

// neccessary for animation of strike when ball hits the border
struct strike {
    dot where;
    int iter;
};
strike strikes[5] = {};
// neccessary for animated striped line in the center of the board
int striped_line_bias = 0;

void indicator(uint16_t * fb, int s1, int s2) {
    int s1_length = trunc(log10(s1)) + 1;
    int s2_length = trunc(log10(s2)) + 1;
    display_number(fb, WIDTH / 2 - 28 - (s1_length * 5), 30, s1, s1_length, rgb565(154, 205, 50));
    display_number(fb, WIDTH / 2 + 33 - (s2_length * 5), 30, s2, s2_length, rgb565(173, 255, 47));
}

void board(uint16_t * fb) {
    rectangle(fb, 0, 0, WIDTH - 1, HEIGHT - 1, WHITE);
    // striped line in the center
    for (int y = -15; y < HEIGHT + 15; y += 15) {
        rectangle(fb, (WIDTH / 2) - 1, y + striped_line_bias, 2, 5, WHITE);
    }
    for (int y = 2; y < HEIGHT - 2; y++) {
        point(fb, (WIDTH / 2), y, WHITE);
    }
    striped_line_bias = (striped_line_bias + 1) % 30;

    indicator(fb, plate_1_score, plate_2_score);
}

void strike_effect(uint16_t * fb, strike & strike_instance) {
    if (strike_instance.iter < 10) {
        circle(fb, strike_instance.where.x, strike_instance.where.y, strike_instance.iter, random(200, 65500));
        strike_instance.iter++;
    }
}

void ball(uint16_t * fb) {
    auto handle_strike = [&]() {
        for (int i = 0; i < 5; i++) {
            if (strikes[i].iter == 9) {
                strikes[i].iter = 0;
                strikes[i].where = dot { ball_x, ball_y };
                return;
            } 
        }
        strikes[0].iter = 0;
        strikes[0].where = dot { ball_x, ball_y };
    };
    auto inverse_y = [&]() {
        handle_strike();
        for (int i = 0; i < 6; i++) ball_trajectory[i].y *= -1;
    };
    auto inverse_x = [&]() {
        handle_strike();
        for (int i = 0; i < 6; i++) ball_trajectory[i].x *= -1;
    };
    auto start_over = [&]() {
        inverse_x();
        ball_x = (WIDTH - 6) / 2;
        ball_y = (HEIGHT - 6) / 2;
    };
    // decresasing ball's acceleration
    float dba = ball_acceleration - 2.4;
    dba = (dba > 0) * dba / (ball_acceleration / 0.145); // 0.145 is a reversed coefficient of air friction (the bigger it is the less the acceleration loss within each bounce)
    ball_acceleration -= dba;
    // calculating ball's coordinates in order to check if there will be any collisions
    dot next = ball_trajectory[ball_trajectory_iter];
    // handling collisions
    if (ball_y + next.y < 10 || ball_y + next.y > HEIGHT - 10) {
        inverse_y();
        ball_acceleration += 1.8;
    }
    // considering case of collision with left plate
    if (ball_x + next.x < (WIDTH / 6) + 5 && ball_x + next.x > (WIDTH / 6) - 5) {
        if (ball_y + next.y < plate_1_position + 75 && ball_y + next.y > plate_1_position - 5) {
            inverse_x();
            ball_acceleration += 1.9;
        }
    }

    // collision with right plate
    if (ball_x + next.x < WIDTH - (WIDTH / 6) + 5 && ball_x + next.x > WIDTH - (WIDTH / 6) - 5) {
        if (ball_y + next.y < plate_2_position + 75 && ball_y + next.y > plate_2_position - 5) {
            inverse_x();
            ball_acceleration += 1.9;
        }
    }
    // when ball hits left border
    if (ball_x + next.x < 10) {
        plate_2_score++;
        start_over();
    }
    // hits right border
    if (ball_x + next.x > WIDTH - 10) {
        plate_1_score++;
        start_over();
    }

    // changing ball's coordinates
    // recalculating ball's coordinates in agreement with previous code which changed traj variable
    next = ball_trajectory[ball_trajectory_iter];
    ball_x += (int) ((float) next.x * ball_acceleration);
    ball_y += (int) ((float) next.y * ball_acceleration);
    filled_circle(fb, ball_x, ball_y, 7, RED);
    ball_trajectory_iter = (ball_trajectory_iter + 1) % 6;
}

void plates(uint16_t * fb, int pot_value) {
    // user's plate:
    int new_plate_position = (int) (((float) pot_value / 1024) * HEIGHT);
    if (plate_1_position == -1) {
        plate_1_position = new_plate_position;
    }

    if (new_plate_position > HEIGHT - 73) {
        filled_rectangle(fb, WIDTH / 6, HEIGHT - 73, 3, 70);
    } else {
        plate_1_position = new_plate_position;
        filled_rectangle(fb, WIDTH / 6, new_plate_position, 3, 70);
    }
    // changing computer's plate position
    float agressiveness = 0.75;
    int change = 5 * ((float) ball_x / (float) WIDTH * agressiveness);
    if (ball_y > plate_2_position) {
        plate_2_position += change;
    } else {
        plate_2_position -= change;
    }
    if (plate_2_position < 0) {
        plate_2_position = 0;
    } 
    if (plate_2_position + 73 > HEIGHT) {
        plate_2_position = HEIGHT - 73;
    }
    filled_rectangle(fb, WIDTH - WIDTH / 6, plate_2_position, 3, 70);
}

#endif