#include"enemy.h"
#include <iostream>

void Enemy::Chase(const SDL_Point &food){

    int X = static_cast<int>(head_x);
    int Y = static_cast<int>(head_y);

    SDL_Point prev_cell{X,Y};

    if(food.x < X){
        head_x -= speed;
    }
    else if(food.x > X){
        head_x += speed;
    }
    else{
        if(food.y < Y){
            head_y -= speed;
        }
        else{
            head_y += speed;
        }
    }
    if(food.x == X && food.y == Y){
        return;
    }
    // wrap around
    head_x = fmod(head_x + grid_width, grid_width);
    head_y = fmod(head_y + grid_height, grid_height);

    SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};
    if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Enemy::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {

  body.push_back(prev_head_cell);

  if (!growing) {
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}
void Enemy::GrowBody() { growing = true; }
