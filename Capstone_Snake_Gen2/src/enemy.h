#ifndef ENEMY_H
#define ENEMY_H
#include "snake.h"
#include <memory>

class Enemy : public Snake{
public:
    Enemy() = default;
    Enemy(int grid_width, int grid_height)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(grid_width / 4),
        head_y(grid_height / 4) {}

    void Chase(const SDL_Point &food);
    void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
    void GrowBody();
    float head_x;
    float head_y;
    float speed{0.05f};
    int score = 0;

private:
    int grid_width;
    int grid_height;
    bool growing{false};
};

#endif