#include "../lib/raylib/raylib.h"
#include "../include/ball.h"

void Ball_Init(Ball* ball) {
    ball->x = 100;
    ball->y = 100;
    ball->speedX = 5;
    ball->speedY = 5;
    ball->radius = 15;
}

void Ball_Update(Ball* ball) {
    ball->x += ball->speedX;
    ball->y += ball->speedY;

    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    if ((ball->x + ball->radius >= screenWidth) || (ball->x - ball->radius <= 0)) {
        ball->speedX *= -1;
    }

    if ((ball->y + ball->radius >= screenHeight) || (ball->y - ball->radius <= 0)) {
        ball->speedY *= -1;
    }
}

void Ball_Draw(const Ball* ball) {
    DrawCircle(ball->x, ball->y, ball->radius, WHITE);
}
