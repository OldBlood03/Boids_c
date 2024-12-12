#include "raylib.h"
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include"boids.h"
#include"ui.h"




int main(void) {
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 450;

    float separation = 0.6f; 
    float aggregation = 0.02f; 
    float alignment = 0.3f; 

    InitWindow(screenWidth, screenHeight, "Boids");
    Camera2D camera = { { 0.0f, 0.0f }, { 0.0f, 0.0f }, 0.f, 1.f };
    Slider separation_slider = {.rect = {10,100,100,5}, .knob_radius = 6.f, .completion = 0.5f, .text = "separation"};
    Slider aggregation_slider = {.rect = {10,200,100,5}, .knob_radius = 6.f, .completion = 0.5f, .text = "aggregation"};
    Slider alignment_slider = {.rect = {10,300,100,5}, .knob_radius = 6.f, .completion = 0.5f, .text = "alignment"};

    InitBoids(screenWidth, screenHeight);

    bool paused = false;

    SetTargetFPS(60);
    while (!WindowShouldClose()) {
        if (!paused){ UpdateBoids(separation, aggregation, alignment); }
        if (IsKeyPressed(KEY_SPACE)){ paused = !paused; }
        if (IsDraggingSlider(&separation_slider)){ DragSlider(&separation_slider); }

        BeginDrawing();

        ClearBackground(DARKPURPLE);
        DrawText("Press Space To Pause", 10,10,3,WHITE);

        DrawSlider(&separation_slider, LEFT);
        DrawSlider(&aggregation_slider, RIGHT);
        DrawSlider(&alignment_slider, UP);

        BeginMode2D(camera);

        DrawBoids();

        EndMode2D();
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
