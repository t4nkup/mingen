#ifndef BALL_H
#define BALL_H

typedef struct Ball {
    int x, y;
    int speedX, speedY;
    int radius;
} Ball;

// Initialize the ball
void Ball_Init(Ball* ball);

// Update ball position and handle bouncing
void Ball_Update(Ball* ball);

// Draw the ball (does not modify it)
void Ball_Draw(const Ball* ball);

#endif // BALL_H
