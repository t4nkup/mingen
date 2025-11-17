#include "../include/mingen.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "Rotating Cube - Correct Raylib 5.5");

    Camera3D camera = { 0 };
    camera.position = (Vector3){4.0f, 4.0f, 4.0f};
    camera.target = (Vector3){0.0f, 0.0f, 0.0f};
    camera.up = (Vector3){0.0f, 1.0f, 0.0f};
    camera.fovy = 45.0f;
    camera.projection = CAMERA_PERSPECTIVE;

    Model cube = LoadModelFromMesh(GenMeshCube(2.0f, 2.0f, 2.0f));
    Vector3 cubePosition = {0.0f, 0.0f, 0.0f};
    Vector3 rotationAxis = {0.0f, 1.0f, 0.0f};
    float rotationAngle = 0.0f;

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        rotationAngle += 0.5f;  // degrees per frame

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(camera);
        DrawModelEx(cube, cubePosition, rotationAxis, rotationAngle, (Vector3){1.0f, 1.0f, 1.0f}, RED);
        DrawGrid(10, 1.0f);
        EndMode3D();

        DrawText("Rotating cube with DrawModelEx", 10, 10, 20, DARKGRAY);

        EndDrawing();
    }

    UnloadModel(cube);
    CloseWindow();

    return 0;
}
