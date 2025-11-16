#include <stdio.h> 
#include "../lib/raylib.h"
#include "../include/ball.h"

int main(void)
{
    Color darkGreen = { 20, 160, 133, 255 };
    
    int screenWidth = 800;
    int screenHeight = 600;
    
    Ball ball;
    Ball_Init(&ball); // initialize the ball
    
    InitWindow(screenWidth, screenHeight, "My first RAYLIB program!");
    SetTargetFPS(60);
    
    while (!WindowShouldClose())
    {
        printf("test");
        Ball_Update(&ball); // update the ball
        
        BeginDrawing();
            ClearBackground(darkGreen);
            Ball_Draw(&ball); // draw the ball
        EndDrawing();
    }
    
    CloseWindow();
    return 0;
}
