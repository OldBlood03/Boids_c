#include"boids.h"

//bird prototype triangle
static constexpr Vector2 point1 = {0,0};
static constexpr Vector2 point2 = {-10,20};
static constexpr Vector2 point3 = {10,20};
static constexpr float view_distance = 3;

constexpr size_t nboids = 100;
static Boid boids[nboids];

static void Separate(float constant){
    for (size_t i = 0; i < nboids; i++){
        Vector2 total = {0.f};
        for (size_t j = 0; j < nboids; j++){

            if (i == j) continue;

            float xdiff = boids[j].pos.x - boids[i].pos.x;
            float ydiff = boids[j].pos.y - boids[i].pos.y;
            float len = sqrt(abs(xdiff * xdiff + ydiff * ydiff));
            if (len > view_distance) continue;

            total.x -= 1/(0.001f+len)*constant*xdiff;
            total.y -= 1/(0.001f+len)*constant*ydiff;
        }
        boids[i].force.x += total.x;
        boids[i].force.y += total.y;
    }
}

static void Aggregate(float constant){
    for (size_t i = 0; i < nboids; i++){
        Vector2 center = {0.f};
        size_t count = 1;
        for (size_t j = 0; j < nboids; j++){
            if (i == j) continue;

            float xdiff = boids[j].pos.x - boids[i].pos.x;
            float ydiff = boids[j].pos.y - boids[i].pos.y;
            float len = sqrt(abs(xdiff * xdiff + ydiff * ydiff));
            if (len > view_distance) continue;

            center.x += boids[j].pos.x;
            center.y += boids[j].pos.y;
            count++;
        }

        center.x /= count;
        center.y /= count;

        float xforce = (center.x - boids[i].pos.x) * constant;
        float yforce = (center.y - boids[i].pos.y) * constant;

        boids[i].force.x += xforce;
        boids[i].force.y += yforce;
    }
}

static void Align(float constant){
    for (size_t i = 0; i < nboids; i++){
        Vector2 avg = {0};

        for (size_t j = 0; j < nboids; j++){
            if (i == j) continue;
            avg.x += boids[j].force.x / nboids;
            avg.y += boids[j].force.y / nboids;
        }

        float xdiff = avg.x - boids[i].force.x;
        float ydiff = avg.y - boids[i].force.y;
        boids[i].force.x += constant*xdiff;
        boids[i].force.y += constant*ydiff;
    }
}

static void ApplyForce(){
    for (size_t i = 0; i < nboids; i++){
        boids[i].pos.x += boids[i].force.x;
        boids[i].pos.y += boids[i].force.y;
    }
}

void InitBoids(int screenWidth, int screenHeight){
    for (size_t i = 0; i < nboids; i++){
        const float x = GetRandomValue(screenWidth/2 - 100, screenWidth/2 +100);
        const float y = GetRandomValue(screenHeight/2 - 100, screenHeight/2 +100);

        const Vector2 pos = {.x = x, .y = y};
        boids[i].pos = pos;
    }
}

void UpdateBoids (float separation, float aggregation, float alignment){
    Separate(separation);
    Aggregate(aggregation);
    Align(alignment);
    ApplyForce();
}

void DrawBoids(){
    for (size_t i = 0; i < nboids; i++){
        Vector2 pos = boids[i].pos;
        const Vector2 p1 = {point1.x + pos.x, point1.y + pos.y};
        const Vector2 p2 = {point2.x+ pos.x, point2.y + pos.y};
        const Vector2 p3 = {point3.x+ pos.x, point3.y + pos.y};

        DrawTriangle(p1, p2, p3, WHITE);
    }
}
