#include "car.h"

car CarCreate(Vector2 position, Vector2 size, Color color) {
    car c;
    c.position = position;
    c.color = color;
    c.size = size;
    c.speed = 10;
    c.velocity = (Vector2){ 3,2 };
    return c;

}

void CarDraw(const car * c){
        Rectangle source = { 0, 0, c->image.width, c->image.height };
        Rectangle dest = { c->position.x, c->position.y, c->size.x, c->size.y };
        DrawTexturePro(c->image, source, dest, (Vector2) { 0, 0 }, 0, c->color);
        // DrawRectangleLinesEx(CarGetRect(c), 2, RED);
}


void EnemyUpdate(car* e) {
    e->position.x += e->velocity.x;
    e->position.y += e->velocity.y;
}

void EnemyRespawn(car* e, int speed, car *enemy_arr, int count) {

        int lane_width = 800 / 3;
        for (int k = 1;k <= 20;k++) { // outer: find a new location


            // determines correct spot for enemy spawn so they dont overlap each other

            int lane = GetRandomValue(0, 2); // Lane 1(left), Lane 2(middle), Lane 3(right)

            e->position.x = lane * lane_width + ((lane_width - e->size.x) / 2);

            e->position.y = -(e->size.y) - GetRandomValue(0, 600);

            if (lane == 0) {
                e->velocity.x = speed;
            }
            else if (lane == 2) {
                e->velocity.x = -speed;
            }
            else {
                int m = GetRandomValue(0, 1);
                e->velocity.x = (m) ? speed : -speed;
            }
            e->velocity.y = speed;

            Rectangle r = CarGetRect(e);
            r.x -= 20;
            r.y -= 20;
            r.width += 40;
            r.height += 40;

            bool spot_free = true;

            for (int i = 0; i < count; i++) {   // Checks if the location is free or not
                                           // if it overlaps a previously occupied spot it will skip it
                if (&enemy_arr[i] == e) {
                    continue; // skips itself since the current spot (we're talking about) is already reserved
                                // for itself
                }
                if (CheckCollisionRecs(r, CarGetRect(&enemy_arr[i]))) {
                    spot_free = false;
                    break; // if another car is close to the bigger hitbox it will break and label the spot as bad
                    // since it's already used up and will look for a newer spot (outer loop)
                }
            }
            if (spot_free) {
                break; // If the current spot is not occupied by any of the other enemy cars, it will exit the outer
                        // loop since we now don't need to search for a new spot as this one is already free(clean).
            }
        }

       
        int choice = GetRandomValue(0, 2);
        if (choice == 0) {
            e->color = BLUE;
        }
        else if (choice == 1) {
            e->color = GREEN;
        }
        else {
            e->color = YELLOW;
        }
}
        

void CarUpdate(car* c) {

    if (IsKeyDown(KEY_RIGHT)) {
        c->position.x += c->speed;
    }
    if (IsKeyDown(KEY_LEFT)) {
        c->position.x -= c->speed;
    }
    if (IsKeyDown(KEY_UP)) {
        c->position.y -= c->speed;
    }
    if (IsKeyDown(KEY_DOWN)) {
        c->position.y += c->speed;
    }

    if (c->position.y < 0) {
        c->position.y = 0;
    }
    if (c->position.y > 600 - c->size.y) {
        c->position.y = 600 - c->size.y;
    }
    if (c->position.x < 0) {
        c->position.x = 0;
    }
    if (c->position.x > 800 - c->size.x) {
        c->position.x = 800 - c->size.x;
    }
}

Rectangle CarGetRect(const car* c)
{
    float padX = c->size.x * 0.15f;
    float padY = c->size.y * 0.10f;
    Rectangle r = { 
        c->position.x + padX, // it moves the hitbox from leftside towards right (inward) basically shrinking it.
        c->position.y + padY, // from up to down
        c->size.x - padX * 2, // this moves the hitbox from rightside towards left (inward) basically shrinking it.
        c->size.y - padY * 2 // from down to up
    };
    return r;
}
