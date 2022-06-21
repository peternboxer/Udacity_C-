#include "game.h"
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      //enemy(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1))
{
  enemy = std::make_unique<Enemy>(grid_width, grid_height);
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration,
               const int &mode)
{
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  _mode = mode; // update game mode

  while (running)
  {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, enemy, food, mode);

    frame_end = SDL_GetTicks();
    frame_count++;
    frame_duration = frame_end - frame_start;

    if (frame_end - title_timestamp >= 1000)
    {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    if (frame_duration < target_frame_duration)
    {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood()
{
  int x, y;
  while (true)
  {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y))
    {
      food.x = x;
      food.y = y;
      return;
    }
  }
}

void Game::Update()
{
  if (!snake.alive)
    return;
  //enemy.Chase(food);
  enemy->Chase(food);
  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  if (_mode == 1)
  {
    // int enemy_x = static_cast<int>(enemy.head_x);
    // int enemy_y = static_cast<int>(enemy.head_y);
    int enemy_x = static_cast<int>(enemy->head_x);
    int enemy_y = static_cast<int>(enemy->head_y);

    if (food.x == enemy_x && food.y == enemy_y)
    {
      std::cout << "You lose.\n";
      enemy->score++;
      std::cout << "Current score: " << this->score << "\n";
      std::cout << "Enemy score: " << enemy->score<<"\n";
      if (enemy->speed >= 0.02f)
      {
        enemy->speed -= 0.01f;
      }
      enemy->GrowBody();
      PlaceFood();
    }
  }

  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score++;
    std::cout << "You win!\n";
    std::cout << "Your score: " << this->score << "\n";
    std::cout << "Enemy score: " << enemy->score<<"\n";
    enemy->speed += 0.02f;
    PlaceFood();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }