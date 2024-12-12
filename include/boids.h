#ifndef BOIDS
#define BOIDS
#include "raylib.h"
#include<stdlib.h>
#include<assert.h>
#include<math.h>

typedef struct Boid {
    Vector2 pos;
    Vector2 force;
}Boid;

void InitBoids(int screenWidth, int screenHeight);
void UpdateBoids (float separation, float aggregation, float alignment);
void DrawBoids();

#endif
