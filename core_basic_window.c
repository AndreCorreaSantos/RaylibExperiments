

#include "raylib.h"
#include "stdio.h"

//----------------------------------------------------------------------------------
// Global Variables Definition
//----------------------------------------------------------------------------------
int screenWidth = 120;
int screenHeight = 450;
int targetFPS = 60;

int currentFPS;
char fpsText[3];

//----------------------------------------------------------------------------------
// Module Functions Declaration
//----------------------------------------------------------------------------------
void UpdateDrawFrame(void);     // Update and Draw one frame

//----------------------------------------------------------------------------------
// Main Entry Point
//----------------------------------------------------------------------------------
int main()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    screenHeight = GetMonitorHeight(0);
    screenWidth = GetMonitorWidth(0);
    targetFPS = GetMonitorRefreshRate(0);
    InitWindow(screenWidth, screenHeight, "raylib [core] example - core world screen");

    // Define the camera to look into our 3d world
    Camera camera = { 0 };
    camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 45.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

    Vector3 cubePosition = { 0.0f, 0.0f, 0.0f };
    Vector2 cubeScreenPosition = { 0.0f, 0.0f };    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    DisableCursor();                    // Limit cursor to relative movement inside the window
    SetTargetFPS(targetFPS);   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateCamera(&camera, CAMERA_THIRD_PERSON);

        // Calculate cube screen space position (with a little offset to be in top)
        cubeScreenPosition = GetWorldToScreen((Vector3){cubePosition.x, cubePosition.y + 2.5f, cubePosition.z}, camera);
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            BeginMode3D(camera);

                DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, MAROON);

                DrawGrid(10, 1.0f);

            EndMode3D();

            DrawText("Enemy: 100 / 100", (int)cubeScreenPosition.x - MeasureText("Enemy: 100/100", 20)/2, (int)cubeScreenPosition.y, 20, BLACK);
            
            DrawText(TextFormat("Cube position in screen space coordinates: [%i, %i]", (int)cubeScreenPosition.x, (int)cubeScreenPosition.y), 10, 10, 20, LIME);
            DrawText("Text 2d should be always on top of the cube", 10, 40, 20, GRAY);
            currentFPS = GetFPS();
            sprintf(fpsText,"%d",currentFPS);
            DrawText(fpsText,100,100,20,GREEN);
            EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}










