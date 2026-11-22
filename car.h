#pragma once
#include <stdbool.h>
#include <raylib.h>
typedef struct car
{
    bool active;
    Texture2D image;
    Vector2 velocity;
    Vector2 direction;
    Vector2 position;
    Vector2 size;
    Color color;
    int speed;

}car;
car CarCreate(Vector2 position, Vector2 size, Color color);
void CarDraw(const car* c);
void CarUpdate(car* c);
void EnemyUpdate(car* e);
void EnemyRespawn(car* e, int speed, car* enemy_arr, int count);
Rectangle CarGetRect(const car* c);
typedef enum GameState { MENU, PLAYING, END }GameState;
