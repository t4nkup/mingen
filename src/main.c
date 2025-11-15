#include "../lib/raylib/raylib.h"
#include "../include/ball.h"

int main(void)
{
    const Color darkGreen = {20, 160, 133, 255};
    
    const int screenWidth = 800;
    const int screenHeight = 600;
    
    Ball ball;
    Ball_Init(&ball); // initialize the ball
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        Ball_Update(&ball); // update the ball
        
        BeginDrawing();
            ClearBackground(darkGreen);
            Ball_Draw(&ball); // draw the ball
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
